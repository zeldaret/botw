#!/usr/bin/env python3

import os
import platform
from pathlib import Path
import sys
import tarfile
import tempfile
import urllib.request

ROOT = Path(__file__).parent.parent


def fail(error: str):
    print(error)
    sys.exit(1)


def set_up_compiler():
    compiler_dir = ROOT / "toolchain" / "clang"
    if compiler_dir.is_dir():
        print("clang is already set up: nothing to do")
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

    print(f"downloading Clang from {url}...")
    with tempfile.TemporaryDirectory() as tmpdir:
        path = tmpdir + "/" + url.split("/")[-1]
        urllib.request.urlretrieve(url, path)

        print(f"extracting Clang...")
        with tarfile.open(path) as f:
            f.extractall(compiler_dir.parent)
            (compiler_dir.parent / dir_name).rename(compiler_dir)

    print(">>> successfully set up Clang")


def create_build_dir():
    build_dir = ROOT / "build"
    if build_dir.is_dir():
        print("build directory already exists: nothing to do")
        return

    os.system("cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B build/")
    print(">>> created build directory")


def main():
    set_up_compiler()
    create_build_dir()


if __name__ == "__main__":
    main()
