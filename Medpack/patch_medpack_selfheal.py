#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Medpack patcher (JointOps / Delta Force: Black Hawk Down, same engine).

Default mode (self-heal): NOPs the 2-byte "current player == thrower -> skip
healing" jump at the top of the Medic killzone handler, so a medpack also
heals the player who threw it.

DFBHD only, --allclasses mode: additionally bypasses the two class gates that
restrict medpack healing to the Medic class (and break it in single player),
so ANY class in ANY mode heals:
  - dispatch gate: class-ability lookup 0x418ec0(class byte, 8) at kztype=3
    case; in single player the class table pointer [0x715b48] is NULL so the
    check always fails and the Medic handler is never loaded.
  - apply gates: heal function 0x4AF0D0 and revive function 0x4AEE40 both
    require the thrower's class id to be 6 or 0xA (Medic) before applying.

All patches are 2-byte edits (NOP or je->jmp): no added code, no size change,
damage-type killzones (satchel/C4/etc.) are untouched.

Patch points (file_offset = VA - 0x400000 holds for every section in both exes):
  jointops.exe : 0xE67A8  74 63 -> 90 90   (self-heal)
  DFBHD.exe    : 0x92EF9  74 68 -> 90 90   (self-heal)
                 0x936E0  74 12 -> 90 90   (dispatch class-ability gate)
                 0xAF13D  74 09 -> EB 09   (heal-apply class gate)
                 0xAEEF3  74 09 -> EB 09   (revive class gate)

Usage:
  python patch_medpack_selfheal.py <original exe> [output path] [--allclasses]
  Target is auto-detected by file size. The patch is idempotent: gates that
  are already patched are skipped, so --allclasses can be applied on top of
  an existing self-heal build.
"""

import hashlib
import os
import sys

TARGETS = [
    {
        "name": "JointOps",
        "size": 4612096,
        "orig_md5": "CB19DCAAFEFF25D5518A49EC9AFAD420",
        "selfheal": [(0xE67A8, b"\x74\x63", b"\x90\x90")],
        "extra": [],
    },
    {
        "name": "DFBHD (Black Hawk Down)",
        "size": 2547712,
        "orig_md5": "D6F51AD03CA62F040586B8B5E3CA8181",
        "selfheal": [(0x92EF9, b"\x74\x68", b"\x90\x90")],
        "extra": [
            (0x936E0, b"\x74\x12", b"\x90\x90"),   # dispatch class-ability gate
            (0xAF13D, b"\x74\x09", b"\xeb\x09"),   # heal-apply class gate
            (0xAEEF3, b"\x74\x09", b"\xeb\x09"),   # revive class gate
        ],
    },
]


def md5(data: bytes) -> str:
    return hashlib.md5(data).hexdigest().upper()


def main() -> int:
    args = [a for a in sys.argv[1:] if a != "--allclasses"]
    allclasses = "--allclasses" in sys.argv[1:]
    if not args:
        print(__doc__)
        return 1

    src = args[0]
    data = open(src, "rb").read()
    digest = md5(data)

    target = next((t for t in TARGETS if len(data) == t["size"]), None)
    if target is None:
        print("Error: file size matches no known version.")
        print("Make sure you passed jointops.exe or DFBHD.exe.")
        return 2
    if allclasses and not target["extra"]:
        print(f"Note: {target['name']} has no class gates; --allclasses ignored.")
        allclasses = False

    if digest != target["orig_md5"]:
        print(f"Warning: MD5 differs from the known original "
              f"(expected {target['orig_md5']}, got {digest}).")

    gates = target["selfheal"] + (target["extra"] if allclasses else [])
    patched = bytearray(data)
    allowed = set()
    applied = 0
    for off, orig, new in gates:
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

    if len(args) >= 2:
        dst = args[1]
    else:
        root, ext = os.path.splitext(src)
        suffix = "_medpack_allclasses" if allclasses else "_medpack_selfheal"
        dst = f"{root}{suffix}{ext or '.exe'}"
    os.makedirs(os.path.dirname(os.path.abspath(dst)), exist_ok=True)
    open(dst, "wb").write(bytes(patched))

    print(f"Target        : {target['name']}{' + all-classes' if allclasses else ''}")
    print(f"Gates applied : {applied} of {len(gates)}")
    for off, orig, new in gates:
        state = "applied" if bytes(data[off:off + 2]) == orig else "already"
        print(f"  0x{off:06X}  {orig.hex()} -> {new.hex()}  ({state})")
    print(f"File size     : {len(patched)} (unchanged)")
    print(f"Original MD5  : {digest}")
    print(f"Patched MD5   : {md5(bytes(patched))}")
    print(f"Output        : {dst}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
