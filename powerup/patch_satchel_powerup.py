# -*- coding: utf-8 -*-
"""
DFBHD.exe (三角洲特种部队1：黑鹰坠落, V1.5.0.5) 炸药包 powerupdef 代码洞补丁 v2
================================================================================
背景：给 ITEMS.DEF id 101891 (Satchel Charge, move/ai=schl, disk=EXPLOSV) 加
`powerupdef AmmoFull` 后，拾取评估例程 0x4AFF40 在标志置位后直接解引用
[obj+0x198]+0x2C（该指针仅 POWERUP 注册链填充，炸药包恒为 0）→ AV@0x4AFFB8。

方案：新增独立可执行节 .joext (VA 0x00F72000)，洞内做"最小注册"：
  - 不调用 PU_REG(0x48C6B0)——其尾部 EFFECT 表查找/0x48C8A0 假定真 POWERUP
    对象形状，在炸药包垃圾字段上 strlen 会 AV（v1 实测崩溃教训）。
  - 自行扫描 powerup 定义表（基址[0x96D1B8]/计数[0x96D1B0]/步长0xB8，
    strcmp=0x5C3570），按 ITEM 记录+0x790 的名字匹配，命中只写安全字段：
    +0x224=mover 0x48B580, +0x198=def, +0x190/+0x194=def+0x20/+0x24,
    +0x1a0=数量, +0x18c=0(上膛)，并清 +0x19C/+0x19D/+0x19E(word)/+0x230
    （+0x19E=0 使 mover 永不调危险的 0x48C8A0）。
  - 寄存器约束：eval 后续路径存活 ebx/edx/edi/esi，洞只破坏 eax/ecx。
挂钩：0x4AFFA7 处 5 字节 `8B 4E 28 85 C9` → E9 rel32，跳回 0x4AFFB2；
      obj+0x28==0 时走原生跳过路径 0x4B02A7（结果字节保持 0xFF=不可用）。

用法：python patch_satchel_powerup.py <原版DFBHD.exe路径> [输出路径]
默认输出：源文件同目录 DFBHD_satchel_powerup_v2.exe
实测成功版本 MD5: EDEC0581F37F4BE5BC195CAC69DD98AD (2551808 字节)
"""
import hashlib
import os
import struct
import sys

ORIG_MD5  = "d6f51ad03ca62f040586b8b5e3ca8181"
ORIG_SIZE = 2547712            # 0x26E000，即新节 raw 起点
V2_MD5    = "edec0581f37f4be5bc195cac69dd98ad"

IMAGE_BASE = 0x00400000
CAVE_RVA   = 0x00B72000
CAVE_VA    = 0x00F72000
CAVE_RAW   = 0x26E000
CAVE_RSIZE = 0x1000
NEW_SIZEOFIMAGE = 0x00B73000

HOOK_VA   = 0x4AFFA7
BACK_VA   = 0x4AFFB2           # je 0x4B02A7 所在指令
SKIP_VA   = 0x4B02A7           # 原生"结果0xFF不可用"返回路径 (pop edi;ret)
HOOK_ORIG = bytes.fromhex("8b4e2885c9")                     # mov ecx,[esi+28];test ecx,ecx
CTX_ORIG  = bytes.fromhex("8b8698010000" "0f84ef020000")    # mov eax,[esi+198]; je SKIP

# 已用 capstone 逐条反汇编核对过的洞机器码（264 字节）：
# 00f72000  8b86 98010000   mov  eax,[esi+0x198]        ; 已注册?
# 00f72006  85c0            test eax,eax
# 00f72008  0f85 e5000000   jne  L3 (0xf720f3)          ; 真powerup→复刻现场跳回
# 00f7200e  8b4e 28         mov  ecx,[esi+0x28]
# 00f72011  85c9            test ecx,ecx
# 00f72013  0f84 ea000000   je   L4 (0xf72103)          ; →jmp 0x4B02A7
# 00f72019  83ec 08         sub  esp,8                  ; [esp]=name [esp+4]=i
# 00f7201c  a1 b0d19600     mov  eax,[0x96D1B0]         ; 定义表计数
# 00f72021  85c0            test eax,eax
# 00f72023  0f8e c7000000   jle  NOTFOUND (0xf720f0)
# 00f72029  8b46 24         mov  eax,[esi+0x24]         ; ITEM 记录
# 00f7202c  05 90070000     add  eax,0x790              ; powerupdef 名字符串
# 00f72031  8904 24         mov  [esp],eax
# 00f72034  c74424 04 00000000  mov dword[esp+4],0      ; i=0
# 00f7203c  LOOP: 8b44 2404 mov  eax,[esp+4]
# 00f72040  69c0 b8000000   imul eax,eax,0xB8           ; 必须 imm32（0xB8>0x7F）
# 00f72046  8b0d b8d19600   mov  ecx,[0x96D1B8]         ; 定义表基址
# 00f7204c  03c8            add  ecx,eax                ; cand = base+i*0xB8
# 00f7204e  51              push ecx
# 00f7204f  ff7424 04       push dword[esp+4]           ; name
# 00f72053  e8 181565ff     call 0x5C3570               ; strcmp
# 00f72058  83c4 08         add  esp,8
# 00f7205b  85c0            test eax,eax
# 00f7205d  74 15           je   FOUND (0xf72074)
# 00f7205f  ff4424 04       inc  dword[esp+4]
# 00f72063  8b44 2404       mov  eax,[esp+4]
# 00f72067  3b05 b0d19600   cmp  eax,[0x96D1B0]
# 00f7206d  7c cd           jl   LOOP
# 00f7206f  e9 7c000000     jmp  NOTFOUND               ; 未命中→保持+0x198=0
# 00f72074  FOUND: 8b0d b8d19600 mov ecx,[0x96D1B8]
# 00f7207a  8b44 2404       mov  eax,[esp+4]
# 00f7207e  69c0 b8000000   imul eax,eax,0xB8
# 00f72084  03c8            add  ecx,eax                ; def
# 00f72086  c786 24020000 80b54800  mov [esi+0x224],0x48B580  ; mover
# 00f72090  898e 98010000   mov  [esi+0x198],ecx        ; def 指针
# 00f72096  8b41 20         mov  eax,[ecx+0x20]
# 00f72099  8986 90010000   mov  [esi+0x190],eax
# 00f7209f  8b41 24         mov  eax,[ecx+0x24]         ; 拾取应用回调
# 00f720a2  8986 94010000   mov  [esi+0x194],eax
# 00f720a8  c686 9c01000000 mov  byte[esi+0x19c],0
# 00f720af  c686 9d01000000 mov  byte[esi+0x19d],0
# 00f720b6  66c786 9e010000 0000 mov word[esi+0x19e],0  ; 关键:阻止0x48C8A0
# 00f720bf  c786 30020000 00000000 mov [esi+0x230],0
# 00f720c9  8b81 b4000000   mov  eax,[ecx+0xB4]         ; 必须 disp32（0xB4>0x7F）
# 00f720cf  85c0            test eax,eax
# 00f720d1  76 09           jbe  NEG (0xf720dc)
# 00f720d3  48              dec  eax
# 00f720d4  8986 a0010000   mov  [esi+0x1a0],eax        ; 可拾取次数
# 00f720da  eb 0a           jmp  CHAMBER (0xf720e6)
# 00f720dc  NEG: c786 a0010000 ffffffff  mov [esi+0x1a0],-1
# 00f720e6  CHAMBER: c786 8c010000 00000000  mov [esi+0x18c],0  ; 上膛
# 00f720f0  NOTFOUND: 83c4 08  add esp,8
# 00f720f3  L3: 8b4e 28     mov  ecx,[esi+0x28]         ; 复刻被挂钩覆盖的现场
# 00f720f6  85c9            test ecx,ecx
# 00f720f8  8b86 98010000   mov  eax,[esi+0x198]
# 00f720fe  e9 afde53ff     jmp  0x4AFFB2
# 00f72103  L4: e9 9fe153ff jmp  0x4B02A7
CAVE = bytes.fromhex(
    "8b8698010000" "85c0" "0f85e5000000"
    "8b4e28" "85c9" "0f84ea000000"
    "83ec08"
    "a1b0d19600" "85c0" "0f8ec7000000"
    "8b4624" "0590070000" "890424" "c744240400000000"
    "8b442404" "69c0b8000000" "8b0db8d19600" "03c8"
    "51" "ff742404" "e8181565ff" "83c408" "85c0" "7415"
    "ff442404" "8b442404" "3b05b0d19600" "7ccd" "e97c000000"
    "8b0db8d19600" "8b442404" "69c0b8000000" "03c8"
    "c78624020000" "80b54800"
    "898e98010000"
    "8b4120" "898690010000"
    "8b4124" "898694010000"
    "c6869c01000000"
    "c6869d01000000"
    "66c7869e010000" "0000"
    "c78630020000" "00000000"
    "8b81b4000000" "85c0" "7609"
    "48" "8986a0010000" "eb0a"
    "c786a0010000" "ffffffff"
    "c7868c010000" "00000000"
    "83c408"
    "8b4e28" "85c9" "8b8698010000"
    "e9afde53ff"
    "e99fe153ff"
)


def v2f(va: int) -> int:
    """DFBHD.exe 全节满足 file_offset = VA - 0x400000"""
    return va - IMAGE_BASE


def main() -> None:
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    src = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else os.path.join(
        os.path.dirname(os.path.abspath(src)), "DFBHD_satchel_powerup_v2.exe")

    data = bytearray(open(src, "rb").read())
    md5 = hashlib.md5(bytes(data)).hexdigest()
    if md5 == V2_MD5:
        print("already patched (v2), abort:", src)
        sys.exit(1)
    assert len(data) == ORIG_SIZE, f"size {len(data)} != {ORIG_SIZE}"
    assert md5 == ORIG_MD5, f"md5 {md5} != {ORIG_MD5} (需要原版 exe)"
    assert len(CAVE) == 264

    # ---- PE 头解析 ----
    lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    assert data[lfanew:lfanew + 4] == b"PE\0\0"
    nsec   = struct.unpack_from("<H", data, lfanew + 6)[0]
    sizeopt = struct.unpack_from("<H", data, lfanew + 20)[0]
    opt    = lfanew + 24
    sect   = opt + sizeopt
    assert nsec == 7, f"nsec={nsec}, 可能已被打过补丁"
    assert struct.unpack_from("<I", data, opt + 56)[0] != NEW_SIZEOFIMAGE

    new_entry = sect + 40 * nsec
    assert new_entry + 40 <= CAVE_RAW, "节表新条目越界"
    assert bytes(data[new_entry:new_entry + 40]) == b"\x00" * 40, "节表空位非零"

    # ---- 新节 .joext ----
    entry = b".joext\0\0" + struct.pack(
        "<IIIIIIHHI", 264, CAVE_RVA, CAVE_RSIZE, CAVE_RAW,
        0, 0, 0, 0, 0x60000020)
    data[new_entry:new_entry + 40] = entry
    struct.pack_into("<H", data, lfanew + 6, nsec + 1)
    struct.pack_into("<I", data, opt + 56, NEW_SIZEOFIMAGE)

    # ---- 洞代码 ----
    if len(data) < CAVE_RAW + CAVE_RSIZE:
        data += b"\x00" * (CAVE_RAW + CAVE_RSIZE - len(data))
    data[CAVE_RAW:CAVE_RAW + len(CAVE)] = CAVE

    # ---- 挂钩 ----
    off = v2f(HOOK_VA)
    assert bytes(data[off:off + 5]) == HOOK_ORIG, "hook 点字节不符"
    assert bytes(data[v2f(BACK_VA - 6):v2f(BACK_VA - 6) + 12]) == CTX_ORIG
    rel = CAVE_VA - (HOOK_VA + 5)
    data[off:off + 5] = b"\xe9" + struct.pack("<i", rel)

    open(out, "wb").write(bytes(data))

    # ---- 回读校验 ----
    chk = open(out, "rb").read()
    assert chk[CAVE_RAW:CAVE_RAW + 264] == CAVE
    assert chk[off:off + 5] == b"\xe9" + struct.pack("<i", rel)
    assert struct.unpack_from("<H", chk, struct.unpack_from("<I", chk, 0x3C)[0] + 6)[0] == 8
    print(f"out: {out}")
    print(f"size {len(chk)} MD5 {hashlib.md5(chk).hexdigest().upper()}")
    print(f"hook {HOOK_VA:08X} -> cave {CAVE_VA:08X}, back {BACK_VA:08X}, skip {SKIP_VA:08X}")


if __name__ == "__main__":
    main()
