# Wind System & Bullet Wind-Drift Patch — *Delta Force: Black Hawk Down* Analysis Report

- **Target**: `DFBHD_P.exe` (v1.5.0.5, 32-bit PE, ImageBase `0x400000`, 2,547,712 bytes)
- **Method**: static analysis (python + capstone + pefile) + in-game verification
- **Date**: 2026-10-20
- **Bottom line**: the engine has a complete weather/wind system, and the wind vector is **already wired into the bullet drag function** — but default ammo always has drag = 1.0, which makes that function return immediately. Bullets being "immune to wind" is by design, not an omission. A 5-byte entry jump plus a 10-instruction injection into the unused `_TEXT` section gives every normal ballistic round real wind drift. Verified in-game.

---

## 1. Address convention

In `.text`: `VA = file_offset + 0x400000`. The code cave lives in the `_TEXT` section: VA `0x610010` = file offset `0x210010` (RawSize 0x1000, VirtualSize only 0xC, zero-filled tail, flags `0xE0000020` = RWX).

## 2. Wind system forensics

### 2.1 Weather master variables

| Variable | VA | Meaning |
|---|---|---|
| wind speed | `0x715798` | integer kph (UI value; max 45 clamped on weather/save side) |
| wind bearing | `0x715794` | degrees |
| weather mode | `0x9F214C` / `0x9F21DC` | 0=custom, 1=no wind, 2=random wind |

Weather update code (`0x4B9AA7` / `0x4B9F0B` / `0x4BA2DF`) reads speed/bearing then `call 0x5370E0` (setter); mode 2 calls `0x5371D0`: bearing = `rand*360>>16`, speed = `rand>>11`.

### 2.2 Wind-vector globals (core)

| Variable | VA | Meaning |
|---|---|---|
| wind_x | `0xE19DC0` | 16.16 fixed point |
| wind_y | `0xE19DC4` | 16.16 fixed point |
| wind_z | `0xE19DC8` | always 0 |
| half-wind copies | `0xE19DCC` / `0xE19DD0` | wind_x/y ÷ 2 |

Conversion in setter `0x5370E0` (file `0x1370E0`): `0x537177 call 0x55E6E0` (1024-segment interpolated sin/cos table, pointer `[0x654CF4]`, angle segment via `>>22`), then `0x537185: imul …; shrd eax,edx,22; mov [0xE19DC0],eax` — i.e. **wind = speed × trig(fixed) >> 22**, decomposed to x/y by cos/sin.

### 2.3 Particle side (why wind "only affects smoke/dust")

- Particle integration loop `0x536F90` (caller `0x4B4B8E`): for the particle array at `0xE14DB4` (stride `0x14`) it performs **per-frame** `[pos-4] += wind_x; [pos] += wind_y` (vertical term -2048/-20480 by weather type). Particles get the **full** wind vector as displacement — visibly drifting smoke/dust/flames.
- Visual path `0x55C843`: reads `0xE19DC0/4/8` → `call 0x55D5D0` (fild → float ×1/65536) → `fmul [0x611570]=62.0`.

## 3. Bullet side: root cause of "no wind"

The bullet mover `0x491B00` calls the drag function `0x491930` every frame at `0x492894` (`push ebx; call`, ebx = bullet instance). Fully disassembled logic (0x491930–0x4919F4):

```
0x491934  mov  ecx,[ebp+8]          ; ecx = bullet instance
0x491937  mov  edx,[ecx+0x16c]      ; ammo type index → table [0x683ee8]
0x49194D  mov  eax,[edx+eax*4+0x1c] ; drag = def+0x1C (16.16 fixed)
0x491951  cmp  eax,0x10000          ; ★ default ammo: drag == 1.0
0x491959  je   0x491a2e             ; ★ returns immediately → zero wind effect
0x49195F  mov  eax,[ecx+0x10]       ; Z position
0x491962  cmp  eax,[0xb63374]       ; waterline
0x49196E  ...                       ; v = (v + wind) → v = v*drag>>16 → v = v - wind
```

The engine's design treats wind as **relative-medium drag**: velocity asymptotically approaches wind speed, and only when `drag ≠ 1.0` above the waterline. All default ammo has `drag = 0x10000`, so the function no-ops at `0x491959` — **root cause confirmed**. Velocity fields: instance `+0x6C`=vx, `+0x70`=vy, `+0x74`=vz (gravity only touches vz; see the gravity report).

## 4. Patch design

### 4.1 Cave choice

No ≥48-byte gap in `.text`; the `_TEXT` section (VA `0x610000`, RawSize 0x1000, VirtualSize only 0xC, RWX) is zero from `0x610010` onward and executable → ideal cave.

### 4.2 Injection (39 bytes changed in total)

**Hook** (file `0x91930`, 5 bytes):

```
55 8B EC 51 8B  →  E9 DB E6 17 00      ; jmp 0x610010
```

**Cave** (file `0x210010`, 34 bytes):

```
0x610010  push ebp / mov ebp,esp / push ecx / mov ecx,[ebp+8]   ; replay overwritten prologue
0x610017  mov  eax,[0xE19DC0]
0x61001C  sar  eax,5                    ; wind scale (see 4.3)
0x61001F  add  [ecx+0x6C],eax           ; vx += wind_x >> 5
0x610022  mov  eax,[0xE19DC4]
0x610027  sar  eax,5
0x61002A  add  [ecx+0x70],eax           ; vy += wind_y >> 5
0x61002D  jmp  0x491937                 ; resume original flow (drag check untouched)
```

Semantics: converts wind from "asymptotic drag" into a **per-frame wind acceleration** for every normal ballistic round (including `nogravity` ammo, which shares the `0x492893` path); drag≠1.0 ammo keeps its original medium logic (our term is added before it).

### 4.3 Tuning

Edit file offsets **`0x21001D`** and **`0x210028`** (the `sar` immediates; keep both equal):

| Value | Wind | Feel |
|---|---|---|
| `03` | /8 | gale, visibly curved trajectories |
| `04` | /16 | strong |
| **`05`** | /32 | current release ("clearly noticeable" in-game) |
| `06` | /64 | gentle |
| `09` | /512 | first build — "present but weak" in-game |

### 4.4 Scope

- ✅ All ammo flying through the normal ballistic mover `0x491B00`.
- ❌ `useownmove` projectiles (grenades / demo packs / claymores) run their own movers via `[obj+0x224]` and never call `0x491930`; covering them requires per-mover hooks at the 12 group-B sites listed in the gravity report.
- ❌ Soldiers / corpses (not needed).

## 5. Field test log

1. `sar 9` build: wind drift observable but weak → hook path confirmed correct.
2. `sar 5` build (×16): clearly noticeable drift, matches the requested boost.
3. Integrity: exactly 39 bytes differ from stock; no self-integrity check observed.

## 6. Related documents

- Full gravity-site table & mover architecture: `../Gravity/Gravity_Analysis_en.md`
- The wind call (`0x492894`) sits right after the gravity block (`0x49284C–0x492890`) in the same mover; the two reports together form the complete ballistics-physics picture.
