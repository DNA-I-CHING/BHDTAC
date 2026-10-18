# Gravity Localization Report — *Delta Force: Black Hawk Down*

- **Target**: `DFBHD_P.exe` (v1.5.0.5, 32-bit PE, ImageBase `0x400000`, 2,547,712 bytes)
- **Method**: static analysis only (python + capstone + pefile, byte-level forensics)
- **Date**: 2026-10-18
- **Bottom line**: there is no single gravity constant. Gravity is hardcoded as **16.16 fixed-point immediates at 20 independent accumulation sites**, spread across the default ballistic mover, 10+ `useownmove` projectile movers, the soldier mover, and a vehicle mover. Patching any single site only affects its own object class.

---

## 1. Address convention

`.text` maps 1:1 from file offset: `VA = file_offset + 0x400000`. Both are listed (`offset = VA − 0x400000`).

## 2. Physics architecture

### 2.1 Mover dispatch

Per-frame movement is dispatched per instance:

```
0x491CB8  test ah, 0x80        ; useownmove flag bit
0x491CD3  call [obj+0x224]     ; if set, run the instance's custom mover
```

- Normal bullets run the default ballistic function `0x491B00`.
- Grenades, demo packs, claymores etc. (ammo carrying `useownmove` in items.def) run their own registered movers (function pointer at `[obj+0x224]`).
- The soldier mover is identified at `0x4168CD` (branches on `[obj+0x224] == 0x477310 / 0x477350 / 0x47CA90`); `0x477350` is the main mover containing gravity.

### 2.2 Numeric representation

- Physics quantities use **16.16 fixed point** (evidence: ammo record default `mov dword ptr [eax+0x1c], 0x10000` = 1.0).
- Gravity is a negative immediate **accumulated into Z velocity every frame**: `vz += (-167)` ≈ -0.002548 units/frame.
- Z-velocity field: instance `+0x74` (bullets/soldiers); some projectile movers use `+0x198` / `+0x19C`.
- Downward terminal-velocity clamp: `cmp eax, 0xffffc000; jl → clamp to -16384` (down only; upward is unclamped).

### 2.3 Related flags (items.def keywords)

| Keyword | Storage | Consumed at | Effect |
|---|---|---|---|
| `nogravity` | def+0 bit `0x400` | `0x49286C test ah,4` → `jne` skips gravity | ammo immune to gravity |
| `useownmove` | def+0 bit `0x8000` (high byte 0x80) | `0x491CB8 test ah,0x80` | route to custom mover |
| `nocollide` / `forcetracer` / `silenced` / `shrapnel` / `muzzle1/2` | other def+0 bits | ballistics/sfx/muzzle code | not gravity; confirms the keyword block grouping |
| (drag) | def+0x1C, 16.16, default 0x10000 | `0x491930`: `v = v*drag >> 16` | velocity damping; above water adds wind vector `[0xE19DC0/4/8]` |

## 3. Complete gravity accumulation table (20 sites)

File offset = VA − 0x400000.

### A. Normal bullets (mover `0x491B00`)

| # | VA | Offset | Original bytes | Const | Notes |
|---|---|---|---|---|---|
| A1 | 0x49288B | 0x9288C | `05 59 FF FF FF` | -167 | in-flight Z-velocity accumulation |
| A2 | 0x492883 | 0x92884 | `83 C0 EC` | -20 | submerged gravity (waterline `[0xB63374]`) |
| A3 | 0x491F4F | 0x91F52 | `81 C2 59 FF FF FF` | -167 | vertical fall after velocity zeroes out ("hovering" ammo still drops unless patched) |

### B. useownmove projectile movers (grenade / demo pack / claymore, etc.)

| # | VA | Offset | Original bytes | Const | Function (Z-vel field) |
|---|---|---|---|---|---|
| B1 | 0x46D72D | 0x6D730 | `81 C1 59 FF FF FF` | -167 | 0x46D6F0 (+0x19C) |
| B2 | 0x46DB9D | 0x6DB9E | `05 59 FF FF FF` | -167 | 0x46D950 (+0x198) |
| B3 | 0x46DDBE | 0x6DDBF | `05 59 FF FF FF` | -167 | 0x46D950 |
| B4 | 0x4734CD | 0x734D0 | `81 C1 59 FF FF FF` | -167 | 0x473490 (+0x74) |
| B5 | 0x4CF355 | 0xCF358 | `81 C2 59 FF FF FF` | -167 | 0x4CF2C0 |
| B6 | 0x4CF350 | 0xCF352 | `83 C2 C9` | -55 | 0x4CF2C0 submerged |
| B7 | 0x4CFB15 | 0xCFB18 | `81 C1 59 FF FF FF` | -167 | 0x4CFA80 |
| B8 | 0x4CFB10 | 0xCFB12 | `83 C1 C9` | -55 | 0x4CFA80 submerged |
| B9 | 0x4D07C9 | 0xD07CC | `81 C2 59 FF FF FF` | -167 | 0x4D0710 |
| B10 | 0x4D1643 | 0xD1644 | `05 59 FF FF FF` | -167 | 0x4D1580 |
| B11 | 0x4D164A | 0xD164C | `83 C2 C9` | -55 | 0x4D1580 submerged |
| B12 | 0x4D2079 | 0xD207C | `81 C2 59 FF FF FF` | -167 | 0x4D2020 |
| B13 | 0x4D30A5 | 0xD30A6 | `05 59 FF FF FF` | -167 | 0x4D2A70 |
| B14 | 0x457F3D | 0x57F40 | `81 C7 B2 FE FF FF` | -334 | 0x457EA0 (double-gravity projectile) |
| B15 | 0x473399 | 0x7339C | `81 C2 B2 FE FF FF` | -334 | 0x4730E0 (double-gravity projectile) |

### C. Soldiers / characters (mover `0x477350`)

| # | VA | Offset | Original bytes | Const | Notes |
|---|---|---|---|---|---|
| C1 | 0x47C440 | 0x7C443 | `81 C2 59 FF FF FF` | -167 | the only gravity site in a 6422-instruction function: `mov edx,[esi+0x74]; add edx,-167; cmp eax,0xffffc000; jl → clamp -16384` |

### D. Vehicles (optional)

| # | VA | Offset | Original bytes | Const | Notes |
|---|---|---|---|---|---|
| D1 | 0x4F3FD2 | 0xF3FD3 | `05 B2 FE FF FF` | -334 | function 0x4F3FB0 |

### Candidates ruled out

- `0x473A04` / `0x473E94` (-83): bounce / final-velocity handling, not gravity.
- `0x439519` (-1336): one-shot impulse.
- `0x477525` / `0x47BA71`: animation / timing code.
- Float constants 9.8 / 9.81 / 19.6 / 4.9: zero hits in .text (float encoding excluded).

## 4. Key disassembly evidence

Gravity block of the default ballistic mover (`0x49284C`–`0x492894`):

```
0x49284C  mov  eax,[ebx+0x224]      ; proceed only if ==0 or ==0x5382E0 (default-mover gate)
0x492866  mov  eax,[ebx+0xd8]       ; instance flags (copy of items.def def+0)
0x49286C  test ah,4                 ; nogravity bit 0x400
0x49286F  jne  0x492893             ; set → skip gravity entirely
0x492871  test eax,0x100000         ; in-water flag
0x492878  cmp  ecx,[0xb63374]       ; waterline height
0x492880  mov  eax,[ebx+0x74] / add eax,-0x14    ; submerged gravity -20
0x492888  mov  eax,[ebx+0x74] / add eax,-0xA7    ; normal gravity -167
0x492890  mov  [ebx+0x74],eax
0x492894  call 0x491930             ; drag applied right after
```

## 5. Patching guide

### 5.1 Field-tested lesson

Patching only A1 (0x9288C) affects **normal bullets only** — grenades / demo packs / claymores (`useownmove`) and characters are unaffected, confirming each mover carries its own gravity constant. **Gravity edits must be applied across the whole table.**

### 5.2 Reverse gravity (invert all)

| Original sequence | Replace with | Applies to |
|---|---|---|
| `59 FF FF FF` | `A7 00 00 00` | all -167 sites |
| `B2 FE FF FF` | `4E 01 00 00` | all -334 sites |
| `83 C0 EC` | `83 C0 14` | A2 submerged -20 |
| `83 Cx C9` | `83 Cx 37` | B6/B8/B11 submerged -55 |

Note: the terminal-velocity clamp (`0xFFFFC000`) limits downward speed only. With reversed gravity, upward speed is unclamped — objects accelerate off the map, which is expected. To cap the rise, the clamp branches must also be converted to positive-value form.

### 5.3 Halve / zero out

| Goal | Method |
|---|---|
| Halve | -167→-83 (`AD 00 00 00`), -334→-167, -20→-10, -55→-27 |
| Zero (keep branches) | immediates → `00 00 00 00`; small-form (`83 C0 EC` class) → last byte `00` |
| Force nogravity (default ballistics only) | at `0x9286F`: `75 22` (jne) → `EB 22` (jmp) |

### 5.4 Risk notes

- All offsets apply **only to v1.5.0.5** of `DFBHD_P.exe`; other versions require re-localization.
- Patch with byte assertions (verify original bytes before writing). The delivered patch was generated and verified this way: 20 sites / 68 changed bytes, the rest of the file byte-identical to stock.
- Back up the stock exe first; no self-integrity check was observed — restore the backup if anything misbehaves.

## 6. Relation to ragdoll

- Soldier falling shares the "fixed-point Z-velocity accumulation + terminal clamp" pattern with projectiles, but **bone matrices are driven purely by .bad keyframes**; the engine has no per-bone physics solver (keywords verlet/rigid/constraint etc. yield zero hits).
- Patching the sites above changes **root-position** motion of corpses/characters (fall, float, ballistics), but cannot produce limb physics. A true ragdoll still requires an injected DLL hooking the bone-write path plus a custom solver.
