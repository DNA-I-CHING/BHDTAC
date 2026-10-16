# JointOps Medpack Self-Heal: Analysis & Patch Report

> Goal: make the medpack ammo heal the thrower as well (vanilla behavior heals teammates only).
> Target: `jointops.exe` (32-bit PE, ImageBase 0x400000, 4612096 bytes, original MD5 `CB19DCAAFEFF25D5518A49EC9AFAD420`).
> Method: local static disassembly with capstone + byte-level forensics (for every section, `file_offset = VA − 0x400000`).
> Patch: 2-byte NOP. No new code, no file-size change.

---

## 1. Medpack Mechanics

In `ammo.def`, medpack is an "instant killzone" ammo carrying the `instantkillzone` flag (bit 0x400) with `kztype = rounds_kz_Medic` (enum value 3):

- Ammo flag dword lives at AMMO record +0x00; `instantkillzone = 0x400`.
- `kztype` lives at AMMO record +0x2C (word); kztype enum table @0x8133E0: null=0 / Standard=2 / **Medic=3** / RadiusBlast=4 / C4=5 / Bullets=6 / Slash=7.
- Killzone parameters: kz_pieslice=+0x30, kz_minradius=+0x34, kz_maxradius=+0x38 (medpack radius = 2).

It has nothing to do with the powerup pickup chain — the heal is resolved by the killzone at the moment the projectile lands.

## 2. Full Call Chain (statically verified)

```
Ammo impact handler
  0x4ec1ed  test dword[ammo_record], 0x400     ; instantkillzone flag
  0x4ec20e  call 0x4e83c0                       ; enqueue (8 args)
        |
0x4e83c0  instant-killzone event queue pusher
  Queue: 0x40 entries x 0x34 bytes, count dword @0xB7C680, base @0xB7C688
  Entry fields: +0x00..0x08 landing position / +0x18 = kztype
                / +0x1C = AMMO record pointer / +0x20 = thrower player object
                / +0x28 = word
        |
0x4ead80  queue processor (consumed each frame)
  0x4eadb7  mov ecx, [esi+0x18] ; sub ecx,1 ; jump table @0x4EB8CC (index = kztype-1)
  Table: kztype 1->0x4eae0c / 2->0x4eadcd / 3->0x4eaddd / 4->0x4eae3c / 5..7->0x4eadcd
  Medic (kztype=3) -> case 0x4eaddd -> handler ptr [esp+0x24] = 0x4E6790
        |
0x4eaf00  player iteration loop (player table 0xA892E0/0xA892E4/0xA892E8)
  Per-player filtering: radius / angle (pieslice) / dead flag / team
  0x4eb078  cmp kztype,3 / je -> Medic PASSES the owner at loop level (no exclusion here)
  0x4eb312  call dword[esp+0x34]                 ; handler(edi = player, esi = queue entry)
        |
0x4e6790  Medic effect handler (used ONLY by kztype=3)
  0x4e67a3  mov eax, [edi+0x20]                  ; queue entry +0x20 = thrower player object
  0x4e67a6  cmp esi, eax                         ; current player == thrower?
  0x4e67a8  je  0x4e680d                         ; * SELF-EXCLUSION: skip healing if equal
  ...
  0x4e67b7  cmp team (+0x162)                    ; team check
  0x4e67e3  call 0x43b8a0 / HP compare / call 0x50de30(thrower, player)   ; heal applied
  0x4e67d6  call 0x517cd0(thrower, player)                                 ; revive
```

**Conclusion**: the self-exclusion is not in the iteration loop (the loop actually lets the owner through for Medic) — it is a single hard-coded `cmp/je` at the top of the Medic handler `0x4E6790`.

## 3. The Patch

| Item | Value |
|---|---|
| File offset | `0xE67A8` (VA 0x4E67A8) |
| Original bytes | `74 63` (`je 0x4e680d`) |
| Patched bytes | `90 90` (NOP x2) |
| Total change | 2 bytes in the whole file |
| File size | 4612096 (unchanged) |
| Patched MD5 | `39C22F7566F2EE5CC1DC3AECED9926C3` |
| Original MD5 | `CB19DCAAFEFF25D5518A49EC9AFAD420` |

After the NOP, execution falls through from `0x4e67a8` into `0x4e67aa` (`mov ecx,2; test byte[eax+0x24],cl`) and continues through the team check (owner vs. self always matches), the HP comparison, and the heal call `0x50de30` — the logic remains fully coherent.

**Blast radius**: `0x4E6790` is dispatched only for kztype=Medic. Satchel / C4 / Standard killzones use the `0x4E6820` handler and are completely unaffected.


## 4. Key Address Cheat Sheet

| Address | Meaning |
|---|---|
| 0x4EC1ED | `test [ammo],0x400` in impact handler (instantkillzone check) |
| 0x4EC20E | enqueue call site |
| 0x4E83C0 | instant-killzone enqueue function (queue base 0xB7C688, count 0xB7C680) |
| 0x4EAD80 | queue processor (dispatches by kztype) |
| 0x4EB8CC | kztype -> case jump table (index = kztype − 1) |
| 0x4EAF00 | player iteration loop (radius/angle/team filters) |
| 0x4EB312 | handler call site `call [esp+0x34]` |
| **0x4E6790** | **Medic handler (location of the self-exclusion)** |
| **0x4E67A8** | **patch site `74 63` -> `90 90`** |
| 0x50DE30 | heal application (thrower, player) |
| 0x517CD0 | revive (thrower, player) |
| 0x4E6820 | damage killzone handler (unaffected) |
| 0x8133E0 | kztype enum table |
| 0x813500 | ammo flag name table |
