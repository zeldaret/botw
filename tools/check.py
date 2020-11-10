#!/usr/bin/env python3

import sys
from typing import Optional

import util.elf
import util.checker
from util import utils


def check_function(checker: util.checker.FunctionChecker, addr: int, size: int, name: str,
                   base_fn: Optional[util.elf.Function] = None) -> bool:
    if base_fn is None:
        try:
            base_fn = util.elf.get_fn_from_base_elf(addr, size)
        except KeyError:
            utils.print_error(f"couldn't find base function 0x{addr:016x} for {utils.format_symbol_name_for_msg(name)}")
            return False

    my_fn = util.elf.get_fn_from_my_elf(name)
    return checker.check(base_fn, my_fn)


def main() -> None:
    failed = False

    nonmatching_fns_with_dump = {p.stem: util.elf.Function(p.read_bytes(), 0) for p in
                                 (utils.get_repo_root() / "expected").glob("*.bin")}

    checker = util.checker.FunctionChecker(log_mismatch_cause=True)

    for func in utils.get_functions():
        if not func.decomp_name:
            continue

        try:
            util.elf.get_fn_from_my_elf(func.decomp_name)
        except KeyError:
            utils.warn(f"couldn't find {utils.format_symbol_name_for_msg(func.decomp_name)}")
            continue

        if func.status == utils.FunctionStatus.Matching:
            if not check_function(checker, func.addr, func.size, func.decomp_name):
                utils.print_error(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} is marked as matching but does not match")
                a1, a2, reason = checker.get_mismatch()
                if a1 != -1:
                    sys.stderr.write(f"       at {a1|0x7100000000:#x} : {reason}\n")
                failed = True
        elif func.status == utils.FunctionStatus.Equivalent or func.status == utils.FunctionStatus.NonMatching:
            if check_function(checker, func.addr, func.size, func.decomp_name):
                utils.print_note(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} is marked as non-matching but matches")

            fn_dump = nonmatching_fns_with_dump.get(func.decomp_name, None)
            if fn_dump is not None and not check_function(checker, func.addr, len(fn_dump), func.decomp_name, fn_dump):
                utils.print_error(
                    f"function {utils.format_symbol_name_for_msg(func.decomp_name)} does not match expected output")
                failed = True

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
