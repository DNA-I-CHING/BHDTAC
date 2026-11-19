# -*- coding: utf-8 -*-
r"""
BHD NVG Advanced Patch (color + grayscale + brightness)
=======================================================
Changes are limited to numeric literals inside the shader source text
at 0x64F8D4 (same-length in-place replacement). Instruction sequence,
offsets and structures are never touched -- maximum safety.

Parameters:
  color hex   RRGGBB, 6 hex digits (e.g. FF5533)
  --luma hex  Grayscale (luminance extraction weights) c0, given as 6 hex
              digits; each byte = weight x 255:
                80FF80  stock (green-biased, bright image) (0.50, 1.00, 0.50)
                4C9618  perceptual luminance (darker, realistic) (0.30, 0.59, 0.09)
                555555  simple average (neutral gray) (0.33, 0.33, 0.33)
              If omitted, the stock weights are kept unchanged.
  --bright F  Brightness multiplier 0.1~4.0 (applies to color gain c1 and
              bias c2)
  exe path    Any argument ending with .exe; if absent, the script looks
              for DFBHD.exe in the current working directory

Usage examples:
  python nvg_color_pro.py D:\somedir\DFBHD.exe FF5533 --luma 4C9618 --bright 1.2
  python nvg_color_pro.py 00C8FF --bright 1.5        (when cd'd into the game dir)

Output: DFBHD_PRO_<color>[_L<luma>][_B<brightness>].exe (new file only,
never touches the game directory)
"""
import pefile
import struct
import hashlib
import re
import os
import sys

OUT_DIR = os.path.dirname(os.path.abspath(__file__))
IMAGE_BASE = 0x400000
SHADER_VA = 0x64F8D4


def parse_color(s):
    # 6-digit RRGGBB only; 8-digit AARRGGBB (alpha) was removed with the
    # transparency feature.
    s = s.strip().lstrip("#").removeprefix("0x").removeprefix("0X")
    if not re.fullmatch(r"[0-9a-fA-F]{6}", s):
        raise ValueError("颜色 hex 必须是 6 位 (RRGGBB)，例如 FF5533。"
                         "（高级版不支持透明度，8 位 hex 已废弃）")
    rgb = tuple(int(s[i:i + 2], 16) for i in (0, 2, 4))
    if rgb == (0, 0, 0):
        raise ValueError("纯黑 (000000) 会让夜视仪全黑，请换一个颜色")
    return rgb, s.upper()


def parse_luma(s):
    """6 hex digits -> three luminance weights (each byte / 255)."""
    s = s.strip().lstrip("#").removeprefix("0x").removeprefix("0X")
    if not re.fullmatch(r"[0-9a-fA-F]{6}", s):
        raise ValueError("--luma 必须是 6 位 hex，如 4C9618（每字节=权重×255）")
    w = tuple(int(s[i:i + 2], 16) / 255.0 for i in (0, 2, 4))
    if sum(w) < 0.05:
        raise ValueError("--luma 权重全为 0 会导致画面纯色，拒绝")
    return w, s.upper()


def va2off(pe, va):
    # VA -> file offset (image base 0x400000)
    return pe.get_offset_from_rva(va - IMAGE_BASE)


def fmt4(v):
    # X.XX 4-char formatting, keeps the shader text same-length
    return "%.2f" % max(0.0, min(v, 9.99))


def patch(buf, pe, rgb, luma, bright):
    # Rewrite only the numeric literals of def c0/c1/c2 in the shader source.
    # c0 = luminance weights (grayscale), c1 = color gain, c2 = color bias.
    # Mapping: c1 = RGB * 0.9 * bright, c2 = RGB * 0.2 * bright -- same
    # dynamic range as the stock green, hue swapped.
    off = va2off(pe, SHADER_VA)
    text = buf[off:off + 256].split(b"\x00")[0].decode("ascii")
    if "ps.1.1" not in text or "def c0" not in text:
        raise RuntimeError("0x%08X 处未找到着色器文本" % SHADER_VA)

    r, g, b = rgb
    c1 = tuple(v * 0.9 * bright for v in (r / 255, g / 255, b / 255))
    c2 = tuple(v * 0.2 * bright for v in (r / 255, g / 255, b / 255))

    new, n1 = re.subn(r"def c1, [0-9.]+,  [0-9.]+,  [0-9.]+,  0\.0",
                      "def c1, %s,  %s,  %s,  0.0" % tuple(fmt4(v) for v in c1),
                      text, count=1)
    new, n2 = re.subn(r"def c2, [0-9.]+,  [0-9.]+,  [0-9.]+,  0\.0",
                      "def c2, %s,  %s,  %s,  0.0" % tuple(fmt4(v) for v in c2),
                      new, count=1)
    n0 = 1
    if luma is not None:
        new, n0 = re.subn(r"def c0, [0-9.]+,  [0-9.]+,  [0-9.]+,  0\.0",
                          "def c0, %s,  %s,  %s,  0.0" % tuple(fmt4(v) for v in luma),
                          new, count=1)
    if (n0, n1, n2) != (1, 1, 1):
        raise RuntimeError("着色器文本格式不符，拒绝补丁")
    if len(new) != len(text):
        raise RuntimeError("等长校验失败")
    buf[off:off + len(new.encode("ascii"))] = new.encode("ascii")
    return text, new


def find_src(args):
    """Locate the source exe: any existing *.exe argument, else DFBHD.exe in
    the current working directory; otherwise fail with a hint. Never
    hard-code personal paths."""
    for a in args:
        if a.lower().endswith(".exe") and os.path.isfile(a):
            return a
    cand = os.path.join(os.getcwd(), "DFBHD.exe")
    if os.path.isfile(cand):
        return cand
    raise SystemExit("错误: 未找到源 exe。请传入 DFBHD.exe 路径，或 cd 到游戏目录再运行。")


def main():
    args = sys.argv[1:]
    if not args or args[0].lower() in ("-h", "--help"):
        print(__doc__)
        return
    src = find_src(args)
    rest = [a for a in args if a is not src and not a.lower().endswith(".exe")]
    if not rest:
        raise SystemExit("错误: 缺少颜色 hex 参数，如 FF5533")
    rgb, hexs = parse_color(rest[0])

    luma = None
    bright = 1.0
    lumahex = None
    i = 1
    while i < len(rest):
        a = rest[i]
        if a == "--luma":
            luma, lumahex = parse_luma(rest[i + 1]); i += 2
        elif a == "--bright":
            bright = float(rest[i + 1]); i += 2
            if not (0.1 <= bright <= 4.0):
                raise ValueError("--bright 取值 0.1~4.0")
        else:
            print("未知参数:", a); return

    md5 = hashlib.md5(open(src, "rb").read()).hexdigest()
    print("源文件:", src)
    print("md5:", md5, "(仅记录，不阻断)")

    pe = pefile.PE(data=open(src, "rb").read(), fast_load=True)
    buf = bytearray(pe.__data__)
    orig, new = patch(buf, pe, rgb, luma, bright)

    final = buf[va2off(pe, SHADER_VA):va2off(pe, SHADER_VA) + 256].split(b"\x00")[0].decode("ascii")
    ok = "ps.1.1" in final and "tex t0" in final and "dp3" in final
    if not ok:
        raise RuntimeError("补丁后校验失败")

    # Output file tag: color, optional luma hex, optional brightness
    tag = hexs
    if luma is not None:
        tag += "_L" + lumahex
    if bright != 1.0:
        tag += "_B%02d" % round(bright * 10)
    out = os.path.join(OUT_DIR, "DFBHD_PRO_%s.exe" % tag)
    with open(out, "wb") as f:
        f.write(buf)

    print("颜色: #%s  灰度: %s  亮度: x%.2f" % (
        hexs, ("0x" + lumahex) if luma else "原版", bright))
    print("--- 补丁后着色器文本 ---")
    print(final.rstrip())
    print("校验:", "通过" if ok else "失败")
    print("输出:", out)


if __name__ == "__main__":
    main()
