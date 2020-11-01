#!/usr/bin/env python3

import argparse
from elftools.elf.elffile import ELFFile
import diff_settings
from pathlib import Path
from typing import Any, Dict
import utils

config: Dict[str, Any] = {}
diff_settings.apply(config, {})

root = Path(__file__).parent.parent
my_elf = ELFFile((root / config["myimg"]).open("rb"))
my_symtab = my_elf.get_section_by_name(".symtab")
if not my_symtab:
    utils.fail(f'{config["myimg"]} has no symbol table')


def get_file_offset(elf, addr: int) -> int:
    for seg in elf.iter_segments():
        if seg.header["p_type"] != "PT_LOAD":
            continue
        if seg["p_vaddr"] <= addr < seg["p_vaddr"] + seg["p_filesz"]:
            return addr - seg["p_vaddr"] + seg["p_offset"]
    assert False


def get_symbol_file_offset_and_size(elf, table, name: str) -> (int, int):
    syms = table.get_symbol_by_name(name)
    if not syms or len(syms) != 1:
        raise KeyError(name)
    return get_file_offset(elf, syms[0]["st_value"]), syms[0]["st_size"]


def get_fn_from_my_elf(name: str) -> bytes:
    offset, size = get_symbol_file_offset_and_size(my_elf, my_symtab, name)
    my_elf.stream.seek(offset)
    return my_elf.stream.read(size)


def dump_fn(name: str) -> None:
    expected_dir = root / "expected"
    try:
        fn = get_fn_from_my_elf(name)
        path = expected_dir / f"{name}.bin"
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(fn)
    except KeyError:
        utils.fail("could not find function")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("function_name", help="Name of the function to dump")
    args = parser.parse_args()

    dump_fn(args.function_name)


if __name__ == "__main__":
    main()
