#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Medpack self-heal patcher for Joint Operations (jointops.exe).

NOPs the 2-byte "current player == thrower -> skip healing" jump at the top
of the Medic killzone handler, so a medpack also heals the player who
threw it.

The patch is a 2-byte edit (74 63 -> 90 90): no added code, no size change,
damage-type killzones (satchel/C4/etc.) are untouched.

Patch point (file_offset = VA - 0x400000 holds for every section):
  jointops.exe : 0xE67A8  74 63 -> 90 90   (self-heal)

Usage:
  python patch_medpack_selfheal_JO.py <jointops.exe> [output path]

The patch is idempotent: if the bytes are already patched, nothing is done.
"""

import hashlib
import os
import sys

TARGET_NAME = "JointOps"
TARGET_SIZE = 4612096
ORIG_MD5 = "CB19DCAAFEFF25D5518A49EC9AFAD420"

# (offset, original bytes, patched bytes)
GATES = [
    (0xE67A8, b"\x74\x63", b"\x90\x90"),   # self-heal gate
]


def md5(data: bytes) -> str:
    return hashlib.md5(data).hexdigest().upper()


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__)
        return 1

    src = sys.argv[1]
    data = open(src, "rb").read()
    digest = md5(data)

    if len(data) != TARGET_SIZE:
        print(f"Error: file size {len(data)} does not match jointops.exe "
              f"({TARGET_SIZE}).")
        return 2

    if digest != ORIG_MD5:
        print(f"Warning: MD5 differs from the known original "
              f"(expected {ORIG_MD5}, got {digest}).")

    patched = bytearray(data)
    allowed = set()
    applied = 0
    for off, orig, new in GATES:
        cur = bytes(patched[off:off + 2])
        if cur == orig:
            patched[off:off + 2] = new
            applied += 1
        elif cur != new:
            print(f"Error: bytes at 0x{off:X} are {cur.hex()}, expected "
                  f"{orig.hex()} (unpatched) or {new.hex()} (patched).")
            print("File looks like a different version; aborting.")
            return 3
        allowed.update({off, off + 1})

    # Safety check: only gate bytes may differ.
    diff = [i for i in range(len(data)) if data[i] != patched[i]]
    assert set(diff) <= allowed, f"Unexpected diff: {[hex(d) for d in diff]}"
    if not diff:
        print(f"Input is already fully patched (MD5 {digest}); nothing to do.")
        return 0

    if len(sys.argv) >= 3:
        dst = sys.argv[2]
    else:
        root, ext = os.path.splitext(src)
        dst = f"{root}_medpack_selfheal{ext or '.exe'}"
    os.makedirs(os.path.dirname(os.path.abspath(dst)), exist_ok=True)
    open(dst, "wb").write(bytes(patched))

    print(f"Target        : {TARGET_NAME}")
    print(f"Gates applied : {applied} of {len(GATES)}")
    for off, orig, new in GATES:
        state = "applied" if bytes(data[off:off + 2]) == orig else "already"
        print(f"  0x{off:06X}  {orig.hex()} -> {new.hex()}  ({state})")
    print(f"File size     : {len(patched)} (unchanged)")
    print(f"Original MD5  : {digest}")
    print(f"Patched MD5   : {md5(bytes(patched))}")
    print(f"Output        : {dst}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
