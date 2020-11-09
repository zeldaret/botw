#!/usr/bin/env python3

from typing import Any, Dict, Set

import capstone as cs
from elftools.elf.elffile import ELFFile

import diff_settings
from util import utils

_config: Dict[str, Any] = {}
diff_settings.apply(_config, {})

_root = utils.get_repo_root()

base_elf = ELFFile((_root / _config["baseimg"]).open("rb"))
my_elf = ELFFile((_root / _config["myimg"]).open("rb"))
my_symtab = my_elf.get_section_by_name(".symtab")
if not my_symtab:
    utils.fail(f'{_config["myimg"]} has no symbol table')


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


def build_symbol_table(symtab) -> Dict[int, str]:
    table = dict()
    for sym in symtab.iter_symbols():
        addr = sym["st_value"]
        existing_value = table.get(addr, None)
        if existing_value is None or not existing_value.startswith("_Z"):
            table[addr] = sym.name
    return table


def get_fn_from_base_elf(addr: int, size: int) -> bytes:
    offset = get_file_offset(base_elf, addr)
    base_elf.stream.seek(offset)
    return base_elf.stream.read(size)


def get_fn_from_my_elf(name: str) -> bytes:
    offset, size = get_symbol_file_offset_and_size(my_elf, my_symtab, name)
    my_elf.stream.seek(offset)
    return my_elf.stream.read(size)
