# DFBHD Dismember Crash Analysis & Binary Patch Report

Target: *Delta Force: Black Hawk Down*
Executable: `DFBHD.exe` V1.5.0.5 (2,547,712 bytes, x86 PE, ImageBase `0x400000`)
Tooling: REA (Ghidra 12.1.4 provider) + manual disassembly of crash dumps

---

## 1. Background

Removing the `nodismember` attribute from an organic unit's entry in `items.def`
enables the dismemberment effect (per ITEM.TXT: `/nodismember /organic can be dismembered`).
However, the feature shipped half-finished: once the attribute is removed, the game
crashes with Access Violations at multiple sites that **lack NULL-pointer checks**.

This report documents the full root-cause analysis of two real crashes and the
corresponding binary patches (Patch 1 + Patch 2). The combined result is
`DFBHD_patched.exe`.

### Offset conversion

In the PE header, `.text` has `VirtualAddress == PointerToRawData == 0x1000`, therefore:

```
file offset = VA − 0x400000
```

### items.def flag parsing (confirmed)

- Parser: `FUN_00464350` (0x464350–0x466A46)
- At `0x465EED` it references the string `"NoDismember"` (VA `0x63AD74`);
  a match sets `def+0x34 |= 0x8000000`
- def record stride: `0x7B8`; `def+0x20` = 8-byte name string; `def+0x38` = unit_type integer

### Runtime object layout (confirmed)

| Offset | Meaning |
|---|---|
| `obj+4` | → T (model record) |
| `T+0x20` bit0 | dismember gating flag (mirrors `def+0x34` bit `0x8000000`) |
| `T+0x38` | → M (part/dismember sub-record, **determined by the model file, not items.def**; may be NULL) |
| `M+0x180` | container back-pointer |
| `M+0x13C` | state field compared against `0x7E` (126) |
| `obj+0x24` | → def record |

> Key conclusion: whether the game crashes depends on **whether the model carries a
> part record (`T+0x38 != NULL`)**, not on what items.def says. Non-organic units never
> had `nodismember` in the first place; only organic units with the attribute removed
> enter these fragile code paths.

---

## 2. Crash 1: attachment-removal routine missing a NULL check

### Dump signature

```
Access violation at 0040DA6Ah, reading 0000013Ch
EAX = 00000000h
```

Faulting address = `EAX + 0x13C` with EAX = 0 → classic `[NULL+0x13C]` read.

### Localization

The crash sits in `FUN_0040d9f0` (0x40D9F0–0x40DAE7, attachment-removal routine),
called from `FUN_0040d880` (destruction loop; the stack return address `0x40d8cb` matches).
Core Ghidra pseudocode:

```c
iVar2 = *(int *)(iVar5 + 4);          // T = obj+4
if (((iVar2 != 0) && ((*(byte *)(iVar2 + 0x20) & 1) == 0)) &&   // nodismember not set
    (*(int *)(*(int *)(iVar2 + 0x38) + 0x13c) == 0x7e)) {       // ← dereferences [T+0x38] without NULL check!
    bVar3 = true;
}
```

Faulting instruction (at 0x40DA6A): `83 B8 3C 01 00 00 7E` =
`cmp dword ptr [eax+0x13C], 0x7E`, where EAX = `[T+0x38]` = NULL.

### Patch 1

Overwrite 5 bytes at the hook site `0x40DA6A` with `E9 rel32` into a code cave.
The cave performs `test eax,eax / je` first, then re-executes the original `cmp`.

- **Hook**: raw `0x0DA6A` (VA `0x40DA6A`), original 5 bytes `83 B8 3C 01 00` → `E9 C3 6E 1D 00` (jumps to `0x5E4932`)
- **Cave**: raw `0x1E4932` (VA `0x5E4932`, inside a zero-filled gap at the end of `.text`), 28 bytes:

```
85 C0                       test eax, eax
74 13                       je   +0x13          ; NULL → skip the comparison
81 B8 3C 01 00 00 7E 00 00 00                   ; cmp dword [eax+0x13C], 0x7E
75 07                       jne  +7             ; not equal → original path resume
C7 45 F8 01 00 00 00        mov dword [ebp-8], 1
E9 2C 91 E2 FF              jmp  0x40DA7A       ; resume right after the original cmp
```

---

## 3. Crash 2: dismember-object spawn returns NULL, unchecked

Occurred after applying Patch 1.

### Dump signature

```
Access violation at 00402FC9h
Attempting to write from 00000104h
EAX = 00000000h, EBX = fffdf7ffh
```

Faulting address = `EAX + 0x104` with EAX = 0 → `[NULL+0x104]` write.
EBX = `fffdf7ff` = `~0x208` (inverted limb mask), consistent with the code semantics.

### Localization

The crash sits in the dismember-spawn block of `FUN_00402ca0` (0x402CA0–0x40301C,
death/damage handling):

```c
if ((((DAT_009f2190 != 0) && ((*(uint *)(param_1 + 0x20) & 1) == 0)) &&
    (iVar2 = *(int *)(iVar2 + 0x38), 0 < iVar2)) &&
   ((((*(uint *)(*(int *)(param_1 + 0x24) + 0x34) & 0x8000000) == 0 && ...
// after a switch builds the limb mask uVar6:
push esi
call FUN_0043c930        // dismember object spawn (cdecl), may return NULL
mov [eax+0x104], ~uVar6  // ← crash: return value never checked
```

Raw bytes at the crash site (matching the dump's code bytes):

```
56                       push esi
89 86 04 01 00 00        mov [esi+0x104], eax
e8 6b 99 03 00           call 0x43C930          ; ← 0x402FC0
33 c9                    xor ecx, ecx           ; ← 0x402FC5
f7 d3                    neg edx
89 98 04 01 00 00        mov [eax+0x104], ebx   ; ← 0x402FC9 crash
```

### Patch 2

Replace the 5-byte call at `0x402FC0` (`E8 6B 99 03 00`) with `E9 rel32` into a cave at `0x5E4972`:

- **Hook**: raw `0x002FC0` → `E9 AD 19 1E 00` (jumps to `0x5E4972`)
- **Cave**: raw `0x1E4972` (VA `0x5E4972`), 22 bytes:

```
E8 B9 7F E5 FF           call 0x43C930          ; original dismember spawn call
85 C0                    test eax, eax
74 05                    je   +5                ; NULL → take the skip path
E9 45 E6 E1 FF           jmp  0x402FC5          ; non-NULL → original resume (xor ecx,ecx)
83 C4 04                 add esp, 4             ; balance the pushed argument (cdecl: caller cleans)
E9 7D E6 E1 FF           jmp  0x403005          ; skip the whole init block, land on its tail
```

The skip path lands on the block tail `mov eax,[ebp+8]; test eax,eax; je...` (`0x403005`),
i.e. when the model has no part record the game simply **gives up spawning the dismember
object** — normal dismemberment is unaffected.

---

## 4. Patch summary

| Patch | Hook site (VA) | Original bytes | New bytes | Cave (VA) | Fixes |
|---|---|---|---|---|---|
| 1 | `0x40DA6A` | `83 B8 3C 01 00` | `E9 C3 6E 1D 00` | `0x5E4932` (28 B) | `FUN_0040d9f0` dereferences `[T+0x38]` unchecked → read `NULL+0x13C` |
| 2 | `0x402FC0` | `E8 6B 99 03 00` | `E9 AD 19 1E 00` | `0x5E4972` (22 B) | `FUN_00402ca0` ignores `FUN_0043c930` return → write `NULL+0x104` |

Code caves live in a 1742-byte zero-filled gap at the end of `.text` starting at `0x5E4932`.
No new section, no relocation-table edits; the rest of the exe is untouched.

Deliverable: `DFBHD_patched.exe` (Patch 1 + Patch 2 combined) — drop it into the game root
to replace the original exe.

### Verification (read-only check against the patched exe)

```
P1 hook 0x40DA6A -> cave 0x5E4932   ✓
P1 cave back     -> 0x40DA7A        ✓
P2 hook 0x402FC0 -> cave 0x5E4972   ✓
P2 call target   -> 0x43C930        ✓
P2 resume        -> 0x402FC5 (33 c9 f7 d3 89 98)  ✓ matches dump
P2 skip          -> 0x403005 (8b 45 08 85 c0 74 0a c7) ✓ matches dump
```

---

## 5. Known risks

Dismemberment is a half-finished feature. Roughly **70 sites** across the exe depend on the
same gating flag (pattern `test byte [r+0x20], 1`), so a third unchecked-NULL crash site
cannot be ruled out. If another crash occurs:

1. Keep the SYSDUMP.TXT;
2. Locate the faulting instruction via `file offset = EIP − 0x400000`;
3. Cross-check the surrounding code bytes from the dump;
4. Apply the same hook + cave NULL-check pattern as above.

New dumps plus reproduction details (map, unit, weapon) are welcome for further triage.
