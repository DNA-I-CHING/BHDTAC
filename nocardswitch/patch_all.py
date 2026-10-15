"""
BHD binary patch — real 3-D iron sights for Sighted weapons
=============================================================

Target: DFBHD.exe  (Delta Force: Black Hawk Down, PE32 / x86, image base 0x400000)
Original SHA-256: 4ce49ba04993ebed5ccef631050ddb87c113b47ec2f2b12f7803380f70846026

Symptom
-------
Weapons carrying `flags Sighted` make the first-person model vanish on
right-click. The model is not hidden by a flag and not pushed off-screen:
it enters the texture-sight state on arrival at `tpos`.

Root cause
----------
Right-click is `case 6` in FUN_00489CC0 (0x489CFF) -> FUN_00488CC0 (0x488CC0).
That function gates on `flags & 3` and interpolates pos <-> tpos, but on arrival
the engine derives the aim-state flag from a second variable:

    00487719  mov   ecx, dword ptr [0x96B668]   ; b668
    0048771F  xor   eax, eax
    00487721  cmp   ecx, ebx                    ; ebx = 0
    00487723  setne al
    0048772C  mov   dword ptr [0x96C3E0], eax   ; c3e0 = (b668 != 0)

DAT_0096C3E0 is cleared in seven places and set in exactly one — the line above.
Both flag queries then multiply by it:

    FUN_00488D90  (Scoped)   ->  -(flags & 1) & c3e0
    FUN_00488DC0  (Sighted)  ->  -(flags & 2) & c3e0

so once c3e0 == 1 with Sighted set, the whole texture-sight pipeline arms
(FOV compression, post-processing, scope HUD, pixel masking) and the
first-person model yields to the overlay.

`Sighted` is read in only two places in the binary (the helpers above). All nine
call sites were decompiled; every one is FOV / post-processing / HUD / pixel-mask
/ effect related. None gates 3-D model visibility. The flag decides whether the
model *moves*; the disappearance is a side effect of entering the texture-sight
state.

Patches (2 coordinated edits, 5 bytes)
--------------------------------------
[1] VA 0x487723  file offset 0x87723
    0F 95 C0   setne al        ->   31 C0 90   xor eax,eax ; nop
    Forces c3e0 to stay 0, so FUN_00488D90 / FUN_00488DC0 always return 0 and
    the texture-sight pipeline never arms.

[2] VA 0x488CFF  file offset 0x88CFF
    8B 15 E0 C3 96 00   mov edx,[0x96C3E0]   ->   8B 15 68 B6 96 00   mov edx,[0x96B668]
    The leave-sight branch in FUN_00488CC0 tests this operand:

        00488CFF  mov  edx, [operand]
        00488D05  test edx, edx
        00488D07  je   0x488D56      ; zero -> "enter sight"

    With [1] alone, c3e0 would never be set and this branch would be
    unreachable, leaving the model stuck at tpos. DAT_0096B668 carries the same
    information independently of the texture-sight pipeline.

Why DAT_0096B668 and not DAT_0096B66C
-------------------------------------
The two are one digit apart in name and mean opposite things. Both verified by
enumerating every read and write:

    DAT_0096B668   0 = hip-fire, 1 = sighted        <- current state
        init 0x4871FD = 0; enter 0x488D56 = 1; leave 0x488D39 = 0

    DAT_0096B66C   0 = heading to tpos, 1 = returning   <- motion direction
        init 0x4871F5 = 1; enter 0x488D82 = 0; leave 0x488D4D = 1

An earlier revision used 0x96B66C and failed: at tpos, b66c == 0, so the `je`
branched back into "enter sight" and the model kept re-running pos -> tpos.
0x96B668 is the correct substitute.

Verified toggle sequence
------------------------
    initial      b668=0  b66c=1  c3e0=0
    press RMB    b668=1  b66c=0  c3e0=0   enter branch, b280(15, pos, tpos)
    arrival      b668=1  b66c=0  c3e0=0   helpers return 0 -> 3-D sights
    press RMB    b668=0  b66c=1  c3e0=0   je not taken -> leave branch, b280(tpos, pos)
    press RMB    b668=0  b66c=1  c3e0=0   cycle repeats

Preserved
---------
    * FUN_00488D90 / FUN_00488DC0 bodies untouched (their other four callers,
      including AI audio, are unaffected)
    * FUN_0048B280 interpolation untouched (pos <-> tpos animation unchanged)
    * Other gates in FUN_00488CC0 untouched: 0x488CE7 (flags & 3),
      0x488CF9 (b664 occupancy)
    * FUN_00487270 switch/reset path untouched

Notes
-----
    .text has rawoff == RVA, so file_offset = VA - 0x400000.
    Every site is byte-checked against the expected original before writing;
    the script aborts on any mismatch and is safe to re-run.
"""
import hashlib
import shutil
import sys
from pathlib import Path

EXE = Path(r"D:\360Downloads\△\BHD\DFBHD.exe")
OUT = Path(__file__).resolve().parent / "DFBHD_3Daim_patched.exe"
BACKUP = EXE.with_suffix(".exe.orig")

ORIG_SHA256 = "4ce49ba04993ebed5ccef631050ddb87c113b47ec2f2b12f7803380f70846026"

PATCHES = [
    (0x87723, bytes.fromhex("0f 95 c0"), bytes.fromhex("31 c0 90"),
     "0x487723 setne al -> xor eax,eax ; nop  (c3e0 stays 0, no texture-sight state)"),
    (0x88CFF, bytes.fromhex("8b 15 e0 c3 96 00"), bytes.fromhex("8b 15 68 b6 96 00"),
     "0x488CFF mov edx,[0x96C3E0] -> mov edx,[0x96B668]  (exit test uses sighted state)"),
]


def sha256(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


def main() -> int:
    if not EXE.exists():
        print(f"[!] not found: {EXE}")
        return 1

    data = bytearray(EXE.read_bytes())
    h = sha256(bytes(data))
    if h != ORIG_SHA256:
        if BACKUP.exists() and sha256(BACKUP.read_bytes()) == ORIG_SHA256:
            print("[!] target is not the original build; restoring from backup first")
            shutil.copy2(BACKUP, EXE)
            data = bytearray(EXE.read_bytes())
            print("[+] restored, hash:", sha256(bytes(data)))
        else:
            print(f"[!] refusing to patch, unexpected hash:\n    got      {h}\n"
                  f"    expected {ORIG_SHA256}")
            return 1
    print(f"[+] source: original build ({h[:16]}...)")

    # verify every site before touching the file
    pending, done = [], []
    for off, expect, repl, desc in PATCHES:
        cur = bytes(data[off:off + len(expect)])
        if cur == repl:
            done.append(desc)
        elif cur == expect:
            pending.append((off, expect, repl, desc))
        else:
            print(f"[!] site {off:#x} does not match: expected {expect.hex(' ')}, "
                  f"found {cur.hex(' ')}")
            print("[!] aborted, nothing written")
            return 1

    for d in done:
        print(f"[=] already patched: {d}")
    if not pending:
        print("[!] nothing to do")
        return 1

    if not BACKUP.exists():
        shutil.copy2(EXE, BACKUP)
        print(f"[+] backup created: {BACKUP}")

    for off, expect, repl, desc in pending:
        data[off:off + len(repl)] = repl
        print(f"[+] {off:#x}: {expect.hex(' ')} -> {repl.hex(' ')}")
        print(f"    {desc}")

    OUT.write_bytes(bytes(data))
    print(f"[+] wrote {OUT} ({len(data)} bytes)")
    print(f"[+] sha256: {sha256(bytes(data))}")
    return 0


if __name__ == "__main__":
    sys.exit(main())