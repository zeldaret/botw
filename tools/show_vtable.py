#!/usr/bin/env python3

import argparse
from colorama import Fore, Style
import cxxfilt
from elftools.elf.elffile import ELFFile
import diff_settings
from pathlib import Path
import struct
from typing import Any, Dict, Optional
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


def build_symbol_table(symtab) -> Dict[int, str]:
    table = dict()
    for sym in symtab.iter_symbols():
        addr = sym["st_value"]
        existing_value = table.get(addr, None)
        if existing_value is None or not existing_value.startswith("_Z"):
            table[addr] = sym.name
    return table


def find_vtable(symtab, class_name: str) -> Optional[str]:
    OFFSET = len("vtable for ")
    for sym in symtab.iter_symbols():
        if not sym.name.startswith("_ZTV"):
            continue
        if cxxfilt.demangle(sym.name)[OFFSET:] == class_name:
            return sym.name
    return None


def bold(s) -> str:
    return Style.BRIGHT + str(s) + Style.NORMAL


def dump_table(name: str) -> None:
    try:
        symbols = build_symbol_table(my_symtab)
        decomp_symbols = {fn.decomp_name for fn in utils.get_functions() if fn.decomp_name}

        offset, size = get_symbol_file_offset_and_size(my_elf, my_symtab, name)
        my_elf.stream.seek(offset)
        vtable_bytes = my_elf.stream.read(size)

        if not vtable_bytes:
            utils.fail(
                "empty vtable; has the key function been implemented? (https://lld.llvm.org/missingkeyfunction.html)")

        print(f"{Fore.WHITE}{Style.BRIGHT}{cxxfilt.demangle(name)}{Style.RESET_ALL}")
        print(f"{Fore.YELLOW}{Style.BRIGHT}vtable @ 0x0{Style.RESET_ALL}")

        assert size % 8 == 0
        for i in range(size // 8):
            word: int = struct.unpack_from("<Q", vtable_bytes, 8 * i)[0]
            name = symbols.get(word, None)
            if word == 0:
                pass
            elif name is not None:
                demangled_name: str = cxxfilt.demangle(name)
                color = Fore.GREEN if name in decomp_symbols else Fore.BLUE
                print(f"{color}{bold(demangled_name)}{Style.RESET_ALL}")
                print(f"    {name}")
            elif word & (1 << 63):
                offset = -struct.unpack_from("<q", vtable_bytes, 8 * i)[0]
                print()
                print(f"{Fore.YELLOW}{Style.BRIGHT}vtable @ {offset:#x}{Style.RESET_ALL}")
            else:
                print(f"{Fore.RED}unknown data: {word:016x}{Style.RESET_ALL}")

    except KeyError:
        utils.fail("could not find symbol")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("symbol_name", help="Name of the vtable symbol (_ZTV...) or class name")
    args = parser.parse_args()

    symbol_name: str = args.symbol_name

    if not symbol_name.startswith("_ZTV"):
        symbol_name = find_vtable(my_symtab, args.symbol_name)

    dump_table(symbol_name)


if __name__ == "__main__":
    main()
