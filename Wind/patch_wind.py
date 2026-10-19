# -*- coding: utf-8 -*-
"""
DFBHD_P.exe 子弹风偏补丁生成器
目标: Delta Force Black Hawk Down, DFBHD_P.exe v1.5.0.5 (32-bit PE)

原理:
  子弹 mover 0x491B00 每帧调用阻力函数 0x491930，默认弹种 drag==0x10000
  时该函数在 0x491959 直接返回，风矢量(0xE19DC0/DC4)从不作用于弹速。
  本补丁将 0x491930 入口改为 jmp 到 _TEXT 节洞 0x610010，注入:
      vx += wind_x >> SAR   (+0x6C)
      vy += wind_y >> SAR   (+0x70)
  后跳回 0x491937 继续原逻辑。

用法:
  python patch_wind.py <原版DFBHD_P.exe> [-o 输出路径] [--sar N] [--unpatch <已打补丁文件>]
  --sar N : 风力缩放位移量，默认 5 (风/32)。越小风越强: 3=狂风, 4=强, 6=温和, 9=微弱。

详见同目录分析报告 Wind_Bullet_zh-CN.md / Wind_Bullet_en.md。
"""
import argparse, sys

# ---- 常量（仅对 v1.5.0.5 有效）----
HOOK_VA   = 0x491930          # 阻力函数入口
HOOK_ORIG = bytes.fromhex('558BEC518B')   # push ebp; mov ebp,esp; push ecx; mov ecx,[ebp+8] 的前5字节
RESUME_VA = 0x491937          # 跳回点（重放完 7 字节序言之后）
CAVE_VA   = 0x610010          # _TEXT 节洞（VA 0x610000, RawSize 0x1000, RWX, 尾部全零）
CAVE_FILE = 0x210010          # 洞的文件偏移
WIND_X_G  = 0xE19DC0          # 风矢量全局 (16.16 定点)
WIND_Y_G  = 0xE19DC4
VX_OFS, VY_OFS = 0x6C, 0x70   # 弹体实例速度字段
TEXT_RVA_DELTA = 0x400000     # 本 exe 中 .text 与 _TEXT 均满足 VA-0x400000=文件偏移


def build_cave(sar: int) -> bytes:
    """构造注入代码（重放序言 + 两轴风力加速 + 跳回）"""
    if not 0 <= sar <= 31:
        sys.exit('--sar 需在 0..31')
    cave = bytearray()
    cave += bytes.fromhex('558BEC518B4D08')                       # 重放被覆盖的 7 字节序言
    for g, ofs in ((WIND_X_G, VX_OFS), (WIND_Y_G, VY_OFS)):
        cave += b'\xA1' + g.to_bytes(4, 'little')                 # mov eax,[wind_g]
        cave += b'\xC1\xF8' + bytes([sar])                        # sar eax,sar
        cave += b'\x01\x41' + bytes([ofs])                        # add [ecx+ofs],eax
    # jmp 回 RESUME_VA（相对偏移在写入时按洞内实际位置计算）
    rel = RESUME_VA - (CAVE_VA + len(cave) + 5)
    cave += b'\xE9' + (rel & 0xFFFFFFFF).to_bytes(4, 'little')
    assert len(cave) <= 48, 'cave 超出预留空间'
    return bytes(cave)


def patch(src: str, dst: str, sar: int):
    data = bytearray(open(src, 'rb').read())
    ho = HOOK_VA - TEXT_RVA_DELTA
    # 前置校验：必须是未打补丁的原版
    if data[ho:ho + 5] != HOOK_ORIG:
        sys.exit('入口字节不匹配：文件不是 v1.5.0.5 原版或已被打过补丁')
    if data[CAVE_FILE:CAVE_FILE + 48] != bytes(48):
        sys.exit('_TEXT 洞非全零，放弃写入')
    # 1) 入口 5 字节 → jmp cave
    rel = CAVE_VA - (HOOK_VA + 5)
    data[ho:ho + 5] = b'\xE9' + (rel & 0xFFFFFFFF).to_bytes(4, 'little')
    # 2) 写洞
    cave = build_cave(sar)
    data[CAVE_FILE:CAVE_FILE + len(cave)] = cave
    open(dst, 'wb').write(bytes(data))
    # 3) 回读校验
    chk = open(dst, 'rb').read()
    orig = open(src, 'rb').read()
    diff = [i for i in range(len(orig)) if orig[i] != chk[i]]
    assert chk[ho:ho + 5] == data[ho:ho + 5]
    print(f'OK: {dst}\n  sar={sar} (风/{2**sar})  改动 {len(diff)} 字节  '
          f'范围 {hex(min(diff))}..{hex(max(diff))}')
    try:
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        print('  hook:', ' '.join(f'{i.mnemonic} {i.op_str}' for i in md.disasm(chk[ho:ho+5], HOOK_VA)))
        print('  cave:')
        for i in md.disasm(chk[CAVE_FILE:CAVE_FILE+len(cave)], CAVE_VA):
            print(f'    {i.address:#08x}  {i.mnemonic} {i.op_str}')
    except ImportError:
        print('  (安装 capstone 可查看反汇编验证)')


def unpatch(tgt: str):
    """还原：把 hook 改回原字节并清零洞（需文件其余部分未动）"""
    data = bytearray(open(tgt, 'rb').read())
    ho = HOOK_VA - TEXT_RVA_DELTA
    if data[ho:ho + 1] != b'\xE9':
        sys.exit('目标没有本补丁的 hook，拒绝操作')
    data[ho:ho + 5] = HOOK_ORIG
    data[CAVE_FILE:CAVE_FILE + 48] = bytes(48)
    open(tgt, 'wb').write(bytes(data))
    print(f'已还原: {tgt}')


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description='DFBHD_P.exe 子弹风偏补丁 (v1.5.0.5)')
    ap.add_argument('exe', help='原版 DFBHD_P.exe 路径')
    ap.add_argument('-o', '--out', help='输出路径（默认 原名_wind.exe）')
    ap.add_argument('--sar', type=int, default=5, help='风力缩放位移，默认5；3=狂风 9=微弱')
    ap.add_argument('--unpatch', metavar='FILE', help='还原指定文件后退出')
    a = ap.parse_args()
    if a.unpatch:
        unpatch(a.unpatch)
    else:
        patch(a.exe, a.out or a.exe.rsplit('.', 1)[0] + '_wind.exe', a.sar)
