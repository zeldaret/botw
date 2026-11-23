#!/usr/bin/env -S uv run
from pathlib import Path
# todo: remove once everything switches off the old config.toml
import os
os.environ["VIKING_CONFIG"] = str(Path(__file__).parent / "config.viking-next.toml")

import argparse
import hashlib
import subprocess
import tempfile
import urllib.request

from viking import ui, core, setup


def _download_downgrade_to_v150_patch(version: str, dest: Path):
    ui.step(f"downloading patch for {version}...")
    urllib.request.urlretrieve(f"https://s.botw.link/v150_downgrade/{version}_to_v150.patch", dest)


def prepare_executable(original_nso: Path | None):
    config = core.get_config()
    target_nso = config.repo.original_nso()
    target_elf = config.repo.original_elf()

    COMPRESSED_V150_HASH = "898dc199301f7c419be5144bb5cb27e2fc346e22b27345ba3fb40c0060c2baf8"
    UNCOMPRESSED_V150_HASH = "d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106"
    COMPRESSED_V160_HASH = "15cfca7b89348956f85d945fade2e215a6af5991ed1071e181f97ca72f7ae20b"
    UNCOMPRESSED_V160_HASH = "8a2fc8b1111a35a76fd2d53a8670599da4a7a9706a3d91215d30fd62149f00c1"
    COMPRESSED_V190_HASH = "f6f0b20bb1f2b67d164c24871cd473147eef1d285f12e7bd492e3126c6022e27"
    UNCOMPRESSED_V190_HASH = "6a30c162a2e6f885e0b1c0a6673a84795549a5ccdec1de8d3a741168ac4cba86"

    # The uncompressed v1.5.0 main NSO.
    TARGET_HASH = UNCOMPRESSED_V150_HASH

    if target_nso.is_file() and hashlib.sha256(target_nso.read_bytes()).hexdigest() == TARGET_HASH and target_elf.is_file():
        ui.step("NSO is already set up")
        return

    if original_nso is None:
        ui.bail("please pass a path to the NSO (refer to the readme for more details)")

    if not original_nso.is_file():
        ui.bail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    version_matrix = [
        # SHA256                 Compressed? Version
        (UNCOMPRESSED_V150_HASH, False,      "1.5.0"),
        (  COMPRESSED_V150_HASH, True,       "1.5.0"),
        (UNCOMPRESSED_V160_HASH, False,      "1.6.0"),
        (  COMPRESSED_V160_HASH, True,       "1.6.0"),
        (UNCOMPRESSED_V190_HASH, False,      "1.9.0"),
        (  COMPRESSED_V190_HASH, True,       "1.9.0"),
    ]

    for (expected_hash, is_compressed, version_str) in version_matrix:
        if nso_hash != expected_hash:
            continue
        ui.step(f"found {"compressed" if is_compressed else "uncompressed"} {version_str} NSO")

        if version_str == "1.5.0":
            setup.convert_nso_to_elf(
                original_nso,
                elf_out_path=target_elf,
                uncompressed_nso_out_path=target_nso
            )
            break

        with tempfile.TemporaryDirectory() as tmpdir:
            patch_path = Path(tmpdir) / "patch"
            patch_version_str = "v" + version_str.replace(".","")
            decompressed_nso_path = Path(tmpdir) / f"{patch_version_str}.nso"
            _download_downgrade_to_v150_patch(patch_version_str, patch_path)
            if is_compressed:
                # decompress -> patch -> elf
                setup.convert_nso_to_elf(original_nso, uncompressed_nso_out_path=decompressed_nso_path, message="decompressing NSO...")
                setup.apply_xdelta3_patch(decompressed_nso_path, patch_path, target_nso)
                setup.convert_nso_to_elf(target_nso, elf_out_path=target_elf)
            else:
                # patch -> elf
                setup.apply_xdelta3_patch(original_nso, patch_path, decompressed_nso_path)
                setup.convert_nso_to_elf(decompressed_nso_path, elf_out_path=target_elf)
        break
    else:
        ui.bail(f"unknown executable: {nso_hash}")

    if not target_nso.is_file():
        ui.bail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(target_nso.read_bytes()).hexdigest() != TARGET_HASH:
        ui.bail("internal error while preparing executable (wrong NSO hash); please report")
    if not target_elf.is_file():
        ui.bail("internal error while preparing executable (missing ELF); please report")


def create_build_dir():
    config = core.get_config()
    build_dir = config.repo.build_path
    if build_dir.is_dir() and (build_dir / "CMakeCache.txt").is_file():
        ui.step("build directory already exists: nothing to do")
        return

    subprocess.check_call(
        "cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B build/".split(" "))
    ui.step("created build directory")


def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the Breath of the Wild decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO (1.5.0 or 1.9.0, compressed or not)", nargs="?")
    args = parser.parse_args()
    prepare_executable(args.original_nso)

    config = core.get_config()
    # If the new check/decompme/listsym tools misbehaves, you can unblock
    # yourself by changing this to False and rerun tools/setup.py
    NEW_TOOLS = True
    if NEW_TOOLS:
        tools_path = config.repo.root_path / "tools"
        viking_bin_path = setup.rust_cli_install_pre_built(tools_path / "viking")

        # todo: right now we still need to override the config path to
        # config.viking-next.toml, since existing tools/scripts work with
        # config.toml. Once everything is switched to viking-next,
        # we can just hardlink the tools and use the default config location

        # setup.rust_cli_create_hardlinks(viking_bin_path, [
        #     (tools_path / tool) for tool in ["check", "listsym", "decompme"]
        # ])

        script_template = """#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

export VIKING_CONFIG="$SCRIPT_DIR/config.viking-next.toml"
exec ./viking %s "$@"
"""
        for tool in ["check", "listsym", "decompme"]:
            tool_path = tools_path / tool
            tool_path.write_text(script_template % tool)
            tool_path.chmod(0o755)
    else:
        from common import setup_common as setup_old
        setup_old.install_viking()

    setup.install_clang("4.0.1")
    create_build_dir()


if __name__ == "__main__":
    main()
