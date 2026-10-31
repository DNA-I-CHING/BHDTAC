# -*- coding: utf-8 -*-
"""
DFBHD-series bullet wind-drift patch generator
Target: Delta Force Black Hawk Down, DFBHD.exe v1.5.0.5 (32-bit PE)

Background:
  The bullet mover 0x491B00 calls the drag function 0x491930 every frame. For the
  default projectile types drag==0x10000, so the function returns immediately at
  0x491959 and the wind vector globals (0xE19DC0/DC4) never reach bullet velocity.
  This patch turns the 0x491930 entry into a jmp to a cave in the _TEXT section at
  0x610010, injecting:
      vx += wind_x >> K   (+0x6C)
      vy += wind_y >> K   (+0x70)
  then jumps back to 0x491937 to continue the original logic.

Usage:
  python 2.py <original exe>              # interactive tier prompt, builds one tier
  python 2.py <original exe> --sar 5      # tier given on the command line (non-interactive)
  python 2.py <original exe> -o <outdir>  # output directory (default: script directory)
  python 2.py --unpatch <patched file>    # restore a patched file

Tiers: wind per tick = fullwind / 2^K; larger K = weaker wind. Output is always
named DFBHD_wind_K{tier}.exe (no LAAM or other tags). Artifacts are written only
to the output directory - never into the game directory. All players in an online
match must run the same tier.

See the analysis reports Wind_Bullet_zh-CN.md / Wind_Bullet_en.md for details.
"""
import argparse, os, sys

# ---- Constants (valid for v1.5.0.5 only) ----
HOOK_VA   = 0x491930          # drag function entry
HOOK_ORIG = bytes.fromhex('558BEC518B')   # first 5 bytes of: push ebp; mov ebp,esp; push ecx; mov ecx,[ebp+8]
RESUME_VA = 0x491937          # jump-back target (after replaying the 7-byte prologue)
CAVE_VA   = 0x610010          # cave in _TEXT section (VA 0x610000, RawSize 0x1000, RWX, tail all-zero)
CAVE_FILE = 0x210010          # file offset of the cave
WIND_X_G  = 0xE19DC0          # wind vector globals (16.16 fixed point)
WIND_Y_G  = 0xE19DC4
VX_OFS, VY_OFS = 0x6C, 0x70   # per-instance bullet velocity fields
TEXT_RVA_DELTA = 0x400000     # in this exe both .text and _TEXT satisfy VA-0x400000=file offset
# Cave layout: 7B prologue + (mov5 + sar3 + add3) x 2 + jmp5 = 34 bytes
CAVE_LEN  = 34


def build_cave(sar: int) -> bytes:
    """Build the injected code: replay prologue + two-axis wind acceleration + jmp back."""
    if not 0 <= sar <= 31:
        sys.exit('--sar must be in 0..31')
    cave = bytearray()
    cave += bytes.fromhex('558BEC518B4D08')                       # replay the overwritten 7-byte prologue
    for g, ofs in ((WIND_X_G, VX_OFS), (WIND_Y_G, VY_OFS)):
        cave += b'\xA1' + g.to_bytes(4, 'little')                 # mov eax,[wind_g]
        cave += b'\xC1\xF8' + bytes([sar])                        # sar eax,sar
        cave += b'\x01\x41' + bytes([ofs])                        # add [ecx+ofs],eax
    # jmp back to RESUME_VA (relative to the cave's actual position)
    rel = RESUME_VA - (CAVE_VA + len(cave) + 5)
    cave += b'\xE9' + (rel & 0xFFFFFFFF).to_bytes(4, 'little')
    assert len(cave) == CAVE_LEN, 'unexpected cave length'
    return bytes(cave)


def apply_patch(data: bytearray, sar: int) -> bytes:
    """Patch an in-memory image (original bytes are verified by the caller); returns cave bytes."""
    ho = HOOK_VA - TEXT_RVA_DELTA
    rel = CAVE_VA - (HOOK_VA + 5)
    data[ho:ho + 5] = b'\xE9' + (rel & 0xFFFFFFFF).to_bytes(4, 'little')
    cave = build_cave(sar)
    data[CAVE_FILE:CAVE_FILE + len(cave)] = cave
    return cave


def ask_tier() -> int:
    """Ask for the tier interactively; bare Enter = default 5. 0-31 covers every
    legal value of the sar immediate (the CPU uses only the low 5 bits)."""
    while True:
        raw = input('Enter wind tier K (0-31, wind = fullwind / 2^K, press Enter for 5): ').strip()
        if raw == '':
            return 5
        if raw.isdigit() and 0 <= int(raw) <= 31:
            return int(raw)
        print('Invalid tier. Please enter a number from 0 to 31.')


def patch(src: str, outdir: str, sar: int):
    orig = open(src, 'rb').read()
    ho = HOOK_VA - TEXT_RVA_DELTA
    # Pre-checks: file must be an unpatched original
    if orig[ho:ho + 5] != HOOK_ORIG:
        sys.exit('Hook bytes mismatch: file is not an unpatched v1.5.0.5 original (or already patched)')
    if orig[CAVE_FILE:CAVE_FILE + 48] != bytes(48):
        sys.exit('_TEXT cave region is not all-zero, aborting')
    os.makedirs(outdir, exist_ok=True)

    data = bytearray(orig)
    cave = apply_patch(data, sar)
    dst = os.path.join(outdir, 'DFBHD_wind_K%d.exe' % sar)
    open(dst, 'wb').write(bytes(data))
    # Post-check: every changed byte must fall inside the hook or the cave
    diff = [i for i in range(len(orig)) if orig[i] != data[i]]
    outside = [i for i in diff if not (ho <= i < ho + 5 or CAVE_FILE <= i < CAVE_FILE + CAVE_LEN)]
    if outside:
        sys.exit('K%d: changes found outside hook/cave: %s' % (sar, [hex(i) for i in outside[:5]]))
    print(f'OK: {dst}')
    print(f'  tier K={sar} (wind/{2**sar}), {len(diff)} bytes differ from original')

    # Disassembly verification via capstone
    try:
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        print('  hook:', ' '.join(f'{i.mnemonic} {i.op_str}' for i in md.disasm(data[ho:ho+5], HOOK_VA)))
        print('  cave:')
        for i in md.disasm(cave, CAVE_VA):
            print(f'    {i.address:#08x}  {i.mnemonic} {i.op_str}')
    except ImportError:
        print('  (install capstone to see disassembly verification)')


def unpatch(tgt: str):
    """Restore: rewrite the original hook bytes and zero the cave (rest of file untouched)."""
    data = bytearray(open(tgt, 'rb').read())
    ho = HOOK_VA - TEXT_RVA_DELTA
    if data[ho:ho + 1] != b'\xE9':
        sys.exit('No patch hook found in target, refusing to restore')
    data[ho:ho + 5] = HOOK_ORIG
    data[CAVE_FILE:CAVE_FILE + 48] = bytes(48)
    open(tgt, 'wb').write(bytes(data))
    print(f'Restored: {tgt}')


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description='DFBHD wind patch generator (v1.5.0.5): one tier per run, tier chosen interactively')
    ap.add_argument('exe', nargs='?', help='path to the original exe')
    ap.add_argument('-o', '--out', help='output directory (default: script directory, never the game directory)')
    ap.add_argument('--sar', type=int, help='tier K on the command line (omit to ask interactively, 0-31)')
    ap.add_argument('--unpatch', metavar='FILE', help='restore the given file and exit')
    a = ap.parse_args()
    if a.unpatch:
        unpatch(a.unpatch)
    elif a.exe:
        sar = a.sar if a.sar is not None else ask_tier()
        patch(a.exe, a.out or os.path.dirname(os.path.abspath(__file__)), sar)
    else:
        ap.error('expected <original exe> path (or --unpatch)')
