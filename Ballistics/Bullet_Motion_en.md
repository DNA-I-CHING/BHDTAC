# Original Bullet Motion Mechanics in DF:BHD — Reverse-Engineering Report

- Target: `DFBHD_LAAM_base.exe` (ballistics code byte-identical to v1.5.0.5; all anchors portable)
- Method: capstone static disassembly + string anchors + SYSDUMP cross-validation
- Date: 2026-10-21

---

## 1. Overview

Bullet motion is a **per-frame Euler-integrated vacuum parabola**:

```
each frame:  pos += v
             v.z += -167        (gravity, 16.16 fixed-point)
             v = (v+wind)*drag - wind   (only when drag != 1.0)
             clamp v.z >= -16384
             terrain / hit / killzone checks
```

No horizontal deceleration, no wind drift (for default ammo), no mass effect. Every "physical" quantity is a hardcoded immediate, independent of ammo data.

Numeric representation: everything is **16.16 fixed-point** (1.0 unit = 65536); the gravity step is `-167/65536 ≈ -0.00255 units/frame`.

## 2. Data structure: ammo def record (items.def, stride 1976 bytes)

Parser at `0x4106xx`; keyword → field mapping (all confirmed by disassembly):

| def keyword | record offset | notes |
|---|---|---|
| (flag word) | `+0x00` | includes `nogravity`=bit 0x400, in-water=bit 0x100000, etc. |
| `max_age` | `+0x08` | lifetime in frames |
| `arm_age` | `+0x0C` | fuse arming distance/time |
| `velocity` | `+0x18` | muzzle velocity (× direction vector into instance vx/vy/vz) |
| (drag) | `+0x1C` | velocity decay coefficient, default `0x10000` = 1.0 |
| `bullet_mass` | `+0x20` | **parsed but never consumed — a dead field** |
| `ai_launch` | `+0x50` | AI firing behavior |
| `ai_launcheffect` | `+0x54` | AI muzzle effect |

The whole keyword block lives at `0x61FBD8~0x620078`: `shotgun / noage / useownmove / ownerimmune / instantkillzone / hasitem / nogravity / nocollide / nosmoke / forcetracer / silenced / shrapnel / muzzle1 / muzzle2 / velocity / bullet_mass ...`

## 3. The per-frame mover: `0x491B00`

### 3.1 Position integration
Plain Euler: `pos += v` each frame; v stored at instance `+0x6C/70/74`.

### 3.2 Gravity block `0x492866`

```
0x492866  mov  eax,[ebx+0xd8]     ; flags
0x49286C  test ah,4               ; nogravity?
0x49286F  jne  0x492893           ; set -> skip gravity
0x492871  test eax,0x100000       ; already in water?
0x492878  cmp  ecx,[0xb63374]     ; water surface height
0x492880  add  [ebx+0x74], -20    ; underwater: weak gravity
0x492888  add  [ebx+0x74], -167   ; airborne: standard gravity
0x492893  ...                     ; terminal-velocity clamp -16384
```

Gravity is a **per-frame constant** — independent of ammo mass, caliber or speed.

### 3.3 Drag / wind function `0x491930` (called at `0x492894`)

```
v = (v + wind) * drag - wind      ; velocity asymptotically relaxes toward wind vector
```

- The entry begins with `cmp [ecx+0x1C], 0x10000 / je ret`: **for drag = 1.0 (every default ammo type) the whole function is a no-op** — the root cause of "wind only affects particles, never bullets" in the original game.
- Global wind vector: `0xE19DC0/DC4/DC8` (x/y/z), written by the weather system (`0x5370E0`) from wind speed (kph, `0x715798`) × sin/cos tables in 16.16 fixed-point; z is always 0.
- Only special ammo with drag ≠ 1.0 (e.g. rockets, `0x3E7F`) actually "feels" the wind.

### 3.4 Mover dispatch architecture

`0x491CB8` tests the def `useownmove` flag → if set, control goes to a **custom mover** at `[obj+0x224]`. Grenades, demo packs, claymores, soldiers and vehicles each have their own mover, and **the gravity constant is duplicated, hardcoded, inside every mover** — 20 sites across the exe (-167×13, -334×3, -55×3, -20×1, etc.; see the Gravity report for the full table).

## 4. Physical essence

- Trajectory: `y(x) = (g/2v₀²)·x²` with g = 167/65536 per frame — a textbook parabola;
- Horizontal velocity never decays (with drag = 1 there is no resistance term at all);
- Mass never appears (F = ma cancels out; every bullet shares one gravity step);
- No lift, no Magnus, no Coriolis, no terminal-velocity limit on horizontal motion.

In short: **engine ballistics = vacuum + constant gravity + an optional medium-drag hook that is disabled by default**.

## 5. Comparison with jointops.exe

| | DF:BHD | JO |
|---|---|---|
| Main ballistics mover | `0x491B00` | `0x4ADEF0` |
| Velocity fields | +0x6C/70/74 | +0x98/9C/A0 |
| Gravity | -167/frame | -167/frame (identical) |
| Wind hookup | inside drag fn, but no-ops by default | main mover never reads wind at all (wind only enters the relative-drag block `0x4E60C7` and visual paths) |
| Wind globals | `0xE19DC0/4` (kph×16.38 fixed) | `0x2C059E4/E8` (≈ raw kph) |

## 6. Verified modifiable points

| Goal | Location | Technique |
|---|---|---|
| Change gravity | 20 sites `add [inst+0x74], imm32` | edit the immediate (file offset = VA − 0x400000) |
| Global zero-g | `0x49286F` `75→EB` | force the jmp |
| Bullets feel wind | hook `0x491930` entry → code cave in `_TEXT` at VA `0x610010` (4KB zero-filled RWX section) | inject `v += wind>>K` (ideal) or `v += (wind-v)>>K` (relaxation) |
| Make mass matter | read `[ecx+0x20]` in the same cave and scale gravity | a few extra imul/sar instructions |

## 7. Conclusion

Original bullet motion is a deliberately simplified "predictable parabola": the designers left a medium/wind hook via the drag field but never enabled it for default ammo, and `bullet_mass` is a completely dead field. All engine physics happens at the **instance root-position level** (per-frame fixed-point integration); there is no skeletal or rigid-body solver — which is exactly why ragdoll cannot be achieved through data files, while wind/gravity patches need only one immediate edit or a ten-instruction hook.
