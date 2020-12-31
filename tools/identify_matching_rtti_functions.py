#!/usr/bin/env python3
import struct
from typing import Dict, Set

import capstone as cs
import cxxfilt
from colorama import Fore

from util import utils, elf


def main() -> None:
    new_matches: Dict[int, str] = dict()
    functions_by_addr: Dict[int, utils.FunctionInfo] = {fn.addr: fn for fn in utils.get_functions()}

    md = cs.Cs(cs.CS_ARCH_ARM64, cs.CS_MODE_ARM)
    md.detail = True
    decomp_addr_to_symbol = elf.build_addr_to_symbol_table(elf.my_symtab)
    decomp_glob_data_table = elf.build_glob_data_table(elf.my_elf)

    processed: Set[int] = set()
    for fn in functions_by_addr.values():
        if fn.status != utils.FunctionStatus.Matching:
            continue

        if fn.size != 0x5C or (not fn.decomp_name.endswith("8getRuntimeTypeInfoEv") and not fn.name.endswith("rtti2")):
            continue

        base_fn = elf.get_fn_from_base_elf(fn.addr, fn.size)
        try:
            my_fn = elf.get_fn_from_my_elf(fn.decomp_name)
        except KeyError:
            utils.warn(f"could not find function {fn.decomp_name}")
            continue

        assert len(base_fn.data) == len(my_fn.data)

        vtable_ptr1 = 0
        vtable_ptr2 = 0
        for j, (i1, i2) in enumerate(zip(md.disasm(base_fn.data, base_fn.addr), md.disasm(my_fn.data, my_fn.addr))):
            assert i1.mnemonic == i2.mnemonic
            if j == 10:
                assert i1.mnemonic == "adrp"
                assert i1.operands[0].reg == i2.operands[0].reg
                vtable_ptr1 = i1.operands[1].imm
                vtable_ptr2 = i2.operands[1].imm
            elif j == 11:
                assert i1.mnemonic == "ldr"
                assert i1.operands[0].reg == i2.operands[0].reg
                assert i1.operands[1].value.mem.base == i2.operands[1].value.mem.base
                vtable_ptr1 += i1.operands[1].value.mem.disp
                vtable_ptr2 += i2.operands[1].value.mem.disp
                break

        assert vtable_ptr1 != 0 and vtable_ptr2 != 0
        if vtable_ptr1 in processed:
            continue
        processed.add(vtable_ptr1)
        ptr1, = struct.unpack("<Q", elf.read_from_elf(elf.base_elf, vtable_ptr1, 8))
        ptr2 = decomp_glob_data_table[vtable_ptr2]

        vtable1 = elf.get_vtable_fns_from_base_elf(ptr1 + 0x10, num_entries=1)
        vtable2 = elf.unpack_vtable_fns(elf.read_from_elf(elf.my_elf, addr=ptr2 + 0x10, size=8), num_entries=1)

        if functions_by_addr[vtable1[0]].status == utils.FunctionStatus.Matching:
            continue

        decomp_derive_fn_addr = vtable2[0]
        if decomp_derive_fn_addr == 0:
            decomp_derive_fn_addr = decomp_glob_data_table.get(ptr2 + 0x10, 0)
        if decomp_derive_fn_addr == 0:
            raise RuntimeError(f"Derive virtual function pointer is null "
                               f"(fn: {fn.decomp_name}, decomp vtable at {ptr2:#x})")

        name = decomp_addr_to_symbol[decomp_derive_fn_addr]
        new_matches[vtable1[0]] = name
        utils.print_note(f"new match: {Fore.BLUE}{cxxfilt.demangle(name)}{Fore.RESET} (from {fn.decomp_name})")

    # overwrite the original names because they are likely to be incorrect
    utils.add_decompiled_functions(new_matches, new_orig_names=new_matches)


if __name__ == '__main__':
    main()
