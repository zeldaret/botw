#!/usr/bin/env python3

import capstone as cs
from elftools.elf.elffile import ELFFile
import diff_settings
from pathlib import Path
import sys
from typing import Any, Dict, Set
import utils

config: Dict[str, Any] = {}
diff_settings.apply(config, {})

root = Path(__file__).parent.parent
base_elf = ELFFile((root / config["baseimg"]).open("rb"))
my_elf = ELFFile((root / config["myimg"]).open("rb"))
my_symtab = my_elf.get_section_by_name(".symtab")
if not my_symtab:
    utils.fail(f'{config["myimg"]} has no symbol table')

md = cs.Cs(cs.CS_ARCH_ARM64, cs.CS_MODE_ARM)
md.detail = True


def get_file_offset(elf, addr: int) -> int:
    for seg in elf.iter_segments():
        if seg.header["p_type"] != "PT_LOAD":
            continue
        if seg["p_vaddr"] <= addr < seg["p_vaddr"] + seg["p_filesz"]:
            return addr - seg["p_vaddr"] + seg["p_offset"]
    assert False


def get_symbol_file_offset(elf, table, name: str) -> int:
    syms = table.get_symbol_by_name(name)
    if not syms or len(syms) != 1:
        raise KeyError(name)
    return get_file_offset(elf, syms[0]["st_value"])


def get_fn_from_base_elf(addr: int, size: int) -> bytes:
    offset = get_file_offset(base_elf, addr)
    base_elf.stream.seek(offset)
    return base_elf.stream.read(size)


def get_fn_from_my_elf(name: str, size: int) -> bytes:
    offset = get_symbol_file_offset(my_elf, my_symtab, name)
    my_elf.stream.seek(offset)
    return my_elf.stream.read(size)


def check_function_ex(addr: int, size: int, base_fn: bytes, my_fn: bytes) -> bool:
    adrp_pair_registers: Set[int] = set()

    for i1, i2 in zip(md.disasm(base_fn, addr), md.disasm(my_fn, addr)):
        if i1.bytes == i2.bytes:
            if i1.mnemonic == 'adrp':
                adrp_pair_registers.add(i1.operands[0].reg)
            elif i1.mnemonic == 'ldr':
                reg = i1.operands[1].value.mem.base
                if reg in adrp_pair_registers:
                    adrp_pair_registers.remove(reg)
            elif i1.mnemonic == 'ldp':
                reg = i1.operands[2].value.mem.base
                if reg in adrp_pair_registers:
                    adrp_pair_registers.remove(reg)
            elif i1.mnemonic == 'add':
                reg = i1.operands[1].reg
                if reg in adrp_pair_registers:
                    adrp_pair_registers.remove(reg)
            continue

        if i1.mnemonic != i2.mnemonic:
            return False

        # Ignore some address differences until a fully matching executable can be generated.

        if i1.mnemonic == 'bl':
            continue

        if i1.mnemonic == 'b':
            # Needed for tail calls.
            branch_target = int(i1.op_str[1:], 16)
            if not (addr <= branch_target < addr + size):
                continue

        if i1.mnemonic == 'adrp':
            if i1.operands[0].reg != i2.operands[0].reg:
                return False
            adrp_pair_registers.add(i1.operands[0].reg)
            continue

        if i1.mnemonic == 'ldr' or i1.mnemonic == 'str':
            if i1.operands[0].reg != i2.operands[0].reg:
                return False
            if i1.operands[1].value.mem.base != i2.operands[1].value.mem.base:
                return False
            reg = i1.operands[1].value.mem.base
            if reg not in adrp_pair_registers:
                return False
            adrp_pair_registers.remove(reg)
            continue

        if i1.mnemonic == 'ldp' or i1.mnemonic == 'stp':
            if i1.operands[0].reg != i2.operands[0].reg:
                return False
            if i1.operands[1].reg != i2.operands[1].reg:
                return False
            if i1.operands[2].value.mem.base != i2.operands[2].value.mem.base:
                return False
            reg = i1.operands[2].value.mem.base
            if reg not in adrp_pair_registers:
                return False
            adrp_pair_registers.remove(reg)
            continue

        if i1.mnemonic == 'add':
            if i1.operands[0].reg != i2.operands[0].reg:
                return False
            if i1.operands[1].reg != i2.operands[1].reg:
                return False
            reg = i1.operands[1].reg
            if reg not in adrp_pair_registers:
                return False
            adrp_pair_registers.remove(reg)
            continue

        return False

    return True


def check_function(addr: int, size: int, name: str, base_fn=None) -> bool:
    if base_fn is None:
        try:
            base_fn = get_fn_from_base_elf(addr, size)
        except KeyError:
            utils.print_error(f"couldn't find base function 0x{addr:016x} for {utils.format_symbol_name_for_msg(name)}")
            return False

    my_fn = get_fn_from_my_elf(name, size)
    return check_function_ex(addr, size, base_fn, my_fn)


def main() -> None:
    failed = False

    nonmatching_fns_with_dump = {p.stem: p.read_bytes() for p in (root / "expected").glob("*.bin")}

    for func in utils.get_functions():
        if not func.decomp_name:
            continue

        try:
            get_fn_from_my_elf(func.decomp_name, 0)
        except KeyError:
            utils.warn(f"couldn't find {utils.format_symbol_name_for_msg(func.decomp_name)}")
            continue

        if func.status == utils.FunctionStatus.Matching:
            if not check_function(func.addr, func.size, func.decomp_name):
                utils.print_error(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} is marked as matching but does not match")
                failed = True
        elif func.status == utils.FunctionStatus.Equivalent or func.status == utils.FunctionStatus.NonMatching:
            if check_function(func.addr, func.size, func.decomp_name):
                utils.print_note(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} is marked as non-matching but matches")

            fn_dump = nonmatching_fns_with_dump.get(func.decomp_name, None)
            if fn_dump is not None and not check_function(func.addr, len(fn_dump), func.decomp_name, fn_dump):
                utils.print_error(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} does not match expected output")
                failed = True

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
