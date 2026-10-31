# Joint Operations: Typhoon Rising — Wind System & Bullet Wind Drift Patch, Analysis Report

- **Target file**: `jointops.exe` (32-bit PE, ImageBase `0x400000`, 4,612,096 bytes)
- **Method**: Ghidra static analysis + byte-level scanning/patch generation + in-game verification
- **Date**: 2026-11-01 (initial 2026-10-31)
- **Conclusion**: The engine ships a complete weather wind system (wind speed kph, wind direction, wind vector globals), and the wind vector correctly drives smoke/particles — but the wind term inside the drag function is **dead code** (`v+=wind → v+=decel → v-=wind`, an add/sub sandwich with no multiplication in between, net effect always zero). Bullets ignoring wind is a refactor leftover, not a missing feature. A 10-byte hook + a 39-byte code cave in a `.text` cc alignment gap give bullets ideal constant-acceleration wind drift (`v += wind >> K`, nine tiers K0–K8, using the engine's native wind power: full wind = 118% of gravity). The injection structure is verified in-game, drift direction correct.

---

## 1. Address Conventions

Within `.text`: `VA = file offset + 0x400000`. The hook sits in the bullet mover `FUN_004e9d70`: VA `0x4EAA5A` = file offset `0xEAA5A`. The patch cave sits in a cc alignment gap between functions in mid-`.text`: VA `0x7472C9` = file offset `0x3472C9` (55 × `0xCC`, immediately followed by an instruction starting with `0F`).

## 2. Wind System Forensics

### 2.1 Mission-side variables and generation path

| Variable | VA | Meaning |
|---|---|---|
| mp_wind MP option | `0x02550B58` → mission state `0x024D20DC` | wind setting delivered with the mission |
| Mode dispatch | `FUN_00524360` | 0=custom, 1=no wind, 2=random wind |

Mode 2 uses the random-wind generator `FUN_005dea80`; the custom path writes the wind vector globals through the setter after MED/host configuration.

### 2.2 Wind vector globals (core)

| Variable | VA | Meaning |
|---|---|---|
| wind_x | `0x02C059E4` | 16.16 fixed point |
| wind_y | `0x02C059E8` | 16.16 fixed point |
| wind_z | `0x02C059EC` | always 0 (wind is horizontal) |
| Weak-wind copies | `0x02C059F0` / `0x02C059F4` | write-only, never read (dead data) |

Conversion happens inside the setter `FUN_005de970(direction, speed)`: angle = `(90−direction)°`, magnitude `mag = speed_kph × 65536 / 234`, component = `sin/cos × mag >> 22`. Full 45 kph wind ≈ **197/frame**.

### 2.3 Particle side (why wind "only seems to affect smoke")

The visual path `FUN_005f70c0` reads `0x02C059E4/E8/EC` to displace smoke, dust and fire particles every frame — the wind system itself is alive and clearly observable; only the bullet side is disconnected.

## 3. Bullet side: why wind has no effect (root cause)

The drag function `FUN_004e5ec0` (0x4E5EC0–0x4E64DE, 438 instructions; 4 mover callers `0x445420` / `0x4EC920` / `0x4E9D70` / `0x545100`) contains a BHD-refactor leftover wind handler (0x4E60F3–0x4E6165, fully verified in disassembly):

```
v += wind
v += decel        ; precomputed air drag: decel = table DAT_00B7B300[speed] / drag / 0x3E, along -v
v -= wind         ; ← cancels the first line, net effect always zero
```

The original BHD formula is `(v + wind) * drag >> 16 - wind` — the multiplication sits between the add/subtract, so the wind term survives. JO refactored to a "precomputed decel" model, the multiplication in the middle disappeared, and the wind term became dead code. **In JO, drag≠1 only yields real air deceleration and never wind drift; editing the drag value in items.def cannot produce wind.**

The two games have completely different drag semantics:

| | BHD | JO |
|---|---|---|
| Formula | `(v+wind)*drag>>16 − wind` (multiplicative damping) | `decel = table[speed]/drag/0x3E`, along −v |
| drag=1 | early return (default ammo no-ops) | normal deceleration |
| drag=0 | extreme damping | zero deceleration (divide-guard) |
| drag>1 | faster deceleration | flies farther (weaker drag force) |

JO anti-reversal guard: `dot(v,decel)>0 → v=0`. Velocity fields: instance `+0x98`=vx, `+0x9C`=vy, `+0xA0`=vz.

## 4. Patch Design

### 4.1 Code cave selection

| Candidate | File state | Runtime verdict |
|---|---|---|
| `_text` section tail slack (`0x7BFA10`, RawSize>VirtualSize) | all zeros | unusable — JO overwrites the `_text` section with data tables at runtime |
| `.text` tail zero-fill (`0x794DEB`+) | all zeros | unusable — overwritten by JIT-generated thunks (cc fill + b9/e9 pattern, referencing heap addresses that change every run) |
| Mid-`.text` cc alignment gap `0x7472C9` | 55 × 0xCC | usable — cc fill is neither overwritten nor executed by the engine; the JO patch family (FP lights / vehicle VTOL) uses the same cave type, runtime-verified stable |

**Zero bytes in the file ≠ usable space at runtime**; the only reliable JO cave sites are cc gaps in mid-`.text`.

### 4.2 Injection scheme (49 bytes written per tier, 48-byte diff vs original)

**Hook** (file `0xEAA5A`, 10 bytes) — the bullet gravity block, naturally "bullets only":

```
004eaa4e  TEST [EBX+0x114],0x100      ; object flags bit 0x100
004eaa58  JNZ  0x4eaa64               ; set=grenade class: skip mover gravity
004eaa5a  ADD  [EBX+0xa0],0xffffff59  ; clear=bullet: vz -= 167   ★ hook
004eaa64  PUSH 0 / PUSH 1 / PUSH EBX
004eaa69  CALL 0x4e5ec0               ; drag function (grenade gravity lives inside it at 0x4E6329)
```

```
original: 81 83 A0 00 00 00 59 FF FF FF
patched:  E8 6A C8 25 00 90 90 90 90 90   ; CALL 0x7472C9 (rel32=0x25C86A) + NOP×5
```

The engine splits gravity into two complementary halves: bit 0x100 **clear** (bullets) applies gravity in the mover, **set** (grenades/thrown objects) applies gravity inside the drag function (`0x4E6329`). Hooking the bullet branch means grenades reach the JNZ and skip the patch entirely — no extra checks needed.

**Cave** (file `0x3472C9`, 39 bytes):

```
0x7472C9  add  [ebx+0xA0],-167         ; original gravity instruction relocated verbatim
0x7472D3  mov  eax,[0x02C059E4]        ; wind_x
0x7472D8  sar  eax,K                   ; tier
0x7472DB  add  [ebx+0x98],eax          ; vx += wind
0x7472E1  mov  eax,[0x02C059E8]        ; wind_y
0x7472E6  sar  eax,K
0x7472E9  add  [ebx+0x9C],eax          ; vy += wind
0x7472EF  ret                          ; → 0x4EAA5F(NOP×5) → 0x4EAA64 args → CALL drag
```

Semantics: turns wind from dead code into a **per-tick constant-force acceleration** (ideal wind model), effective for all ammo types of mover `FUN_004e9d70` regardless of drag; `sar` (arithmetic shift) keeps negative wind components sign-correct; wind_z is always 0 so vz needs no handling. Register safety: EBX = bullet instance (used by the original instruction anyway), EAX is dead at the hook (reloaded at `0x4EAA71`).

### 4.3 Native wind tier adjustment

16.16 fixed point, tick ≈ 60 Hz: gravity 167/frame ≈ 9.17 m/s²; JO full wind 45 kph ≈ 197/frame ≈ **118% of gravity** — the patch uses the engine's native wind power as-is with no extra scaling: a full crosswind pushes a bullet at about 1.18× gravity per tick.

Each tier divides the wind by 2^K with `sar eax,K`: one 3-byte instruction with a 1-byte immediate — changing tiers means editing immediates only, instruction length is fixed (all nine tiers share the exact same code layout), and the shift is exact in fixed point with no rounding accumulation. The nine tiers span 118% → 0.45% (a 256× range, each tier halves).

Edit file offsets **`0x3472DA`** and **`0x3472E8`** (`sar` immediates, both must match):

| K | Wind (full wind vs gravity) | 300 m drift* | Notes |
|---|---|---|---|
| `00` | 118% | ~76 cm | = JO native full-wind strength (reference only) |
| `01` | 59% | ~38 cm | |
| `02` | 29.5% | ~19 cm | |
| `03` | 14.7% | ~9.5 cm | |
| **`04`** | 7.3% | ~4.8 cm | **recommended** |
| **`05`** | 3.7% | ~2.4 cm | **recommended** |
| `06` | 1.8% | ~1.2 cm | |
| `07` | 0.9% | ~0.6 cm | |
| `08` | 0.45% | ~0.3 cm | barely noticeable |

\* Anchor: 800 m/s bullet, full 45 kph crosswind, square-law drift ½at².

### 4.4 Coverage

- ✅ All ammo types of the bullet mover `FUN_004e9d70` — the hook sits on the common path before the drag call, independent of drag value.
- ✅ Grenades/satchels/claymores: they take the bit-0x100-set complementary branch (gravity inside the drag function at `0x4E6329`), automatically unaffected — nothing to do.
- ❌ Soldier/vehicle movers (the other 14 gravity sites; byte pattern `81 8r A0 00 00 00 59 FF FF FF` scans to 16 sites file-wide): not needed.
- Windless maps: wind vector is 0, the patch's add is always 0, trajectories are bit-identical to the original — safe to keep installed permanently.

## 5. Verification Log

1. In-game verification (2026-10-31, same injection structure — same hook, same cave, same add semantics): wind drift works, **direction correct** (the `+=` convention holds — the stored wind vector points downwind). Direction findings are scale-independent and carry over to the native build; drift magnitudes at native tiers are pending in-game confirmation.
2. Only maps with wind actually set in MED are affected; windless maps show no difference.
3. Patch integrity: five generator assertions (source size 4,612,096; original hook bytes verified byte-for-byte; cave region 55 × 0xCC; each tier differs from the original in exactly 48 bytes, all inside the hook/cave ranges; the nine tiers differ from each other in exactly 2 bytes @ `0x3472DA`/`0x3472E8`). The assertion chain caught two real bugs: a miscalculated rel32 (now guarded by a formula-based assertion) and a misplaced second `sar` immediate (cave offset 31, not the assumed-symmetric 30 — offset 30 is the F8 opcode byte).

## 6. Related Documents

- DFBHD companion report: `Wind_Bullet_zh-CN.md` (ballistic wind analysis of this engine's predecessor and the source of the `+=` direction convention; combined, the two reports form the complete ballistic physics picture of this engine).
- Release notes: `readme.txt` (bilingual tier table, install steps, DIY tier offsets, MP same-tier requirement).
- Patch generator: `gen_patch_JO_wind_native.py` (assertion chain + capstone self-check, outputs the nine tier exes).
