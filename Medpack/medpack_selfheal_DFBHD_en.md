# Delta Force: Black Hawk Down (DFBHD.exe) Medpack Self-Exclusion Analysis & Patch Report

> Goal: let the medpack heal its own thrower as well (vanilla heals teammates only).
> Target: `DFBHD.exe` (Black Hawk Down main binary, same engine as JointOps; 32-bit PE, ImageBase 0x400000, 2547712 bytes, original MD5 `D6F51AD03CA62F040586B8B5E3CA8181`).
> Method: local capstone static disassembly + byte-level forensics (file_offset = VA − 0x400000 holds for every section).
> Patch: 2-byte NOP — no added code, no size change.

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
    0x4936d6  call 0x418ec0(8, [thrower+0x244])   ; thrower validity check
    0x4936eb  mov dword [ebp-0x14], 0x492EE0      ; ★ load Medic handler
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

## 3. The Patch

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

## 4. Address Quick Reference

| Address | Meaning |
|---|---|
| 0x493670 | Instant-killzone queue processor (dispatch by kztype) |
| 0x9D71C8 | Queue entry base (count dword [0x96ED50]) |
| 0x4940EC | kztype→case jump table (index = kztype itself) |
| 0x4936C8 | Medic case (conditional handler load) |
| **0x492EE0** | **Medic handler (self-exclusion lives here)** |
| **0x492EF9** | **Patch point `74 68`→`90 90`** |
| 0x4AF0D0 | Heal apply (player, thrower) |
| 0x4AEE40 | Revive downed (player, thrower) |
| 0x441B90 | Player max-HP query |
| 0x492F70 | Damage killzone handler (unaffected) |
| 0x9F2190 | Global effect-enable switch (must be non-zero) |
| 0x61FD48 | `rounds_kz_Medic` string |

> Field-offset deltas vs. the JointOps variant: item record ptr player+0x24 (JO: +0x20), itemtype record+0x38 (JO: +0x5c), team field +0xF6 (JO: +0x162), HP field +0xE2 (JO: +0x11e), flag byte +0x20 bit4 (JO: +0x24 bit2). Jump-table indexing also differs: DFBHD uses kztype directly, JointOps uses kztype−1.
