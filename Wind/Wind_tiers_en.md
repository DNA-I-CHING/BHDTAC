# Wind-Drift Patch Tier Table (ideal model `v += wind >> K`)

- Base file: `DFBHD.exe` (all tiers generated from it; each is standalone — pick one and replace the game exe)
- Model: each frame adds `wind_vector >> K` (16.16 fixed-point) to the bullet's horizontal velocity; applies to standard ballistic ammo only — `useownmove` thrown items are not affected
- Reference: at full 45 kph wind the wind vector ≈ 737/frame

| Tier | File | Name | Gain | Accel / frame | % of gravity | Trajectory-plane tilt | Intended use |
|---|---|---|---|---|---|---|---|
| K0 | DFBHD_wind_K0.exe | Tornado | wind/1 | 737 | 441% | 77.2° | Gags / extreme demos |
| K1 | DFBHD_wind_K1.exe | Storm | wind/2 | 368 | 220% | 65.6° | Bullets fly nearly sideways |
| K2 | DFBHD_wind_K2.exe | Gale | wind/4 | 184 | 110% | 47.8° | Over-the-top gameplay |
| K3 | DFBHD_wind_K3.exe | High wind | wind/8 | 92 | 55% | 28.9° | Heavy interference, big lead needed |
| K4 | DFBHD_wind_K4.exe | Strong | wind/16 | 46 | 27.5% | 15.4° | Clearly visible drift |
| K5 | DFBHD_wind_K5.exe | Medium-strong | wind/32 | 23 | 13.8% | 7.8° | In-game tested |
| K6 | DFBHD_wind_K6.exe | Medium | wind/64 | 11 | 6.6% | 3.8° | In-game tested |
| K7 | DFBHD_wind_K7.exe | Mild | wind/128 | 5 | 3.0% | 1.7° | In-game tested, noticeable only at long range |
| K8 | DFBHD_wind_K8.exe | Faint | wind/256 | 2 | 1.2% | 0.7° | Easter-egg level |

## DIY tuning (no need to regenerate files)

In any of these exes, edit these two bytes to switch between K = 0..31 (they must match):

- File offset `0x21001E` (X-axis `sar` immediate)
- File offset `0x210029` (Y-axis `sar` immediate)

Note: x86 masks shift counts with `&31`, so values above 31 wrap (e.g. 37 ≡ 5).

## Notes

- Tilt angle θ = atan(wind accel / gravity 167), i.e. the sideways lean of the trajectory plane relative to the sight line; maximal when the wind is perpendicular to the firing direction
- The ideal model has no lateral velocity cap (drift grows as t² forever); for saturating behavior use the relaxation build `DFBHD_P_wind_real.exe`
- Always back up the original exe before replacing it
