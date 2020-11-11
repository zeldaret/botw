import io
from typing import Any, Dict, NamedTuple

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from elftools.elf.sections import Section

import diff_settings
from util import utils

_config: Dict[str, Any] = {}
diff_settings.apply(_config, {})

_root = utils.get_repo_root()

base_elf_data = io.BytesIO((_root / _config["baseimg"]).read_bytes())
my_elf_data = io.BytesIO((_root / _config["myimg"]).read_bytes())

base_elf = ELFFile(base_elf_data)
my_elf = ELFFile(my_elf_data)
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
    raise KeyError(f"No segment found for {addr:#x}")


def is_in_section(section: Section, addr: int, size: int) -> bool:
    begin = section["sh_addr"]
    end = begin + section["sh_size"]
    return begin <= addr < end and begin <= addr + size < end


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


def read_from_elf(elf: ELFFile, addr: int, size: int) -> bytes:
    offset: int = get_file_offset(elf, addr)
    elf.stream.seek(offset)
    return elf.stream.read(size)


def get_fn_from_base_elf(addr: int, size: int) -> Function:
    return Function(read_from_elf(base_elf, addr, size), addr)


def get_fn_from_my_elf(name: str) -> Function:
    sym = get_symbol(my_symtab, name)
    return Function(read_from_elf(my_elf, sym.addr, sym.size), sym.addr)


R_AARCH64_GLOB_DAT = 1025


def build_glob_data_table(elf: ELFFile) -> Dict[int, int]:
    table: Dict[int, int] = dict()
    section = elf.get_section_by_name(".rela.dyn")
    assert isinstance(section, RelocationSection)

    symtab = elf.get_section(section["sh_link"])

    for reloc in section.iter_relocations():
        sym_value = symtab.get_symbol(reloc["r_info_sym"])["st_value"]
        if reloc["r_info_type"] == R_AARCH64_GLOB_DAT:
            table[reloc["r_offset"]] = sym_value + reloc["r_addend"]

    return table
