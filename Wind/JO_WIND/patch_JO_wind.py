# -*- coding: utf-8 -*-
"""
JO (Joint Operations: Typhoon Rising) bullet wind-drift patch generator
Target: jointops.exe (4,612,096 bytes, 32-bit PE)

Background:
  JO bullets never feel wind. Inside the drag function FUN_004e5ec0 the wind
  term is dead code (v += wind; v += decel; v -= wind nets to zero), so bullets
  fly perfectly straight no matter the weather.
  This patch turns the bullet-gravity ADD at 0x4EAA5A (mover FUN_004e9d70) into
  a CALL to a code cave at 0x7472C9 (a 55-byte cc-aligned gap inside .text),
  injecting after the replayed gravity ADD:
      vx += wind_x >> K
      vy += wind_y >> K
  The hook sits on the bullet-only gravity block (grenades take gravity from
  elsewhere), so the wind applies to bullets only, automatically.

Usage:
  python 1.py [original exe] [-o outdir] [--sar K] [--unpatch FILE]
  default source = D:\\3DM\\JOTAC\\Game\\JO\\jointops.exe (read-only; never write into the game dir)
  default output = script directory

Tiers in plain words:
  Every tick the patch adds wind / 2^K to the bullet velocity.
  JO full wind = 197 per frame = about 118% of bullet gravity.
    K=0  full 118%  - hurricane, bullets bend hard
    K=4  7.4%  (wind/16)  - clearly visible drift, recommended
    K=5  3.7%  (wind/32)  - subtle drift, recommended
    K=8  0.5%  (wind/256) - barely a breeze
  Each step up HALVES the wind. K range 0-31 covers every legal sar value.

Output: jointops_wind_K{tier}.exe. Artifacts are written only to the
output directory - never into the game directory. Online matches require all
players to run the same tier.

See JO_Wind_Patch_CN.md / JO_Wind_Patch_EN.md for the full analysis.
"""
import argparse, os, sys, hashlib

# ---- Constants (valid for this jointops.exe build only) ----
SIZE     = 4612096
HOOK_OFF = 0xEAA5A    # VA 0x004EAA5A (file offset)
CAVE_OFF = 0x3472C9   # VA 0x007472C9 (file offset)
HOOK_VA  = 0x4EAA5A
CAVE_VA  = 0x7472C9

# Original hook bytes: add [ebx+0xA0], -167 (bullet gravity, 16.16 fixed point)
HOOK_ORIG = bytes([0x81, 0x83, 0xA0, 0x00, 0x00, 0x00, 0x59, 0xFF, 0xFF, 0xFF])
# Replacement: CALL rel32 into the cave + NOP x5
HOOK_NEW  = bytes([0xE8, 0x6A, 0xC8, 0x25, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90])

# 39-byte cave template; the two tier bytes sit at idx17 / idx31
CAVE_TEMPLATE = bytes([
    0x81, 0x83, 0xA0, 0x00, 0x00, 0x00, 0x59, 0xFF, 0xFF, 0xFF,  # add [ebx+0xA0],-167  replayed original gravity ADD
    0xA1, 0xE4, 0x59, 0xC0, 0x02,                                # mov eax,[0x02C059E4]  wind_x
    0xC1, 0xF8, 0x00,                                            # sar eax,K             tier byte (idx17)
    0x01, 0x83, 0x98, 0x00, 0x00, 0x00,                          # add [ebx+0x98],eax    vx += wind
    0xA1, 0xE8, 0x59, 0xC0, 0x02,                                # mov eax,[0x02C059E8]  wind_y
    0xC1, 0xF8, 0x00,                                            # sar eax,K             tier byte (idx31)
    0x01, 0x83, 0x9C, 0x00, 0x00, 0x00,                          # add [ebx+0x9C],eax    vy += wind
    0xC3,                                                        # ret
])
CAVE_LEN = 39
# Expected byte differences vs the original: hook 9 (one CALL byte coincides) + cave 39
EXPECTED_DIFF = 48

DEFAULT_SRC = r"D:\3DM\JOTAC\Game\JO\jointops.exe"


def build_cave(sar: int) -> bytes:
    """Build the injected code: replayed gravity ADD + two-axis wind acceleration + ret."""
    if not 0 <= sar <= 31:
        sys.exit('--sar must be in 0..31')
    cave = bytearray(CAVE_TEMPLATE)
    cave[17] = sar
    cave[31] = sar
    return bytes(cave)


def apply_patch(data: bytearray, sar: int) -> bytes:
    """Patch an in-memory image (original bytes are verified by the caller); returns cave bytes."""
    data[HOOK_OFF:HOOK_OFF + 10] = HOOK_NEW
    cave = build_cave(sar)
    data[CAVE_OFF:CAVE_OFF + CAVE_LEN] = cave
    return cave


def ask_tier() -> int:
    """Ask for the tier interactively; bare Enter = default 5. 0-31 covers every
    legal value of the sar immediate (the CPU uses only the low 5 bits)."""
    print()
    print('How tiers work: every tick the patch adds wind / 2^K to bullet velocity.')
    print('  K=0 -> full wind (118% of bullet gravity, hurricane-like drift);')
    print('  each step up HALVES the wind (K=4 -> wind/16, K=5 -> wind/32, ...).')
    print('  Rule of thumb: K4/K5 = realistic noticeable drift (recommended);')
    print('                 K0 = storm, K7/K8 = barely a breeze.')
    while True:
        raw = input('Enter wind tier K (0-31, press Enter for 5): ').strip()
        if raw == '':
            return 5
        if raw.isdigit() and 0 <= int(raw) <= 31:
            return int(raw)
        print('Invalid tier. Please enter a number from 0 to 31.')


def patch(src: str, outdir: str, sar: int):
    orig = open(src, 'rb').read()
    print(f'Source: {src} ({len(orig)} bytes)')
    # Pre-checks: file must be the expected unpatched original
    if len(orig) != SIZE:
        sys.exit(f'Unexpected file size: {len(orig)} (expected {SIZE})')
    if orig[HOOK_OFF:HOOK_OFF + 10] != HOOK_ORIG:
        sys.exit(f'Hook bytes mismatch @ {HOOK_OFF:#x}: file is not the expected unpatched original (or already patched)')
    cave_region = orig[CAVE_OFF:CAVE_OFF + 55]
    if len(cave_region) != 55 or any(b != 0xCC for b in cave_region):
        sys.exit(f'Cave region @ {CAVE_OFF:#x} is not 55 bytes of 0xCC, aborting')
    os.makedirs(outdir, exist_ok=True)

    data = bytearray(orig)
    cave = apply_patch(data, sar)
    dst = os.path.join(outdir, 'jointops_wind_K%d.exe' % sar)
    open(dst, 'wb').write(bytes(data))
    # Post-checks: diff must be exactly 48 bytes, all inside hook/cave; tier bytes in place
    diff = [i for i in range(SIZE) if orig[i] != data[i]]
    if len(diff) != EXPECTED_DIFF:
        sys.exit(f'K={sar}: byte diff is {len(diff)}, expected {EXPECTED_DIFF}')
    outside = [i for i in diff
               if not (HOOK_OFF <= i < HOOK_OFF + 10 or CAVE_OFF <= i < CAVE_OFF + CAVE_LEN)]
    if outside:
        sys.exit(f'K={sar}: changes found outside hook/cave: ' + ', '.join(hex(i) for i in outside[:5]))
    if data[CAVE_OFF + 17] != sar or data[CAVE_OFF + 31] != sar:
        sys.exit(f'K={sar}: tier bytes wrong ({data[CAVE_OFF + 17]}/{data[CAVE_OFF + 31]})')
    md5 = hashlib.md5(bytes(data)).hexdigest()
    print(f'OK: {dst}')
    print(f'  tier K={sar} (wind/{2**sar}), {len(diff)} bytes differ from original, md5={md5}')

    # Disassembly verification via capstone
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        md = Cs(CS_ARCH_X86, CS_MODE_32)
        print('  hook:')
        for ins in md.disasm(HOOK_NEW, HOOK_VA):
            print(f'    {ins.address:#08x}  {ins.mnemonic} {ins.op_str}')
        print('  cave:')
        for ins in md.disasm(cave, CAVE_VA):
            print(f'    {ins.address:#08x}  {ins.mnemonic} {ins.op_str}')
    except ImportError:
        print('  (install capstone to see disassembly verification)')


def unpatch(tgt: str):
    """Restore: rewrite the original hook bytes and refill the cave with 0xCC."""
    data = bytearray(open(tgt, 'rb').read())
    if data[HOOK_OFF:HOOK_OFF + 5] != HOOK_NEW[:5]:
        sys.exit('No patch hook found in target, refusing to restore')
    data[HOOK_OFF:HOOK_OFF + 10] = HOOK_ORIG
    data[CAVE_OFF:CAVE_OFF + CAVE_LEN] = b'\xCC' * CAVE_LEN
    open(tgt, 'wb').write(bytes(data))
    print(f'Restored: {tgt}')


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description='JO wind patch generator: one tier per run, tier chosen interactively')
    ap.add_argument('exe', nargs='?', default=DEFAULT_SRC, help='path to the original jointops.exe (default: %(default)s)')
    ap.add_argument('-o', '--out', help='output directory (default: script directory, never the game directory)')
    ap.add_argument('--sar', type=int, help='tier K on the command line (omit to ask interactively, 0-31)')
    ap.add_argument('--unpatch', metavar='FILE', help='restore the given file and exit')
    a = ap.parse_args()
    if a.unpatch:
        unpatch(a.unpatch)
    else:
        sar = a.sar if a.sar is not None else ask_tier()
        patch(a.exe, a.out or os.path.dirname(os.path.abspath(__file__)), sar)
