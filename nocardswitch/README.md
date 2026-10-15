# BHD Weapon View — Reverse Engineering Analysis & Binary Patches

Reverse engineering notes for two first-person weapon issues in
**Delta Force: Black Hawk Down** (`DFBHD.exe`, PE32 / x86).

| Target | SHA-256 (original) |
|---|---|
| `DFBHD.exe` | `4ce49ba04993ebed5ccef631050ddb87c113b47ec2f2b12f7803380f70846026` |
| File size | 2,547,712 bytes (image base `0x400000`) |

Two defects are documented and patched here. Combined footprint: **6 bytes**.

---

## Table A — Weapon definition layout

The `.def` parser (`FUN_004CB040`, the weapon.def keyword handler) populates a
global table. Entries are **0x338 (824) bytes** each, at most **60** (`0x3C`).

| Field | Offset | Notes |
|---|---|---|
| `category` | `+0x00` | Clamped to 0–9 by the parser |
| `rank` | `+0x04` | Clamped to 0–24 (`0x18`) |
| `flags` | `+0x28` | Bitfield, see Table B |
| `scope_max_mag` | `+0x34` | Magnification ceiling |
| **`pos`** | `+0x64` | Hip-fire transform (6 × dword) |
| **`cur`** | `+0x7C` | Live/animated transform (6 × dword) |
| **`tpos`** | `+0x94` | Sighted transform (6 × dword) |

Global table base `DAT_00A05360`, name table `DAT_00A05543`.

Slot index: `slot = (category * 0x19 + rank) * 0x60`
(`0x19` = 25 → 25 rank slots per category; instance stride `0x60`).

### Table B — `flags` bitfield (`+0x28`)

| Bit | Name | Used by |
|---|---|---|
| `0x1` | `Scoped` | `FUN_00488D90` |
| `0x2` | **`Sighted`** | `FUN_00488DC0` |
| `0x8` | `AutoLob` | FOV path |
| `0x10` | `NoClipsNoDraw` | `FUN_00488930` |
| `0x80` | `Emplaced` | `FUN_004CA054` |

---

# Patch 1 — `category 2` first-person flicker

## Symptom

Any weapon moved into category `2` makes the first-person model oscillate
between its `pos` and `tpos` transforms while firing. Any other category
behaves normally.

## Root cause

`FUN_00487270` (`0x487270`), reached on weapon switch / sight reset.

```asm
00487389  mov   edi, dword ptr [eax]   ; edi = def->category
0048738b  xor   edx, edx
0048738d  cmp   edi, 2
00487390  setne dl                     ; dl = (category != 2)
00487393  dec   edx                     ; -1 -> 0xFFFFFFFF, 0 -> 0
00487394  and   edx, esi                ; & weapon instance pointer
00487396  mov   dword ptr [0x96B660], edx
```

> **Operator precedence warning**
> Ghidra renders this as `(... != 2) - 1 & param_1`. In C, `-` binds tighter
> than `&`, so the real semantics are `((cat != 2) - 1) & esi` — **not** a literal
> `-1`.

| `category` | `(cat!=2)-1` | `& esi` | Result |
|---|---|---|---|
| `!= 2` | `0x00000000` | `0` | channel **closed** — model stays at `pos` |
| `== 2` | `0xFFFFFFFF` | `esi` | channel **open** — `pos`/`tpos` lerp runs |

`DAT_0096B660` is consumed by `FUN_00489CC0` (`0x48AD48`):

```asm
0048AD48  mov  eax, dword ptr [0x96B660]
0048AD4D  test eax, eax
0048AD4F  je   0x48ADFE        ; zero -> skip the whole sight transition
```

So `category == 2` **opens** the interpolation channel. This is a hidden engine
convention: category 2 is the secondary (pistol) slot, whose weapons have no
independent sight and are expected to share a viewmodel host. Assigning any other
weapon to category 2 trips the convention.

> This was the only literal `== 2` comparison against `category` in the entire
> binary. Verified by byte-scan of the whole `.text`.

## Patch

`cmp edi, 2` → `cmp edi, 0x0B`.

The parser clamps `category` to 0–9 (`if ((iVar5 < 0) || (9 < iVar5)) iVar5 = 0;`),
so `0x0B` is unreachable and the special case can never be selected. Behaviour for
categories 0–9 is bit-for-bit unchanged.

| File offset | VA | Original | Patched |
|---|---|---|---|
| `0x8738F` | `0x48738F` | `02` | `0B` |

Verified working in-game by the user.

---

# Patch 2 — Sighted weapons: real 3-D iron sights

## Symptom

Weapons carrying `flags Sighted` (with or without `sights` texture rows) make the
first-person model disappear when right-click is held. The model is neither
hidden by a flag nor pushed off-screen — it **enters the texture-sight state**
on arrival at `tpos`.

## Root cause

Right-click is handled as `case 6` in `FUN_00489CC0`:

```asm
00489CFF  call 0x488CC0        ; FUN_00488CC0 — pos <-> tpos interpolation
```

`FUN_00488CC0` (`0x488CC0`) gates on `flags & 3`:

```asm
00488CE7  test byte ptr [eax+0x28], 3    ; Sighted(0x2) | Scoped(0x1)
00488CEB  je   0x488D8A                   ; neither -> do nothing
```

Then the interpolation direction is chosen by `DAT_0096C3E0`, and on arrival the
engine derives the aim state from a second flag:

```asm
; ---- interpolation complete  (VA 0x48771F) ----
00487719  mov   ecx, dword ptr [0x96B668]   ; b668
0048771F  xor   eax, eax
00487721  cmp   ecx, ebx                    ; ebx = 0
00487723  setne al                          ; al = (b668 != 0)
00487726  mov   dword ptr [0x96B670], ebx
0048772C  mov   dword ptr [0x96C3E0], eax   ; c3e0 = (b668 != 0)
```

`DAT_0096C3E0` is the aim-state flag. Byte-scanning every write to it shows it is
cleared in seven places and **set in exactly one** — the `0x48772C` above:

| VA | Value | Meaning |
|---|---|---|
| `0x41C71A`, `0x420B7D`, `0x48AE2A`, `0x4CA2DF`, `0x4C97AF`, `0x4C988F`, `0x4C9CF3` | `0` | cleared |
| **`0x48772C`** | `eax` | **only non-zero source** |

Both flag queries multiply by it:

```asm
; FUN_00488D90  — Scoped
00488DA9  mov   eax, dword ptr [eax+0x28]
00488DAC  mov   ecx, dword ptr [0x96C3E0]
00488DB2  and   al, 1
00488DB4  neg   al
00488DB6  sbb   eax, eax
00488DB8  and   eax, ecx          ; return -(Scoped) & aim_state

; FUN_00488DC0  — Sighted
00488DD9  mov   eax, dword ptr [eax+0x28]
00488DDC  mov   ecx, dword ptr [0x96C3E0]
00488DE2  and   al, 2
00488DE4  neg   al
00488DE6  sbb   eax, eax
00488DE8  and   eax, ecx          ; return -(Sighted) & aim_state
```

Once `c3e0 == 1` and `Sighted` is set, both return non-zero, which arms the
entire texture-sight pipeline: FOV compression, post-processing, scope HUD text,
scope pixel masking — and the first-person model yields to the overlay.

`Sighted` is read in only **two** places in the whole binary (the two helpers
above). All **nine** call sites of those helpers were decompiled individually;
every one is FOV / post-processing / HUD / pixel-mask / effect related. **None
of them gates 3-D model visibility.** The flag is not a hide switch — it decides
*whether the model moves*, and the hide is a side effect of entering the
texture-sight state.

## Patch

Two coordinated edits:

| File offset | VA | Original | Patched | Effect |
|---|---|---|---|---|
| `0x087723` | `0x487723` | `0F 95 C0` (`setne al`) | `31 C0 90` (`xor eax,eax` ; `nop`) | `c3e0` stays `0` → texture-sight pipeline never arms |
| `0x088D01` | `0x488CFF` | `8B 15 E0 C3 96 00` | `8B 15 68 B6 96 00` | exit test reads `DAT_0096B668` instead of `c3e0` |

### Why the second edit is required

With `c3e0` forced to `0`, the exit branch in `FUN_00488CC0` becomes unreachable,
so the model can never travel back from `tpos` to `pos`:

```asm
00488CFF  mov   edx, dword ptr [0x96C3E0]   ; original test operand
00488D05  test  edx, edx
00488D07  je    0x488D56                    ; c3e0 == 0 -> "enter sight"
           ; ... fallthrough = "leave sight" branch ...
```

### Flag semantics — `0x96B668` vs `0x96B66C`

These two differ by one digit in name but are **opposites**. Both were verified by
enumerating every read and write:

| Flag | Semantics | Evidence |
|---|---|---|
| `DAT_0096B668` | `0` = hip-fire, `1` = sighted — **current state** | init `0x4871FD`=`0`; enter `0x488D56` / `0x48735D`=`1`; leave `0x488D39`=`0` |
| `DAT_0096B66C` | `0` = travelling to `tpos`, `1` = returning to `pos` — **motion direction** | init `0x4871F5`=`1`; enter `0x488D82`=`0`; leave `0x488D4D`=`1` |

An earlier revision used `0x96B66C` and failed: at `tpos`, `b66c == 0`, so the
`je` branched back into "enter sight" and the model kept re-running `pos → tpos`.
`0x96B668` is the correct substitute — it stays `1` while sighted, so the `je`
falls through into the leave-sight branch.

### Verified toggle sequence

| Step | `b668` | `b66c` | `c3e0` | Behaviour |
|---|---|---|---|---|
| initial | 0 | 1 | 0 | at `pos` |
| press RMB | 0 → **1** | → 0 | 0 | enter branch → `b280(15, pos, tpos)` |
| arrival | 1 | 0 | 0 | `c3e0` forced 0 → helpers return 0 → **3-D sights** |
| press RMB | 1 → 0 | → 1 | 0 | `je` not taken → leave branch → `b280(tpos, pos)` |
| press RMB | 0 | 1 | 0 | cycle repeats |

### Preserved

- `FUN_00488D90` / `FUN_00488DC0` bodies untouched — their other four callers
  (AI audio and similar) are unaffected
- `FUN_0048B280` interpolation logic untouched — the `pos ↔ tpos` animation runs
  exactly as before
- Other gates in `FUN_00488CC0` untouched: `0x488CE7` (`flags & 3`) and
  `0x488CF9` (`b664` occupancy)
- `FUN_00487270` switch/reset path untouched

---

## Verification

| Check | Result |
|---|---|
| Bytes modified (patch 1) | 1 |
| Bytes modified (patch 2) | 5 |
| File size | 2,547,712 — unchanged |
| MZ / PE signature | valid |
| Section headers | all 7 intact, byte-identical |
| `.text` → file offset | `VA − 0x400000` (`.text` `rawoff == RVA`) |
| Post-patch disassembly | both sites re-decoded, control flow intact |
| In-game | both patches confirmed working by the user |

---

## Reproducing

```python
# image base 0x400000; .text section rawoff == RVA, so file_off = VA - 0x400000
PATCHES = [
    # category-2 flicker
    (0x8738F, bytes.fromhex("02"),        bytes.fromhex("0b")),
    # 3-D sights, part 1: aim-state flag forced low
    (0x087723, bytes.fromhex("0f95c0"), bytes.fromhex("31c090")),
    # 3-D sights, part 2: exit test uses the sighted-state flag
    (0x088CFF, bytes.fromhex("8b15e0c39600"), bytes.fromhex("8b1568b69600")),
]
```

Verify the expected original bytes before writing, and diff the result to confirm
only the intended bytes moved.

---

## Method notes

Two lessons cost most of the time on this analysis:

1. **Read the assembly for anything involving precedence or masking.**
   `(... != 2) - 1 & param_1` reads as "yield −1" but computes `0` or a valid
   pointer — the opposite of the first reading.

2. **Exhaustively enumerate every read/write of a flag before theorising.**
   A byte-scan listing all five `flags` test sites and both `Sighted` sites would
   have surfaced `0x487723` immediately. Instead, three rounds of speculation
   about model hiding and screen-space offsets were pursued first. The fix was
   3 bytes; the detour was not.

Corollary: when substituting a variable, confirm its semantics directionally from
all of its write sites first. `0x96B668` and `0x96B66C` are one digit apart and
mean opposite things.

---

## Appendix — toolchain

- **Ghidra 12.1.4** headless (`analyzeHeadless`), project reused with `-noanalysis`
  (~15 s per script run after the initial full analysis)
- **capstone 5.0.7** for byte-level disassembly of individual functions
- Raw byte scanning of `.text` for instruction encodings, used to avoid
  decompiler-syntax ambiguity

Ghidra 12 scripting pitfalls encountered:

- `Instruction.getNumAddressTypes()` / `getAddress()` — removed from the Memory API
- `Instruction.getOperandType(i)` returns `int`, not an operand object
- Text matching on `ins.toString()` is the most reliable pre-filter before
  decompiling
- Large decompiler output must be written by the script itself via
  `PrintWriter`; stdout is swallowed by the analyzer banner
- Ghidra renders struct byte offsets as dword indices: `+0x64` → `[0x19]`,
  `+0x94` → `[0x25]`, `+0x28` → `[0xa]`