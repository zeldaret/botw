#!/usr/bin/env python3

import argparse
import hashlib
from pathlib import Path
import subprocess
import tempfile
import urllib.request
from typing import Optional
from common import setup_common as setup


TARGET_PATH = setup.get_target_path()
TARGET_ELF_PATH = setup.get_target_elf_path()


def _download_v181_to_v150_patch(dest: Path):
    print(">>>> downloading patch...")
    urllib.request.urlretrieve("https://s.botw.link/v150_downgrade/v181_to_v150.patch", dest)


def prepare_executable(original_nso: Optional[Path]):
    COMPRESSED_V150_HASH = "898dc199301f7c419be5144bb5cb27e2fc346e22b27345ba3fb40c0060c2baf8"
    UNCOMPRESSED_V150_HASH = "d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106"
    COMPRESSED_V181_HASH = "92a2ff88205a00ba3eaaf7c1cd3e247220c93eafefa48d7b7b1d6b97e444bb5e"
    UNCOMPRESSED_V181_HASH = "efccff3dd89599f54d7889e339b240565ad4a21c6478a7264808b702a7d264c4"

    # The uncompressed v1.5.0 main NSO.
    TARGET_HASH = UNCOMPRESSED_V150_HASH

    if TARGET_PATH.is_file() and hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() == TARGET_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if original_nso is None:
        setup.fail("please pass a path to the NSO (refer to the readme for more details)")

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    if nso_hash == UNCOMPRESSED_V150_HASH:
        print(">>> found uncompressed 1.5.0 NSO")
        TARGET_PATH.write_bytes(nso_data)

    elif nso_hash == COMPRESSED_V150_HASH:
        print(">>> found compressed 1.5.0 NSO")
        setup._decompress_nso(original_nso, TARGET_PATH)

    elif nso_hash == UNCOMPRESSED_V181_HASH:
        print(">>> found uncompressed 1.8.1 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            _download_v181_to_v150_patch(patch_path)
            setup._apply_xdelta3_patch(original_nso, patch_path, TARGET_PATH)

    elif nso_hash == COMPRESSED_V181_HASH:
        print(">>> found compressed 1.8.1 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            decompressed_nso_path = Path(tmpdir) / "v181.nso"

            setup._decompress_nso(original_nso, decompressed_nso_path)
            _download_v181_to_v150_patch(patch_path)
            setup._apply_xdelta3_patch(decompressed_nso_path, patch_path, TARGET_PATH)

    else:
        setup.fail(f"unknown executable: {nso_hash}")

    if not TARGET_PATH.is_file():
        setup.fail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() != TARGET_HASH:
        setup.fail("internal error while preparing executable (wrong NSO hash); please report")

    setup._convert_nso_to_elf(TARGET_PATH)

    if not TARGET_ELF_PATH.is_file():
        setup.fail("internal error while preparing executable (missing ELF); please report")


def create_build_dir():
    build_dir = setup.ROOT / "build"
    if build_dir.is_dir():
        print(">>> build directory already exists: nothing to do")
        return

    subprocess.check_call(
        "cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B build/".split(" "))
    print(">>> created build directory")


def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the Breath of the Wild decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO (1.5.0 or 1.8.1, compressed or not)", nargs="?")
    args = parser.parse_args()

    setup.install_viking()
    prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    create_build_dir()


if __name__ == "__main__":
    main()
