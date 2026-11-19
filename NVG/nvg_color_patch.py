# -*- coding: utf-8 -*-
"""
BHD 夜视仪自定义颜色补丁
========================
原理：NVG 绿色效果 = 0x64F8D4 处内嵌的 ps.1.1 像素着色器源码文本
    def c0, 0.50,  1.00,  0.50,  0.0   <- 亮度权重（灰度化，不动）
    def c1, 0.20,  0.90,  0.20,  0.0   <- 颜色增益（决定色调）
    def c2, 0.00,  0.20,  0.00,  0.0   <- 颜色底色（暗部也带色）
  引擎启动时用 D3DXAssembleShader 编译该文本，渲染时 FUN_0052BDB0
  （步行 NVG）/ FUN_0052C630（车载 NVG）绑定为全屏 pass。

补丁方式（全部等长原地替换，不破坏任何结构/偏移）：
  1. 重写着色器源码里 c1/c2 两行（ASCII 文本）
  2. 重写 5 处固定管线兜底颜色 imm32（不支持像素着色器时的路径）
     0xFF408040 @ 0x52BE16 / 0x52C7EA
     0xFF084808 @ 0x52BE77 / 0x52C854
     0xFF308030 @ 0x52BEBB
     0xFF30FF30 @ 0x52BEB3

用法：
  python nvg_color_patch.py <RGB hex> <DFBHD.exe 路径>
  例：python nvg_color_patch.py FF5533 DFBHD.exe
      python nvg_color_patch.py 00C8FF "C:\\Games\\BHD\\DFBHD.exe"
  <DFBHD.exe 路径> 省略时，依次尝试：当前目录 → 脚本所在目录
  下的 DFBHD.exe。脚本只读源文件，输出新文件到脚本所在目录，
  绝不改动游戏目录里的任何文件。

注意：输出是【新文件】，自行把生成的 DFBHD_NVG_<色值>.exe
  复制到游戏目录使用。
"""
import pefile
import struct
import re
import os
import sys

# ---- 默认参数 ----
OUT_DIR = os.path.dirname(os.path.abspath(__file__))

# ---- 补丁点（VA / image base 0x400000）----
SHADER_VA = 0x64F8D4          # NVG 像素着色器源码文本起始
COLOR_PATCHES = [             # (VA, 原始 dword, 亮度等级=原G/0xFF)
    (0x52BE16, 0xFF408040, 0x80 / 0xFF),   # 步行 NVG：PS 路径顶点色
    (0x52C7EA, 0xFF408040, 0x80 / 0xFF),   # 车载 NVG：PS 路径顶点色
    (0x52BE77, 0xFF084808, 0x48 / 0xFF),   # 步行：固定管线暗部
    (0x52C854, 0xFF084808, 0x48 / 0xFF),   # 车载：固定管线暗部
    (0x52BEBB, 0xFF308030, 0x80 / 0xFF),   # 步行：固定管线标准亮度
    (0x52BEB3, 0xFF30FF30, 0xFF / 0xFF),   # 步行：固定管线增亮（NVG增亮开）
]
IMAGE_BASE = 0x400000


def parse_rgb(s):
    s = s.strip().lstrip("#").removeprefix("0x").removeprefix("0X")
    if not re.fullmatch(r"[0-9a-fA-F]{6}", s):
        raise ValueError("RGB hex 必须是 6 位十六进制，例如 FF5533")
    r, g, b = (int(s[i:i + 2], 16) for i in (0, 2, 4))
    if (r, g, b) == (0, 0, 0):
        raise ValueError("纯黑 (000000) 会让夜视仪全黑，请换一个颜色")
    return (r, g, b), s.upper()


def va2off(pe, va):
    return pe.get_offset_from_rva(va - IMAGE_BASE)


def fmt_f(v):
    """格式化成与源码等宽的 X.XX（4 字符）"""
    return "%.2f" % max(0.0, min(v, 9.99))


def patch_shader(buf, pe, rgb):
    """等长重写 c1/c2 两行。色调 T：c1 = T*0.9（增益），c2 = T*0.2（底色）
    与原版 (0.2,0.9,0.2)+(0,0.2,0) 的动态范围一致，仅换色调。"""
    off = va2off(pe, SHADER_VA)
    src = buf[off:off + 256].split(b"\x00")[0].decode("ascii")
    orig = src  # 保留原文用于报告

    t = (c / 255.0 for c in rgb)
    r, g, b = rgb
    c1 = (r * 0.9 / 255.0, g * 0.9 / 255.0, b * 0.9 / 255.0)
    c2 = (r * 0.2 / 255.0, g * 0.2 / 255.0, b * 0.2 / 255.0)

    new_src, n1 = re.subn(
        r"def c1, [0-9.]+,  [0-9.]+,  [0-9.]+,  0\.0",
        "def c1, %s,  %s,  %s,  0.0" % (fmt_f(c1[0]), fmt_f(c1[1]), fmt_f(c1[2])),
        src, count=1)
    new_src, n2 = re.subn(
        r"def c2, [0-9.]+,  [0-9.]+,  [0-9.]+,  0\.0",
        "def c2, %s,  %s,  %s,  0.0" % (fmt_f(c2[0]), fmt_f(c2[1]), fmt_f(c2[2])),
        new_src, count=1)
    if n1 != 1 or n2 != 1:
        raise RuntimeError("着色器源码格式与预期不符，拒绝补丁")
    if len(new_src) != len(src):
        raise RuntimeError("重写后长度变化，拒绝补丁")
    buf[off:off + len(new_src)] = new_src.encode("ascii")
    return orig, new_src


def patch_colors(buf, pe, rgb):
    r, g, b = rgb  # 0-255 整数
    report = []
    for va, orig, level in COLOR_PATCHES:
        off = va2off(pe, va)
        cur = struct.unpack_from("<I", buf, off)[0]
        if cur != orig:
            raise RuntimeError("0x%08X 处字节与预期不符 (0x%08X != 0x%08X)，拒绝补丁"
                               % (va, cur, orig))
        nr = min(255, round(r * level))
        ng = min(255, round(g * level))
        nb = min(255, round(b * level))
        new = 0xFF000000 | (nr << 16) | (ng << 8) | nb
        struct.pack_into("<I", buf, off, new)
        report.append((va, orig, new))
    return report


def verify(buf, pe):
    """补丁后结构校验：着色器源码仍可解析、指令序列未变。"""
    off = va2off(pe, SHADER_VA)
    src = buf[off:off + 256].split(b"\x00")[0].decode("ascii")
    ok = all(k in src for k in ("ps.1.1", "tex t0", "dp3     r0, t0, c0",
                                "mul  r0, r0, c1", "add     r0, r0, c2"))
    return ok, src


def find_src(args):
    """定位源 exe：第 2 个位置参数 → 当前目录 → 脚本所在目录"""
    explicit = None
    rest = []
    i = 0
    while i < len(args):
        if not explicit and not args[i].startswith("-") and args[i].lower().endswith(".exe"):
            explicit = args[i]
        else:
            rest.append(args[i])
        i += 1
    if explicit:
        return explicit, rest
    for cand in (os.path.join(os.getcwd(), "DFBHD.exe"),
                 os.path.join(OUT_DIR, "DFBHD.exe")):
        if os.path.isfile(cand):
            return cand, rest
    return None, rest


def main():
    if len(sys.argv) < 2 or sys.argv[1].lower() in ("-h", "--help"):
        print(__doc__)
        return
    rgb, hexs = parse_rgb(sys.argv[1])

    src, rest = find_src(sys.argv[2:])
    if not src:
        print("未找到 DFBHD.exe。请把源 exe 路径作为第 2 个参数传入，"
              "或把 DFBHD.exe 放在当前目录/脚本目录。")
        return
    print("源文件:", src)

    pe = pefile.PE(data=open(src, "rb").read(), fast_load=True)
    buf = bytearray(pe.__data__)

    orig_shader, new_shader = patch_shader(buf, pe, rgb)
    color_report = patch_colors(buf, pe, rgb)
    ok, final_src = verify(buf, pe)
    if not ok:
        raise RuntimeError("补丁后校验失败！")

    out = os.path.join(OUT_DIR, "DFBHD_NVG_%s.exe" % hexs)
    with open(out, "wb") as f:
        f.write(buf)

    r, g, b = rgb
    print("补丁颜色: #%02X%02X%02X" % (r, g, b))
    print("--- 着色器源码 (0x%08X) ---" % SHADER_VA)
    print("原:"); print(orig_shader)
    print("新:"); print(new_shader)
    print("--- 固定管线兜底颜色 ---")
    for va, o, n in color_report:
        print("0x%08X: 0x%08X -> 0x%08X" % (va, o, n))
    print("校验:", "通过" if ok else "失败")
    print("输出文件:", out)


if __name__ == "__main__":
    main()
