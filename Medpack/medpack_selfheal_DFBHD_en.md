# Delta Force: Black Hawk Down (DFBHD.exe) Medpack Self-Heal & All-Class Healing Analysis & Patch Report

> Goal 1: let the medpack heal its own thrower as well (vanilla heals teammates only).
> Goal 2 (`--allclasses` / v3 patch): in vanilla only a Medic (class id 6/0xA) can heal with medpacks — cqb/sniper/gunner and single player produce no healing. After the patch, ANY class in ANY mode heals.
> Target: `DFBHD.exe` (Black Hawk Down main binary, same engine as JointOps; 32-bit PE, ImageBase 0x400000, 2547712 bytes, original MD5 `D6F51AD03CA62F040586B8B5E3CA8181`).
> Method: local capstone static disassembly + byte-level forensics (file_offset = VA − 0x400000 holds for every section).
> Patch: in-place 2-byte edits only (NOP or je→jmp) — no added code, no size change.

---

## 1. Medpack Mechanism Background

Same as JointOps: the medpack is an "instant killzone" round carrying the `instantkillzone` flag with `kztype = rounds_kz_Medic` (enum value 3). Healing is resolved at the moment the projectile hits, via killzone settlement — completely unrelated to the powerup pickup chain.

Engine strings present in the binary confirm the shared engine and mechanism:

| String | VA |
|---|---|
| `rounds_kz_Medic` | 0x61FD48 |
| `instantkillzone` | 0x61FBC0 |
| `ownerimmune` | 0x61FBB4 |

## 2. Full Call Chain (statically verified)

```
Instant-killzone queue processor
  0x493670  queue base 0x9D71C8, count dword [0x96ED50]
  Entry fields: +0x18 = kztype / +0x1C = AMMO record ptr / +0x20 = thrower player object
  0x4936ad  mov ecx, [esi+0x18]              ; kztype directly
  0x4936b9  jmp dword [ecx*4 + 0x4940EC]     ; jump table (index = kztype itself)
  Table: 0→0x4936F4 / 1→0x4936FC / 2→0x4936C0 / 3→0x4936C8
         / 4→0x49372C / 5,6,7→0x4936C0
  Medic (kztype=3) → case 0x4936C8
    0x4936d6  call 0x418ec0([thrower+0x244] class byte, 8) ; class-ability bit lookup (only Medic has bit 8)
    0x4936e0  je  0x4936f4                          ; ★ class gate 1: non-Medic → handler never loaded
    0x4936eb  mov dword [ebp-0x14], 0x492EE0        ; load Medic handler
        ↓
  Per-player iteration, then handler(esi = player, edi = queue entry)
        ↓
0x492EE0  Medic effect handler (loaded only for kztype=3)
  0x492ee7  mov eax, [esi+0x24]              ; player's item record
  0x492eea  cmp dword [eax+0x38], 3          ; itemtype == 3
  0x492ef4  mov eax, [edi+0x20]              ; queue entry +0x20 = thrower player object
  0x492ef7  cmp esi, eax                     ; current player == thrower?
  0x492ef9  je  0x492f63                     ; ★ self-exclusion: skip healing if equal
  0x492f0a  cmp team field (+0xF6)           ; teammate check
  0x492f3a  call 0x441b90 / compare HP (+0xE2) / call 0x4AF0D0(player, thrower)   ; heal apply
  0x492f2d  call 0x4AEE40(player, thrower)                                       ; revive downed
```

**Conclusion**: structurally identical to JointOps — the self-exclusion is hardcoded as a single `cmp/je` at the top of Medic handler `0x492EE0`, not in the player iteration loop. Locating method: the exact byte signature of the JointOps gate, `8b 47 20 3b f0 74`, produced a **single hit in the whole file at 0x492EF4**; the surrounding disassembly was then verified instruction-by-instruction against the JointOps template.

## 3. Self-Heal Patch (single gate)

| Item | Value |
|---|---|
| File offset | `0x92EF9` (VA 0x492EF9) |
| Original bytes | `74 68` (`je 0x492f63`) |
| Patched bytes | `90 90` (NOP ×2) |
| Total change | 2 bytes in the whole file |
| File size | 2547712 (unchanged) |
| Patched MD5 | `AC1CC9518F1651FF1BAF31044D497CBB` |
| Original MD5 | `D6F51AD03CA62F040586B8B5E3CA8181` |

After the NOP, execution falls from `0x492ef9` into `0x492efb` (reads the thrower's flag byte) and continues through the teammate check (comparing the thrower against itself always matches), the HP comparison, and the heal application at `0x4AF0D0`. The logic path remains complete.

**Blast radius**: `0x492EE0` is loaded only from the kztype=3 (Medic) branch of the jump table. Standard/RadiusBlast/C4/Bullets/Slash killzones go through the damage handler `0x492F70` or other cases and are entirely unaffected.

## 4. Class Restriction Analysis (three class gates, statically verified)

In vanilla only a Medic thrower's medpack heals. The restriction lives on **three independent gates**; NOPing only gate 1 is not enough — the heal-apply and revive functions each contain another gate:

### Gate 1: dispatch gate (handler load condition) — 0x4936E0

```
0x4936c8  mov eax, [esi+0x20]                  ; esi=queue entry, +0x20=thrower player object
0x4936cd  mov cl, byte [eax+0x244]             ; class id byte
0x4936d3  push 8                               ; ability bit = 8 (medic heal)
0x4936d5  push ecx
0x4936d6  call 0x418ec0                        ; class-ability bit lookup
0x4936de  test eax, eax
0x4936e0  je  0x4936f4                         ; ★ returns 0 → handler slot cleared, never loaded
0x4936eb  mov dword [ebp-0x14], 0x492EE0       ; load Medic handler
```

- `0x418ec0(id, bit)` looks up the class ability table: base 0x715b80, entry stride 0x84, mask field record+0x28; only the Medic entry carries bit 8.
- **Single player root cause**: the table pointer `[0x715b48]` is NULL in single player, so the lookup always returns 0 → gate 1 always fails → the Medic handler is never loaded.

### Gate 2: heal-apply gate — inside 0x4AF0D0 (patch point 0x4AF13D)

Even after the handler runs, the heal-apply function `0x4AF0D0(player, thrower)` re-checks the **thrower's class**:

```
Scan player record table [0x9ED600] (stride 0xAF33C, record+0x18=player object ptr, +0x68c4=slot valid)
Once the thrower's record ebx is found:
0x4af134  mov eax, [ebx+0x68A0]                ; thrower class id (record field)
0x4af13a  cmp eax, 6
0x4af13d  je  0x4af148                         ; medic(6) → pass
0x4af13f  cmp eax, 0xA
0x4af142  jne 0x4af20c                         ; ★ class not 6/0xA → return, no healing
```

Patch: at `0x4AF13D` change `74` (je) → `EB` (jmp), so every class takes the pass branch `0x4af148`.

### Gate 3: revive gate — inside 0x4AEE40 (patch point 0x4AEEF3)

The downed-revive function `0x4AEE40` has the same check (reading the thrower object field directly):

```
0x4aeeea  mov ecx, [esi+0x244]                 ; thrower class id byte
0x4aeef0  cmp ecx, 6
0x4aeef3  je  0x4aeefe                         ; medic(6) → pass
0x4aeef5  cmp ecx, 0xA
0x4aeef8  jne 0x4af0bf                         ; ★ class not 6/0xA → return, no revive
```

Patch: same `74`→`EB` at `0x4AEEF3`.

> Note: `0x418ec0` has 6 call sites in the file; the other three (0x4aa034 / 0x507a25 / 0x50bada) are ammo-crate pickup restrictions, unrelated to killzone healing and untouched by this patch.

## 5. All-Class Patch (v3, field-tested working)

On top of the self-heal patch (section 3), the three class gates are bypassed — 4 in-place 2-byte edits total (each je→jmp changes only 1 physical byte, so the real diff is 6 bytes):

| # | File offset | VA | Original | Patched | Effect |
|---|---|---|---|---|---|
| 1 | `0x92EF9` | 0x492EF9 | `74 68` | `90 90` | self-heal: NOP the thrower==self skip |
| 2 | `0x936E0` | 0x4936E0 | `74 12` | `90 90` | gate 1: dispatch loads handler unconditionally |
| 3 | `0xAF13D` | 0x4AF13D | `74 09` | `EB 09` | gate 2: heal-apply passes all classes |
| 4 | `0xAEEF3` | 0x4AEEF3 | `74 09` | `EB 09` | gate 3: revive passes all classes |

| Item | Value |
|---|---|
| Patch file | `DFBHD_medpack_v3.exe` |
| Total change | 6 bytes |
| File size | 2547712 (unchanged) |
| Patched MD5 | `1E3DDF254828A04F6610BD3C4A57ADBA` |
| Original MD5 | `D6F51AD03CA62F040586B8B5E3CA8181` |

**Effect**: medpacks thrown by any class (cqb/sniper/gunner/engineer/medic) in any mode (including single player) heal both self and teammates; damage killzones (satchel/C4 etc.) are unaffected.

**How to build**: `python patch_medpack_selfheal.py DFBHD.exe DFBHD_medpack_v3.exe --allclasses` (the script auto-detects JointOps and applies only the self-heal gate there; idempotent — `--allclasses` can be layered on an existing self-heal build).

## 6. Address Quick Reference

| Address | Meaning |
|---|---|
| 0x493670 | Instant-killzone queue processor (dispatch by kztype) |
| 0x9D71C8 | Queue entry base (count dword [0x96ED50]) |
| 0x4940EC | kztype→case jump table (index = kztype itself) |
| 0x4936C8 | Medic case (conditional handler load) |
| 0x418EC0 | Class-ability bit lookup (table base 0x715B80 stride 0x84; table ptr [0x715B48] NULL in single player) |
| **0x492EE0** | **Medic handler (self-exclusion lives here)** |
| **0x492EF9** | **Patch point 1 self-heal `74 68`→`90 90`** |
| **0x4936E0** | **Patch point 2 dispatch class gate `74 12`→`90 90`** |
| 0x4AF0D0 | Heal apply (player, thrower), contains class gate |
| **0x4AF13D** | **Patch point 3 heal-apply class gate `74`→`EB`** |
| 0x4AEE40 | Revive downed (player, thrower), contains class gate |
| **0x4AEEF3** | **Patch point 4 revive class gate `74`→`EB`** |
| 0x9ED600 | Player record table base (stride 0xAF33C, record+0x68A0 = class id) |
| 0x441B90 | Player max-HP query |
| 0x492F70 | Damage killzone handler (unaffected) |
| 0x9F2190 | Global effect-enable switch (must be non-zero) |
| 0x61FD48 | `rounds_kz_Medic` string |

> Field-offset deltas vs. the JointOps variant: item record ptr player+0x24 (JO: +0x20), itemtype record+0x38 (JO: +0x5c), team field +0xF6 (JO: +0x162), HP field +0xE2 (JO: +0x11e), flag byte +0x20 bit4 (JO: +0x24 bit2). Jump-table indexing also differs: DFBHD uses kztype directly, JointOps uses kztype−1.
