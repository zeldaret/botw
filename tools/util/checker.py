import struct
from collections import defaultdict
from typing import Set, DefaultDict, Dict, Optional, Tuple

import capstone as cs

from util import dsym, elf, utils

_store_instructions = ("str", "strb", "strh", "stur", "sturb", "sturh")


class FunctionChecker:
    def __init__(self, log_mismatch_cause: bool = False):
        self.md = cs.Cs(cs.CS_ARCH_ARM64, cs.CS_MODE_ARM)
        self.md.detail = True
        self.my_symtab = elf.build_name_to_symbol_table(elf.my_symtab)
        self.dsymtab = dsym.DataSymbolContainer()
        self.decompiled_fns: Dict[int, str] = dict()

        self._log_mismatch_cause = log_mismatch_cause
        self._mismatch_addr1 = -1
        self._mismatch_addr2 = -1
        self._mismatch_cause = ""
        self._base_got_section = elf.base_elf.get_section_by_name(".got")
        self._decomp_glob_data_table = elf.build_glob_data_table(elf.my_elf)
        self._got_data_symbol_check_cache: Dict[Tuple[int, int], bool] = dict()

        self.load_data_for_project()

    def _reset_mismatch(self) -> None:
        self._mismatch_addr1 = -1
        self._mismatch_addr2 = -1
        self._mismatch_cause = ""

    def get_data_symtab(self) -> dsym.DataSymbolContainer:
        return self.dsymtab

    def get_mismatch(self) -> (int, int, str):
        return self._mismatch_addr1, self._mismatch_addr2, self._mismatch_cause

    def load_data_for_project(self) -> None:
        self.decompiled_fns = {func.addr: func.decomp_name for func in utils.get_functions() if func.decomp_name}
        self.get_data_symtab().load_from_csv(utils.get_repo_root() / "data" / "data_symbols.csv")

    def check(self, base_fn: elf.Function, my_fn: elf.Function) -> bool:
        self._reset_mismatch()
        gprs1: DefaultDict[int, int] = defaultdict(int)
        gprs2: DefaultDict[int, int] = defaultdict(int)
        adrp_pair_registers: Set[int] = set()

        size = len(base_fn)
        if len(base_fn) != len(my_fn):
            if self._log_mismatch_cause:
                self._set_mismatch_cause(None, None, "different function length")
            return False

        for i1, i2 in zip(self.md.disasm(base_fn.data, base_fn.addr), self.md.disasm(my_fn.data, my_fn.addr)):
            if i1.bytes == i2.bytes:
                if i1.mnemonic == 'adrp':
                    gprs1[i1.operands[0].reg] = i1.operands[1].imm
                    gprs2[i2.operands[0].reg] = i2.operands[1].imm
                    adrp_pair_registers.add(i1.operands[0].reg)
                elif i1.mnemonic == 'ldp' or i1.mnemonic == 'ldpsw':
                    reg = i1.operands[2].value.mem.base
                    if reg in adrp_pair_registers:
                        adrp_pair_registers.remove(reg)
                elif i1.mnemonic.startswith('ld'):
                    reg = i1.operands[1].value.mem.base
                    if reg in adrp_pair_registers:
                        adrp_pair_registers.remove(reg)
                elif i1.mnemonic == 'add':
                    reg = i1.operands[1].reg
                    if reg in adrp_pair_registers:
                        adrp_pair_registers.remove(reg)
                elif i1.mnemonic == 'b':
                    branch_target = i1.operands[0].imm
                    if not (base_fn.addr <= branch_target < base_fn.addr + size):
                        if not self._check_function_call(i1, i2, branch_target, i2.operands[0].imm):
                            return False
                continue

            if i1.mnemonic != i2.mnemonic:
                if self._log_mismatch_cause:
                    self._set_mismatch_cause(i1, i2, "mnemonics are different")
                return False

            # Ignore some address differences until a fully matching executable can be generated.

            if i1.mnemonic == 'bl':
                if not self._check_function_call(i1, i2, i1.operands[0].imm, i2.operands[0].imm):
                    return False
                continue

            if i1.mnemonic == 'b':
                branch_target = i1.operands[0].imm
                # If we are branching outside the function, this is likely a tail call.
                # Treat this as a function call.
                if not (base_fn.addr <= branch_target < base_fn.addr + size):
                    if not self._check_function_call(i1, i2, branch_target, i2.operands[0].imm):
                        return False
                    continue
                # Otherwise, it's a mismatch.
                return False

            if i1.mnemonic == 'adrp':
                if i1.operands[0].reg != i2.operands[0].reg:
                    return False
                reg = i1.operands[0].reg

                gprs1[reg] = i1.operands[1].imm
                gprs2[reg] = i2.operands[1].imm

                adrp_pair_registers.add(reg)
                continue

            if i1.mnemonic == 'ldp' or i1.mnemonic == 'ldpsw' or i1.mnemonic == 'stp':
                if i1.operands[0].reg != i2.operands[0].reg:
                    return False
                if i1.operands[1].reg != i2.operands[1].reg:
                    return False
                if i1.operands[2].value.mem.base != i2.operands[2].value.mem.base:
                    return False
                reg = i1.operands[2].value.mem.base
                if reg not in adrp_pair_registers:
                    return False

                gprs1[reg] += i1.operands[2].value.mem.disp
                gprs2[reg] += i2.operands[2].value.mem.disp
                if not self._check_data_symbol_load(i1, i2, gprs1[reg], gprs2[reg]):
                    return False

                adrp_pair_registers.remove(reg)
                continue

            if i1.mnemonic.startswith('ld') or i1.mnemonic in _store_instructions:
                if i1.operands[0].reg != i2.operands[0].reg:
                    return False
                if i1.operands[1].value.mem.base != i2.operands[1].value.mem.base:
                    return False
                reg = i1.operands[1].value.mem.base
                if reg not in adrp_pair_registers:
                    return False

                gprs1[reg] += i1.operands[1].value.mem.disp
                gprs2[reg] += i2.operands[1].value.mem.disp
                if not self._check_data_symbol_load(i1, i2, gprs1[reg], gprs2[reg]):
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

                gprs1[reg] += i1.operands[2].imm
                gprs2[reg] += i2.operands[2].imm
                if not self._check_data_symbol(i1, i2, gprs1[reg], gprs2[reg]):
                    return False

                adrp_pair_registers.remove(reg)
                continue

            return False

        return True

    def _set_mismatch_cause(self, i1: Optional[any], i2: Optional[any], description: str) -> None:
        self._mismatch_addr1 = i1.address if i1 else -1
        self._mismatch_addr2 = i2.address if i2 else -1
        self._mismatch_cause = description

    def _check_data_symbol(self, i1, i2, orig_addr: int, decomp_addr: int) -> bool:
        symbol = self.dsymtab.get_symbol(orig_addr)
        if symbol is None:
            return True

        decomp_symbol = self.my_symtab[symbol.name]
        if decomp_symbol.addr == decomp_addr:
            return True

        if self._log_mismatch_cause:
            self._set_mismatch_cause(i1, i2, f"data symbol mismatch: {symbol.name} (original address: {orig_addr:#x}, "
                                             f"expected: {decomp_symbol.addr:#x}, "
                                             f"actual: {decomp_addr:#x})")

        return False

    def _check_data_symbol_load(self, i1, i2, orig_addr: int, decomp_addr: int) -> bool:
        cached_result = self._got_data_symbol_check_cache.get((orig_addr, decomp_addr), None)
        if cached_result is not None:
            return cached_result

        if not elf.is_in_section(self._base_got_section, orig_addr, 8):
            return True

        ptr1, = struct.unpack("<Q", elf.read_from_elf(elf.base_elf, orig_addr, 8))
        if self.dsymtab.get_symbol(ptr1) is None:
            return True

        ptr2 = self._decomp_glob_data_table[decomp_addr]

        result = self._check_data_symbol(i1, i2, ptr1, ptr2)
        self._got_data_symbol_check_cache[(orig_addr, decomp_addr)] = result
        return result

    def _check_function_call(self, i1, i2, orig_addr: int, decomp_addr: int) -> bool:
        name = self.decompiled_fns.get(orig_addr, None)
        if name is None:
            self.on_unknown_fn_call(orig_addr, decomp_addr)
            return True

        decomp_symbol = self.my_symtab[name]
        if decomp_symbol.addr == decomp_addr:
            return True

        if self._log_mismatch_cause:
            self._set_mismatch_cause(i1, i2, f"function call mismatch: {name}")

        return False

    def on_unknown_fn_call(self, orig_addr: int, decomp_addr: int) -> None:
        pass
