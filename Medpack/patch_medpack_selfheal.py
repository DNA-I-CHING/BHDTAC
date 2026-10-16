#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Medpack self-heal patcher (JointOps / Delta Force: Black Hawk Down, same engine).

How it works: NOPs out the 2-byte "current player == thrower -> skip healing"
conditional jump at the top of the Medic killzone handler, so a medpack can
also heal the player who threw it. Only 2 bytes change: no added code, no
size change, damage-type killzones (satchel/C4/etc.) are untouched.

Patch points (file_offset = VA - 0x400000 holds for every section in both exes):
  jointops.exe : VA 0x4E67A8 / file offset 0xE67A8  original bytes 74 63 (je 0x4e680d)
  DFBHD.exe    : VA 0x492EF9 / file offset 0x92EF9  original bytes 74 68 (je 0x492f63)

Usage:
  python patch_medpack_selfheal_en.py <original exe> [output path]
  The target is auto-detected by matching file size + gate bytes.
  Without an output path, writes <name>_medpack_selfheal.exe next to the input.
"""

import hashlib
import os
import sys

TARGETS = [
    {
        "name": "JointOps",
        "gate_off": 0xE67A8,          # file offset (= VA 0x4E67A8 - 0x400000)
        "orig_bytes": b"\x74\x63",    # je 0x4e680d (skip healing)
        "patch_bytes": b"\x90\x90",
        "orig_md5": "CB19DCAAFEFF25D5518A49EC9AFAD420",
        "size": 4612096,
    },
    {
        "name": "DFBHD (Black Hawk Down)",
        "gate_off": 0x92EF9,          # file offset (= VA 0x492EF9 - 0x400000)
        "orig_bytes": b"\x74\x68",    # je 0x492f63 (skip healing)
        "patch_bytes": b"\x90\x90",
        "orig_md5": "D6F51AD03CA62F040586B8B5E3CA8181",
        "size": 2547712,
    },
]

# MD5s of already-patched binaries, so re-running on them is a no-op.
PATCHED_MD5 = ("39C22F7566F2EE5CC1DC3AECED9926C3", "AC1CC9518F1651FF1BAF31044D497CBB")


def md5(data: bytes) -> str:
    return hashlib.md5(data).hexdigest().upper()


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__)
        return 1

    src = sys.argv[1]
    data = open(src, "rb").read()
    digest = md5(data)

    # Bail out early if the input is already a patched build.
    if digest in PATCHED_MD5:
        print(f"Input is already patched (MD5 {digest}); nothing to do.")
        return 0

    target = None
    for t in TARGETS:
        # Identify the game by file size plus the expected gate instruction.
        if len(data) == t["size"] and data[t["gate_off"]:t["gate_off"] + 2] == t["orig_bytes"]:
            target = t
            break
    if target is None:
        print("Error: unrecognized target (file size or gate bytes match no known version).")
        print("Make sure you passed an UNPATCHED jointops.exe or DFBHD.exe.")
        return 2

    if digest != target["orig_md5"]:
        print(f"Warning: MD5 differs from the known original "
              f"(expected {target['orig_md5']}, got {digest}).")
        print("Version may differ, but the gate bytes match; proceeding anyway.")

    patched = bytearray(data)
    patched[target["gate_off"]:target["gate_off"] + 2] = target["patch_bytes"]

    # Safety check: exactly the 2 gate bytes may differ.
    diff = [i for i in range(len(data)) if data[i] != patched[i]]
    assert diff == [target["gate_off"], target["gate_off"] + 1], f"Unexpected diff: {[hex(d) for d in diff]}"

    if len(sys.argv) >= 3:
        dst = sys.argv[2]
    else:
        root, ext = os.path.splitext(src)
        dst = f"{root}_medpack_selfheal{ext or '.exe'}"
    os.makedirs(os.path.dirname(os.path.abspath(dst)), exist_ok=True)
    open(dst, "wb").write(bytes(patched))

    print(f"Target        : {target['name']}")
    print(f"Patch point   : file offset 0x{target['gate_off']:X}  "
          f"{target['orig_bytes'].hex()} -> {target['patch_bytes'].hex()}")
    print(f"File size     : {len(patched)} (unchanged)")
    print(f"Original MD5  : {digest}")
    print(f"Patched MD5   : {md5(bytes(patched))}")
    print(f"Output        : {dst}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
