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

ROOT = Path(__file__).parent.parent


def fail(error: str):
    print(">>> " + error)
    sys.exit(1)


def _get_tool_binary_path():
    base = ROOT / "tools" / "nx-decomp-tools-binaries"
    system = platform.system()
    if system == "Linux":
        return str(base / "linux") + "/"
    if system == "Darwin":
        return str(base / "macos") + "/"
    return ""


def _convert_nso_to_elf(nso_path: Path):
    print(">>>> converting NSO to ELF...")
    binpath = _get_tool_binary_path()
    subprocess.check_call([binpath + "nx2elf", str(nso_path)])


def _decompress_nso(nso_path: Path, dest_path: Path):
    print(">>>> decompressing NSO...")
    binpath = _get_tool_binary_path()
    subprocess.check_call([binpath + "hactool", "-tnso",
                           "--uncompressed=" + str(dest_path), str(nso_path)])


def _download_v160_to_v150_patch(dest: Path):
    print(">>>> downloading patch...")
    urllib.request.urlretrieve("https://s.botw.link/v150_downgrade/v160_to_v150.patch", dest)


def _apply_xdelta3_patch(input: Path, patch: Path, dest: Path):
    print(">>>> applying patch...")
    try:
        subprocess.check_call(["xdelta3", "-d", "-s", str(input), str(patch), str(dest)])
    except FileNotFoundError:
        fail("error: install xdelta3 and try again")


def prepare_executable(original_nso: Path):
    COMPRESSED_V150_HASH = "898dc199301f7c419be5144bb5cb27e2fc346e22b27345ba3fb40c0060c2baf8"
    UNCOMPRESSED_V150_HASH = "d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106"
    COMPRESSED_V160_HASH = "15cfca7b89348956f85d945fade2e215a6af5991ed1071e181f97ca72f7ae20b"
    UNCOMPRESSED_V160_HASH = "8a2fc8b1111a35a76fd2d53a8670599da4a7a9706a3d91215d30fd62149f00c1"

    # The uncompressed v1.5.0 main NSO.
    TARGET_HASH = UNCOMPRESSED_V150_HASH
    TARGET_PATH = ROOT / "data" / "main.nso"
    TARGET_ELF_PATH = ROOT / "data" / "main.elf"

    if TARGET_PATH.is_file() and hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() == TARGET_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if not original_nso.is_file():
        fail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    if nso_hash == UNCOMPRESSED_V150_HASH:
        print(">>> found uncompressed 1.5.0 NSO")
        TARGET_PATH.write_bytes(nso_data)

    elif nso_hash == COMPRESSED_V150_HASH:
        print(">>> found compressed 1.5.0 NSO")
        _decompress_nso(original_nso, TARGET_PATH)

    elif nso_hash == UNCOMPRESSED_V160_HASH:
        print(">>> found uncompressed 1.6.0 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            _download_v160_to_v150_patch(patch_path)
            _apply_xdelta3_patch(original_nso, patch_path, TARGET_PATH)

    elif nso_hash == COMPRESSED_V160_HASH:
        print(">>> found compressed 1.6.0 NSO")

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            decompressed_nso_path = Path(tmpdir) / "v160.nso"

            _decompress_nso(original_nso, decompressed_nso_path)
            _download_v160_to_v150_patch(patch_path)
            _apply_xdelta3_patch(decompressed_nso_path, patch_path, TARGET_PATH)

    else:
        fail(f"unknown executable: {nso_hash}")

    if not TARGET_PATH.is_file():
        fail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() != TARGET_HASH:
        fail("internal error while preparing executable (wrong NSO hash); please report")

    _convert_nso_to_elf(TARGET_PATH)

    if not TARGET_ELF_PATH.is_file():
        fail("internal error while preparing executable (missing ELF); please report")


def set_up_compiler():
    compiler_dir = ROOT / "toolchain" / "clang"
    if compiler_dir.is_dir():
        print(">>> clang is already set up: nothing to do")
        return

    system = platform.system()
    machine = platform.machine()

    builds = {
        # Linux
        ("Linux", "x86_64"): {
            "url": "https://releases.llvm.org/4.0.1/clang+llvm-4.0.1-x86_64-linux-gnu-Fedora-25.tar.xz",
            "dir_name": "clang+llvm-4.0.1-x86_64-linux-gnu-Fedora-25",
        },
        ("Linux", "aarch64"): {
            "url": "https://releases.llvm.org/4.0.1/clang+llvm-4.0.1-aarch64-linux-gnu.tar.xz",
            "dir_name": "clang+llvm-4.0.1-aarch64-linux-gnu",
        },

        # macOS
        ("Darwin", "x86_64"): {
            "url": "https://releases.llvm.org/4.0.1/clang+llvm-4.0.1-x86_64-apple-darwin.tar.xz",
            "dir_name": "clang+llvm-4.0.1-x86_64-apple-darwin",
        },
        ("Darwin", "aarch64"): {
            "url": "https://releases.llvm.org/4.0.1/clang+llvm-4.0.1-x86_64-apple-darwin.tar.xz",
            "dir_name": "clang+llvm-4.0.1-x86_64-apple-darwin",
        },
    }

    build_info = builds.get((system, machine))
    if build_info is None:
        fail(
            f"unknown platform: {platform.platform()} (please report if you are on Linux and macOS)")

    url: str = build_info["url"]
    dir_name: str = build_info["dir_name"]

    print(f">>> downloading Clang from {url}...")
    with tempfile.TemporaryDirectory() as tmpdir:
        path = tmpdir + "/" + url.split("/")[-1]
        urllib.request.urlretrieve(url, path)

        print(f">>> extracting Clang...")
        with tarfile.open(path) as f:
            f.extractall(compiler_dir.parent)
            (compiler_dir.parent / dir_name).rename(compiler_dir)

    print(">>> successfully set up Clang")


def create_build_dir():
    build_dir = ROOT / "build"
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
                        help="Path to the original NSO (1.5.0 or 1.6.0, compressed or not)")
    args = parser.parse_args()

    prepare_executable(args.original_nso)
    set_up_compiler()
    create_build_dir()


if __name__ == "__main__":
    main()
