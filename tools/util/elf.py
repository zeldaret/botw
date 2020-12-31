import io
import struct
from typing import Any, Dict, NamedTuple, Tuple

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


_ElfSymFormat = struct.Struct("<IBBHQQ")


class _ElfSym(NamedTuple):
    st_name: int
    info: int
    other: int
    shndx: int
    st_value: int
    st_size: int

    @staticmethod
    def parse(d: bytes):
        return _ElfSym._make(_ElfSymFormat.unpack(d))


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


_TableCache = dict()


def make_table_cached(symtab):
    table = _TableCache.get(id(symtab))
    if table is None:
        table = build_name_to_symbol_table(symtab)
        _TableCache[id(symtab)] = table
    return table


def get_symbol(symtab, name: str) -> Symbol:
    table = make_table_cached(symtab)
    return table[name]


def get_symbol_file_offset_and_size(elf, table, name: str) -> (int, int):
    sym = get_symbol(table, name)
    return get_file_offset(elf, sym.addr), sym.size


def iter_symbols(symtab):
    offset = symtab["sh_offset"]
    entsize = symtab["sh_entsize"]
    for i in range(symtab.num_symbols()):
        symtab.stream.seek(offset + i * entsize)
        entry = _ElfSym.parse(symtab.stream.read(_ElfSymFormat.size))
        name = symtab.stringtable.get_string(entry.st_name)
        yield Symbol(entry.st_value, name, entry.st_size)


def build_addr_to_symbol_table(symtab) -> Dict[int, str]:
    table = dict()
    for sym in iter_symbols(symtab):
        addr = sym.addr
        existing_value = table.get(addr, None)
        if existing_value is None or not existing_value.startswith("_Z"):
            table[addr] = sym.name
    return table


def build_name_to_symbol_table(symtab) -> Dict[str, Symbol]:
    return {sym.name: sym for sym in iter_symbols(symtab)}


def read_from_elf(elf: ELFFile, addr: int, size: int) -> bytes:
    addr &= ~0x7100000000
    offset: int = get_file_offset(elf, addr)
    elf.stream.seek(offset)
    return elf.stream.read(size)


def get_fn_from_base_elf(addr: int, size: int) -> Function:
    return Function(read_from_elf(base_elf, addr, size), addr)


def get_fn_from_my_elf(name: str) -> Function:
    sym = get_symbol(my_symtab, name)
    return Function(read_from_elf(my_elf, sym.addr, sym.size), sym.addr)


R_AARCH64_GLOB_DAT = 1025
R_AARCH64_RELATIVE = 1027


def build_glob_data_table(elf: ELFFile) -> Dict[int, int]:
    table: Dict[int, int] = dict()
    section = elf.get_section_by_name(".rela.dyn")
    assert isinstance(section, RelocationSection)

    symtab = elf.get_section(section["sh_link"])
    offset = symtab["sh_offset"]
    entsize = symtab["sh_entsize"]

    for reloc in section.iter_relocations():
        symtab.stream.seek(offset + reloc["r_info_sym"] * entsize)
        sym_value = _ElfSym.parse(symtab.stream.read(_ElfSymFormat.size)).st_value
        info_type = reloc["r_info_type"]
        if info_type == R_AARCH64_GLOB_DAT:
            table[reloc["r_offset"]] = sym_value + reloc["r_addend"]
        elif info_type == R_AARCH64_RELATIVE:
            # FIXME: this should be Delta(S) + A
            table[reloc["r_offset"]] = sym_value + reloc["r_addend"]

    return table


def unpack_vtable_fns(vtable_bytes: bytes, num_entries: int) -> Tuple[int, ...]:
    return struct.unpack(f"<{num_entries}Q", vtable_bytes[:num_entries * 8])


def get_vtable_fns_from_base_elf(vtable_addr: int, num_entries: int) -> Tuple[int, ...]:
    vtable_bytes = read_from_elf(base_elf, vtable_addr, num_entries * 8)
    return unpack_vtable_fns(vtable_bytes, num_entries)


def get_vtable_fns_from_my_elf(vtable_name: str, num_entries: int) -> Tuple[int, ...]:
    offset, size = get_symbol_file_offset_and_size(my_elf, my_symtab, vtable_name)
    my_elf.stream.seek(offset + 0x10)
    vtable_bytes = my_elf.stream.read(size - 0x10)
    return unpack_vtable_fns(vtable_bytes, num_entries)
