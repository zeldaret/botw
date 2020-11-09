from typing import Set

import capstone as cs


class FunctionChecker:
    def __init__(self):
        self.md = cs.Cs(cs.CS_ARCH_ARM64, cs.CS_MODE_ARM)
        self.md.detail = True

    def check(self, addr: int, size: int, base_fn: bytes, my_fn: bytes) -> bool:
        adrp_pair_registers: Set[int] = set()

        for i1, i2 in zip(self.md.disasm(base_fn, addr), self.md.disasm(my_fn, addr)):
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
