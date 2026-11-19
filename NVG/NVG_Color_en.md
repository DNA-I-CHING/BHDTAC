# BHD Night Vision Goggles (NVG) Color Implementation Analysis

> Target: DFBHD.exe (Delta Force: Black Hawk Down)
> MD5: `d6f51ad03ca62f040586b8b5e3ca8181` · Image Base: `0x400000` · 6777 functions
> Tools: local Ghidra (decompilation/xrefs) + pefile (byte-level locating)
> Date: 2026-11-19
> Chinese version: [NVG_Color_zh.md](NVG_Color_zh.md)

---

## 1. Executive Summary

The NVG green look is **not a texture and not lighting** — it is a **ps.1.1 pixel shader source embedded as plain ASCII text** inside the exe, compiled at startup via D3DXAssembleShader and applied as a full-screen post-processing pass:

```
Scene pixel → luminance extraction (dp3) → × color gain → + color bias → green image
```

| Question | Answer |
|---|---|
| Where is the green defined | `def c1 / def c2` lines of the shader source text @ `0x64F8D4` |
| Who compiles it | `FUN_0052A9D0` (at D3D init) |
| Who applies it | `FUN_0052BDB0` (on-foot) / `FUN_0052C630` (in-vehicle) |
| Who toggles it | `FUN_00489CC0` input action handler, `case 0x33` (N key) |

---

## 2. Complete Trigger Chain

```
[Keybind table .data 0x628488, stride 0x64]
  N-key entry @0x629A04: id=0x33, key=0x4E, "!Night Vision", command "NVG"
        │ N pressed
        ▼
FUN_00489CC0 (input action handler, switch(action id))
  case 0x33:  DAT_0096C4BC = !DAT_0096C4BC      ← NVG active flag 0↔1
              FUN_004BE3A0(DAT_00A02028/2C)     ← on/off sound
        │
        ▼
FUN_004B7110 (main render function)
  if (DAT_0096C4BC != 0) → special-view branch
        │
        ▼
FUN_0052BDB0 (foot NVG render) / FUN_0052C630 (vehicle NVG render)
  With pixel shaders : bind DAT_00E049B0 (NVG shader), draw full-screen quad
  Without shaders    : fixed-function green vertex-color modulation (fallback)
```

Keybind entry layout (0x64 bytes/entry): `{id: dword, flags: 5 bytes, param: dword, key: dword, "!display": char[28], "command": char[45]}`. The table has no direct code references (pure default data); dispatch happens via the `id` field.

---

## 3. Core Address Map (Key Section)

### 3.1 The Color Itself — Shader Source Text @ `0x64F8D4`

```asm
ps.1.1
def c0, 0.50,  1.00,  0.50,  0.0   ; luminance weights (R,G,B) — for grayscale, not color
def c1, 0.20,  0.90,  0.20,  0.0   ; ★ color gain — main source of "green" (G=0.90)
def c2, 0.00,  0.20,  0.00,  0.0   ; ★ color bias — dark areas keep 0.2 green

tex t0                             ; sample scene texture
dp3     r0, t0, c0                 ; dot product = luminance extraction → grayscale
mul  r0, r0, c1                     ; multiply by color gain
add     r0, r0, c2                 ; add bias → green-tinted frame
```

Interpretation: `c1` decides "which color is brightest", `c2` decides "what hue shadows glow with". Stock: G gain 0.90 + G bias 0.20, R/B only 0.20/0.00 — classic night-vision green.

### 3.2 Color Constants (Fixed-Function Fallback Path)

On GPUs without pixel shaders, the fixed-function path approximates the same effect via **vertex-color modulation**:

| Address (VA) | Original | Meaning |
|---|---|---|
| `0x52BE16` | `0xFF408040` | Foot NVG · PS-path vertex tint (ARGB, A=FF opaque) |
| `0x52C7EA` | `0xFF408040` | Vehicle NVG · PS-path vertex tint |
| `0x52BE77` | `0xFF084808` | Foot · fixed-function dark level |
| `0x52C854` | `0xFF084808` | Vehicle · fixed-function dark level |
| `0x52BEBB` | `0xFF308030` | Foot · fixed-function standard brightness |
| `0x52BEB3` | `0xFF30FF30` | Foot · fixed-function bright level (NVG gain on) |

> Format: D3DCOLOR is laid out as `AARRGGBB`. The leading `FF` is Alpha=255 (fully opaque); the real RGB is the last 6 digits. E.g. `0xFF30FF30` = R:0x30, G:0xFF, B:0x30.

### 3.3 Function Addresses

| Address | Function | Purpose |
|---|---|---|
| `0x52A9D0` | `FUN_0052A9D0` | Special-view init: compiles 4 ps.1.1 shaders, loads `Binoculr.tga` lens HUD texture |
| `0x52BDB0` | `FUN_0052BDB0` | **Foot NVG render**: full-screen green pass |
| `0x52C630` | `FUN_0052C630` | Vehicle NVG render (same shader handle) |
| `0x4B7110` | `FUN_004B7110` | Main render dispatch: special-view branch on `DAT_0096C4BC` |
| `0x489CC0` | `FUN_00489CC0` | Input action handler: `case 0x33` = N key NVG toggle |
| `0x629A04` | Keybind data | N-key binding entry (id 0x33 → "!Night Vision" → command "NVG") |

### 3.4 Key Globals

| Address | Meaning |
|---|---|
| `DAT_0096C4BC` | NVG active flag (1=on). Only real setter: `FUN_00489CC0` case 0x33; all other writes clear it |
| `DAT_0096C4B0/B1` | Binocular mode (B key, id 0x23; per-frame latch B0=B1 in `FUN_004240C0`) |
| `DAT_00E049B0` | NVG shader handle (PS path); without PS it holds fixed-function stage-state config |
| `DAT_00E049CC` | Brightness-boost flag (=1 → fallback uses bright green `0xFF30FF30`) |
| `DAT_00E049C0/C4` | `Binoculr.tga` lens HUD texture handles |

---

## 4. Shader Initialization (`FUN_0052A9D0`) Details

Runs once after D3D device creation; compiles **4 ps.1.1 shaders** (`FUN_0057BC42` = D3DXAssembleShader):

| Source VA | c0 (luma weights) | Purpose | Stored in |
|---|---|---|---|
| `0x64F8D4` | 0.50, 1.00, 0.50 | **NVG green tint** (subject of this report) | `DAT_00E049B0` |
| `0x64F99C` | 0.50, 0.50, 0.50 | Neutral grayscale (binocular family) | `DAT_00E04998` |
| `0x64F728` | 0.30, 0.60, 0.10 | 4-texture variant | `DAT_00E049B4` |
| `0x64FAA4` | 0.30, 0.60, 0.10 | 1-texture variant | `DAT_00E049A8` |

If the device lacks PS support or the D3D level is insufficient, `DAT_00E049B0` is filled by `FUN_005AB760` with fixed-function texture-stage state instead, and `DAT_00E049CC=1` enables the brightness boost.

---

## 5. Recolor Patch

Script: `nvg_color_patch.py` (distributed alongside this report)

```bash
python nvg_color_patch.py FF5533 DFBHD.exe      # orange-red NVG
python nvg_color_patch.py 00C8FF "C:\\Games\\BHD\\DFBHD.exe"   # cyan-blue NVG
```

Pass the source exe path as the 2nd argument (if omitted, the script looks for `DFBHD.exe` in the current directory, then the script directory). The script only reads the source file.

Principle (**all edits are same-length in-place replacements** — no offsets/structures touched):

1. **Shader source** (0x64F8D4): only the numeric text of the `def c1` / `def c2` lines is rewritten
   - Mapping: `c1 = RGB × 0.9` (gain), `c2 = RGB × 0.2` (bias) — same dynamic range as stock, hue swapped
2. **Fallback colors** (6 imm32s): scaled from the custom RGB by the stock brightness levels (0.50 / 0.28 / 1.00); Alpha stays FF
3. Validation (relaxed — position only, no content consistency): file size unchanged before/after + `def c1/def c2` lines present at 0x64F8D4 + the 6 color addresses writable; no original byte values are compared
4. Writes a **new file** `DFBHD_NVG_<hex>.exe`; the game directory is never touched — copy the result in yourself

---

## 6. Methodology Notes

- Ghidra showed no xrefs into the `0x62xxxx` keybind data block → switched to a **pefile whole-file imm32 scan** to locate code references; must exclude `E8/E9/0F8x` (call/jcc displacement) false positives
- Filtering strings by the `"ps.1.1"` keyword is the fastest entry point for locating render effects
- `NVG_FLIP` @ `0x64A6F8` is a character-model animation marker (goggle-flip), not the effect itself; the "Night Vision Goggles" item in `ITEMS_.DEF` (id 101904, graphic nvg) is the world pickup model, also not the effect itself
