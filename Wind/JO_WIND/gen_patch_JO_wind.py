# -*- coding: utf-8 -*-
"""
JO（Joint Operations: Typhoon Rising）子弹风偏补丁生成器（原生风力版）

钩子: 0x004EAA5A（mover FUN_004e9d70 子弹重力 ADD，10 字节）→ CALL 洞 + NOP×5
洞:   0x007472C9（.text 中部 55B cc 对齐间隙，文件偏移 0x3472C9）→ 39 字节注入码
语义: 每 tick  vx/vy += wind >> K   （JO 原生满风 197/帧 = 重力 118%，K=0..8 九档）
推荐档位: K4 / K5

用法:
    python gen_patch_JO_wind_native.py [源exe] [输出目录]
    默认源 = D:\\3DM\\JOTAC\\Game\\JO\\jointops.exe（只读，严禁写入游戏目录）
    默认输出 = 脚本所在目录

内置五重断言 + capstone 反汇编自检（若已安装）。
"""
import os
import sys
import hashlib

SIZE     = 4612096
HOOK_OFF = 0xEAA5A    # VA 0x004EAA5A
CAVE_OFF = 0x3472C9   # VA 0x007472C9
HOOK_VA  = 0x4EAA5A
CAVE_VA  = 0x7472C9

# 原始钩子字节: add [ebx+0xA0], -167 （必须逐位核对，防版本不对）
HOOK_ORIG = bytes([0x81, 0x83, 0xA0, 0x00, 0x00, 0x00, 0x59, 0xFF, 0xFF, 0xFF])
# 替换字节: CALL rel32 + NOP×5
HOOK_NEW  = bytes([0xE8, 0x6A, 0xC8, 0x25, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90])

# 洞内 39 字节模板；档位字节位于 idx17 / idx31
CAVE_TEMPLATE = bytes([
    0x81, 0x83, 0xA0, 0x00, 0x00, 0x00, 0x59, 0xFF, 0xFF, 0xFF,  # add [ebx+0xA0],-167 原重力指令搬入
    0xA1, 0xE4, 0x59, 0xC0, 0x02,                                # mov eax,[0x02C059E4]  wind_x
    0xC1, 0xF8, 0x00,                                            # sar eax,K             档位 (idx17)
    0x01, 0x83, 0x98, 0x00, 0x00, 0x00,                          # add [ebx+0x98],eax    vx += wind
    0xA1, 0xE8, 0x59, 0xC0, 0x02,                                # mov eax,[0x02C059E8]  wind_y
    0xC1, 0xF8, 0x00,                                            # sar eax,K             档位 (idx31)
    0x01, 0x83, 0x9C, 0x00, 0x00, 0x00,                          # add [ebx+0x9C],eax    vy += wind
    0xC3,                                                        # ret
])

# 每档与原版的预期差异字节数：钩子 9 + 洞 39 = 48
EXPECTED_DIFF = 48


def fail(msg):
    raise SystemExit("[X] " + msg)


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else r"D:\3DM\JOTAC\Game\JO\jointops.exe"
    outdir = sys.argv[2] if len(sys.argv) > 2 else os.path.dirname(os.path.abspath(__file__))

    # rel32 自检：5 字节 CALL 必须落在洞址
    rel = CAVE_VA - (HOOK_VA + 5)
    if rel != 0x25C86A:
        fail("rel32 = 0x%08X, 预期 0x25C86A" % rel)
    if len(CAVE_TEMPLATE) != 39:
        fail("洞模板长度错误: %d" % len(CAVE_TEMPLATE))

    data = open(src, "rb").read()
    print("[i] 源文件: %s (%d 字节)" % (src, len(data)))
    if len(data) != SIZE:
        fail("源文件尺寸不符（应为 %d）" % SIZE)

    # 断言 1：钩子原始字节
    if data[HOOK_OFF:HOOK_OFF + 10] != HOOK_ORIG:
        fail("钩子字节不匹配 @0x%X（版本不对？）" % HOOK_OFF)
    print("[ok] 钩子原始字节核对通过")

    # 断言 2：洞区为 55 字节纯 0xCC
    cave_region = data[CAVE_OFF:CAVE_OFF + 55]
    if len(cave_region) != 55 or any(b != 0xCC for b in cave_region):
        fail("洞区不是 55 字节纯 cc @0x%X（被占用？）" % CAVE_OFF)
    print("[ok] 洞区 55×0xCC 核对通过")

    # 生成九档
    os.makedirs(outdir, exist_ok=True)
    outs = {}
    for K in range(9):
        buf = bytearray(data)
        cave = bytearray(CAVE_TEMPLATE)
        cave[17] = K
        cave[31] = K
        buf[HOOK_OFF:HOOK_OFF + 10] = HOOK_NEW
        buf[CAVE_OFF:CAVE_OFF + 39] = cave
        path = os.path.join(outdir, "jointops_wind_native_K%d.exe" % K)
        with open(path, "wb") as f:
            f.write(buf)
        outs[K] = buf
        print("[..] 已生成 jointops_wind_native_K%d.exe" % K)

    # 断言 3/4：每档与原版 diff 恰 48 字节，且全部落在钩子/洞范围内；档位字节正确
    print("[i] --- 逐档校验 ---")
    for K in range(9):
        buf = outs[K]
        diff = [i for i in range(SIZE) if buf[i] != data[i]]
        if len(diff) != EXPECTED_DIFF:
            fail("K%d: diff=%d, 预期 %d" % (K, len(diff), EXPECTED_DIFF))
        outside = [i for i in diff
                   if not (HOOK_OFF <= i < HOOK_OFF + 10 or CAVE_OFF <= i < CAVE_OFF + 39)]
        if outside:
            fail("K%d: 存在钩子/洞范围外的改动: %s" % (K, ", ".join("0x%X" % i for i in outside[:5])))
        if buf[CAVE_OFF + 17] != K or buf[CAVE_OFF + 31] != K:
            fail("K%d: 档位字节错误 (%d/%d)" % (K, buf[CAVE_OFF + 17], buf[CAVE_OFF + 31]))
        md5 = hashlib.md5(bytes(buf)).hexdigest()
        print("[ok] K%d: diff=%d  档位字节=%d/%d  md5=%s" % (K, len(diff), K, K, md5))

    # 断言 5：九档之间仅差 2 个档位字节
    a, z = outs[0], outs[8]
    cross = [i for i in range(SIZE) if a[i] != z[i]]
    if cross != [CAVE_OFF + 17, CAVE_OFF + 31]:
        fail("跨档 diff 异常: %s" % ", ".join("0x%X" % i for i in cross[:5]))
    print("[ok] 跨档校验：K0 vs K8 仅差 2 字节 @ 0x%X / 0x%X" % (CAVE_OFF + 17, CAVE_OFF + 31))

    # capstone 反汇编自检（可选）
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        md = Cs(CS_ARCH_X86, CS_MODE_32)
    except ImportError:
        print("[i] 未安装 capstone，跳过反汇编自检（pip install capstone 后可启用）")
        return
    except TypeError:
        print("[i] capstone 版本不兼容，跳过反汇编自检")
        return
    for K in (0, 4):
        cave = bytearray(CAVE_TEMPLATE)
        cave[17] = K
        cave[31] = K
        print("[i] --- 洞内反汇编自检 (K=%d) ---" % K)
        for ins in md.disasm(bytes(cave), CAVE_VA):
            print("     0x%08X  %-6s %s" % (ins.address, ins.mnemonic, ins.op_str))
        print("[i] --- 钩子反汇编自检 ---")
        for ins in md.disasm(HOOK_NEW, HOOK_VA):
            print("     0x%08X  %-6s %s" % (ins.address, ins.mnemonic, ins.op_str))

    print("[DONE] 九档原生风力补丁生成并校验完毕，输出目录: %s" % outdir)
    print("[i] 注意：产物只写本目录，请自行复制到游戏目录；联机需全员同档位。")


if __name__ == "__main__":
    main()
