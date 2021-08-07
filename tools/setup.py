#!/usr/bin/env python3

import argparse
import hashlib
import platform
from pathlib import Path
import subprocess
import sys
import tarfile
import tempfile
import urllib.request
from common import setup_common as setup


def _download_v160_to_v150_patch(dest: Path):
    print(">>>> downloading patch...")
    urllib.request.urlretrieve("https://s.botw.link/v150_downgrade/v160_to_v150.patch", dest)


def prepare_executable(original_nso: Path):
    COMPRESSED_V150_HASH = "898dc199301f7c419be5144bb5cb27e2fc346e22b27345ba3fb40c0060c2baf8"
    UNCOMPRESSED_V150_HASH = "d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106"
    COMPRESSED_V160_HASH = "15cfca7b89348956f85d945fade2e215a6af5991ed1071e181f97ca72f7ae20b"
    UNCOMPRESSED_V160_HASH = "8a2fc8b1111a35a76fd2d53a8670599da4a7a9706a3d91215d30fd62149f00c1"

    # The uncompressed v1.5.0 main NSO.
    TARGET_HASH = UNCOMPRESSED_V150_HASH

    if setup.TARGET_PATH.is_file() and hashlib.sha256(setup.TARGET_PATH.read_bytes()).hexdigest() == TARGET_HASH and setup.TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    if nso_hash == UNCOMPRESSED_V150_HASH:
        print(">>> found uncompressed 1.5.0 NSO")
        setup.TARGET_PATH.write_bytes(nso_data)

    elif nso_hash == COMPRESSED_V150_HASH:
        print(">>> found compressed 1.5.0 NSO")
        setup._decompress_nso(original_nso, setup.TARGET_PATH)

    elif nso_hash == UNCOMPRESSED_V160_HASH:
        print(">>> found uncompressed 1.6.0 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            _download_v160_to_v150_patch(patch_path)
            setup._apply_xdelta3_patch(original_nso, patch_path, setup.TARGET_PATH)

    elif nso_hash == COMPRESSED_V160_HASH:
        print(">>> found compressed 1.6.0 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            decompressed_nso_path = Path(tmpdir) / "v160.nso"

            setup._decompress_nso(original_nso, decompressed_nso_path)
            _download_v160_to_v150_patch(patch_path)
            setup._apply_xdelta3_patch(decompressed_nso_path, patch_path, setup.TARGET_PATH)

    else:
        setup.fail(f"unknown executable: {nso_hash}")

    if not setup.TARGET_PATH.is_file():
        setup.fail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(setup.TARGET_PATH.read_bytes()).hexdigest() != TARGET_HASH:
        setup.fail("internal error while preparing executable (wrong NSO hash); please report")

    setup._convert_nso_to_elf(setup.TARGET_PATH)

    if not setup.TARGET_ELF_PATH.is_file():
        setup.fail("internal error while preparing executable (missing ELF); please report")

def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the Breath of the Wild decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO (1.5.0 or 1.6.0, compressed or not)")
    args = parser.parse_args()

    prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    setup.create_build_dir()


if __name__ == "__main__":
    main()
