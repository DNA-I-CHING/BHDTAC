# DFBHD.exe Satchel `powerupdef` Code-Cave Patch — Analysis Report

> Goal: in *Delta Force: Black Hawk Down* (DFBHD.exe, V1.5.0.5), adding
> `powerupdef AmmoFull` to ITEMS.DEF id 101891 (Satchel Charge, move/ai=schl,
> disk=EXPLOSV) should let the player walk over the dropped satchel and pick it
> up for full ammo — without crashing.
> Status: **v2 patch confirmed working in-game** (no crash + pickup refills ammo).

---

## 1. Root cause of the crash (SYSDUMP + static disassembly proven)

With the modified ITEMS.DEF, the vanilla exe crashes on throwing/touching:

```
AV @ EIP=0x004AFFB8, read attempt at 0x0000002C (EAX=0)
```

The fault site is inside the pickup/interaction evaluation routine **0x4AFF40**
(caller at 0x4B05A4; args `[ebp+8]=obj`, `[ebp+0xC]=result-byte pointer, 0xFF=unavailable):

```asm
0x4AFF8F  mov  eax,[esi+0x24]        ; ITEM record pointer
0x4AFF92  mov  ebx,[eax+0x34]        ; flags dword (powerupdef flag = bit 0x2)
0x4AFF98  je   normal path           ; no flag -> regular evaluation
0x4AFFA7  mov  ecx,[esi+0x28]
0x4AFFAA  test ecx,ecx
0x4AFFAC  mov  eax,[esi+0x198]       ; powerup definition-record pointer
0x4AFFB2  je   0x4B02A7              ; only null-checks obj+0x28, never eax
0x4AFFB8  mov  ecx,[eax+0x2C]        ; <-- AV here when EAX=0
```

**Root cause**: `obj+0x198` (powerup definition pointer) is only populated by the
POWERUP disk-registration chain. The satchel's disk_function is EXPLOSV and its
move_function is schl, so it never goes through POWERUP registration and
`+0x198` stays 0; once the flag is set, the evaluator dereferences `[eax+0x2C]`
with no NULL check — part of this engine's family of missing-NULL-check defects
(the JointOps sibling is at 0x50FB55 reading +0x2C0).

## 2. Engine powerup registration chain (capstone static findings)

### 2.1 Dispatch tables

- **disk_function name table @0x63BF78** (stride 20, `{name[16]; fn}`, 9 entries):
  GENERIC→0x46E2D0, **POWERUP→0x48C9F0**, ORGANIC→0x441DA0, PLAYER→0x441EA0,
  HELO→0x441EC0, EMPLACE→0x441F00, LANDMINE→0x4D54D0, EXPLOSV→0x4D06F0, MARKER→0x442070
- move_function name table sits above it (stride 16, `{name[8]; fn}`), schl→0x4D1580

### 2.2 PU_REG = 0x48C6B0 (__cdecl, single obj argument)

- powerupdef name string comes from **ITEM record +0x790**
- Definition table: **base dword[0x96D1B8], count dword[0x96D1B0], stride 0xB8**
- Name match via strcmp **0x5C3570** (return 0 = match)
- On success it writes the object fields:
  | Field | Value | Meaning |
  |---|---|---|
  | obj+0x198 | def pointer | powerup definition record |
  | obj+0x224 | 0x48B580 | per-frame mover |
  | obj+0x190 | [def+0x20] | |
  | obj+0x194 | [def+0x24] | pickup apply callback |
  | obj+0x1a0 | [def+0xB4]-1 (-1 if <=0) | remaining pickup count |
  | obj+0x18c | -1 | "not chambered" (0 = pickup allowed) |

### 2.3 Pickup mover = 0x48B580

- Global gate `[0x9F2190]`; returns if `+0x1a0==0`; `+0x18c>0` = cooldown tick;
  `+0x18c<0` = skipped
- **Pickup runs only when `+0x18c==0`**: calls `[obj+0x194]` (the def+0x24
  apply callback — the refill-ammo family at 0x48B5F0), then decrements `+0x1a0`
- After pickup it calls 0x48C8A0 (effect/string logic) only if `word[obj+0x19E] != 0`

### 2.4 Key lesson: PU_REG must NOT be called on non-POWERUP-shaped objects

The v1 patch simply did `call PU_REG` inside the code cave; in testing it crashed
on touching the satchel:

```
AV @ EIP=0x77952D59 (strlen scan loop inside ntdll), read at 0x0012B078
Stack return address 0x0048CF76 = right after `call 0x55D400` inside 0x48C8A0
```

Reason: PU_REG's tail logic (the EFFECT table lookup 0x518AB0 treats `[obj+0x28]`
as a stride-0xB8 table base and searches the string "EFFECT"@0x63CF7C; and
0x48C8A0 treats `[obj+0x88]`, record +0x294/+0x2B4 as strings) **assumes a real
POWERUP object shape**. On the satchel those fields are garbage, so the scan /
strlen walks into unmapped memory.

## 3. v2 patch design (confirmed working)

### 3.1 PE structure: new executable section `.joext`

| Item | Value |
|---|---|
| RVA / VA | 0xB72000 / 0x00F72000 |
| raw offset / size | 0x26E000 / 0x1000 |
| Characteristics | 0x60000020 (CODE\|EXECUTE\|READ) |
| Section count | 7 → 8 (0xCB8 of slack after the section table is enough) |
| SizeOfImage | → 0xB73000 |
| File size | 2547712 → **2551808** bytes |

### 3.2 Hook

At 0x4AFFA7 the 5 bytes `8B 4E 28 85 C9` are replaced by `E9 rel32` into the
cave (exact length match; the return point 0x4AFFB2 sits on a clean instruction
boundary).

### 3.3 Code cave (264 bytes): inline "minimal registration"

Register constraint: ebx/edx/edi/esi stay live on the evaluator's later path, so
**the cave may only clobber eax/ecx**.

Flow:

1. `[esi+0x198] != 0` (already registered, a real powerup) → replay the original
   3 instructions and jump back to 0x4AFFB2
2. `[esi+0x28] == 0` → jump to 0x4B02A7 (native "result 0xFF, unavailable" return)
3. Otherwise `sub esp,8` to stash the name (record+0x790) and index i; loop:
   `def = [0x96D1B8] + i*0xB8`, `push def / push name / call 0x5C3570`;
   match → FOUND; `i >= [0x96D1B0]` (not found) → leave +0x198=0 and take the
   native skip path
4. FOUND writes only safe fields: `+0x224=0x48B580`, `+0x198=def`,
   `+0x190=[def+0x20]`, `+0x194=[def+0x24]`,
   `+0x1a0=([def+0xB4]>0 ? [def+0xB4]-1 : -1)`, and zeroes
   `+0x19C/+0x19D/+0x19E(word)/+0x230` — **zeroing +0x19E guarantees the mover
   never calls the dangerous 0x48C8A0**
5. Finally write `+0x18C=0` (chambered), replay context, jump back to 0x4AFFB2

### 3.4 Verification

- Cave machine code was checked instruction-by-instruction with capstone: all
  jcc/jmp/call targets and esp balance (`sub esp,8` paired with `add esp,8` on
  both exits) are correct
- Encoding lesson: the imm8/disp8 short forms sign-extend 0xB8 into -72/-0x4C —
  values > 0x7F must use imm32 (`69 C0 B8 00 00 00`) / disp32 (`8B 81 B4 00 00 00`)
- In-game test: touching the satchel no longer crashes → walking over it picks
  it up → ammo fully refilled ✓

## 4. Deliverables

| File | MD5 | Notes |
|---|---|---|
| `DFBHD_satchel_powerup_v2.exe` | `EDEC0581F37F4BE5BC195CAC69DD98AD` | 2551808 bytes, based on vanilla |
| vanilla `DFBHD.exe` | `D6F51AD03CA62F040586B8B5E3CA8181` | 2547712 bytes |

Usage: copy the v2 exe into the game folder replacing DFBHD.exe, and keep the
modified ITEMS.DEF (id 101891 with `powerupdef AmmoFull`).

Note: v2 is built on the **vanilla** exe and does not include the medpack
self-heal / all-class patches; a combined build can be produced on request.
