#!/usr/bin/env python3

from typing import Any, Dict, NamedTuple

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


class Symbol(NamedTuple):
    addr: int
    name: str
    size: int


class Function(NamedTuple):
    data: bytes
    addr: int


def get_file_offset(elf, addr: int) -> int:
    for seg in elf.iter_segments():
        if seg.header["p_type"] != "PT_LOAD":
            continue
        if seg["p_vaddr"] <= addr < seg["p_vaddr"] + seg["p_filesz"]:
            return addr - seg["p_vaddr"] + seg["p_offset"]
    assert False


def get_symbol(table, name: str) -> Symbol:
    syms = table.get_symbol_by_name(name)
    if not syms or len(syms) != 1:
        raise KeyError(name)
    return Symbol(syms[0]["st_value"], name, syms[0]["st_size"])


def get_symbol_file_offset_and_size(elf, table, name: str) -> (int, int):
    sym = get_symbol(table, name)
    return get_file_offset(elf, sym.addr), sym.size


def build_addr_to_symbol_table(symtab) -> Dict[int, str]:
    table = dict()
    for sym in symtab.iter_symbols():
        addr = sym["st_value"]
        existing_value = table.get(addr, None)
        if existing_value is None or not existing_value.startswith("_Z"):
            table[addr] = sym.name
    return table


def build_name_to_symbol_table(symtab) -> Dict[str, Symbol]:
    return {sym.name: Symbol(sym["st_value"], sym.name, sym["st_size"]) for sym in symtab.iter_symbols()}


def get_fn_from_base_elf(addr: int, size: int) -> Function:
    offset = get_file_offset(base_elf, addr)
    base_elf.stream.seek(offset)
    return Function(base_elf.stream.read(size), addr)


def get_fn_from_my_elf(name: str) -> Function:
    sym = get_symbol(my_symtab, name)
    offset = get_file_offset(my_elf, sym.addr)
    my_elf.stream.seek(offset)
    return Function(my_elf.stream.read(sym.size), sym.addr)
