#!/usr/bin/env python3
"""Verify the exact V16 input engine and a diagnostic APK payload."""

from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import zipfile

EXPECTED_APK_SHA256 = "f8d30149d0a4c93829d1fde873a4860f1a0f833c01dd7c9312ea07a7f438393e"
EXPECTED_LIBG_SHA256 = "0b580222e5a3502cf153bb5e6297ec32d2b154b605b777c74873dd75722e4eaa"
LIBG_MEMBER = "lib/arm64-v8a/libg.so"
PROBE_MEMBER = "lib/arm64-v8a/libcrprobe.so"


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def verify_input(apk: Path) -> dict:
    apk_hash = hashlib.sha256(apk.read_bytes()).hexdigest()
    if apk_hash != EXPECTED_APK_SHA256:
        raise ValueError(f"V16 input APK SHA-256 mismatch: {apk_hash}")
    with zipfile.ZipFile(apk) as archive:
        libg = archive.read(LIBG_MEMBER)
    libg_hash = sha256_bytes(libg)
    if libg_hash != EXPECTED_LIBG_SHA256:
        raise ValueError(f"V16 input libg SHA-256 mismatch: {libg_hash}")
    return {"apk_sha256": apk_hash, "libg_sha256": libg_hash}


def verify_output(apk: Path, probe: Path) -> dict:
    expected_probe = hashlib.sha256(probe.read_bytes()).hexdigest()
    with zipfile.ZipFile(apk) as archive:
        libg_hash = sha256_bytes(archive.read(LIBG_MEMBER))
        probe_hash = sha256_bytes(archive.read(PROBE_MEMBER))
    if libg_hash != EXPECTED_LIBG_SHA256:
        raise ValueError(f"Output APK contains unexpected libg.so: {libg_hash}")
    if probe_hash != expected_probe:
        raise ValueError(f"Output APK probe differs from build output: {probe_hash}")
    return {
        "schema": "firstlight-v16-probe-diagnostics.v1",
        "apk_sha256": hashlib.sha256(apk.read_bytes()).hexdigest(),
        "libg_sha256": libg_hash,
        "probe_sha256": probe_hash,
        "mode": "diagnostics-only-no-hooks",
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("input", "output"))
    parser.add_argument("--apk", type=Path, required=True)
    parser.add_argument("--probe", type=Path)
    args = parser.parse_args()
    if args.mode == "input":
        result = verify_input(args.apk)
    else:
        if args.probe is None:
            parser.error("--probe is required in output mode")
        result = verify_output(args.apk, args.probe)
        args.apk.with_suffix(".v16-diagnostics.json").write_text(
            json.dumps(result, indent=2) + "\\n", encoding="utf-8"
        )
    print(json.dumps(result, indent=2), flush=True)


if __name__ == "__main__":
    main()
