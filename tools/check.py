#!/usr/bin/env python3

import sys

import util.elf
from util import utils


def check_function(addr: int, size: int, name: str, base_fn=None) -> bool:
    if base_fn is None:
        try:
            base_fn = util.elf.get_fn_from_base_elf(addr, size)
        except KeyError:
            utils.print_error(f"couldn't find base function 0x{addr:016x} for {utils.format_symbol_name_for_msg(name)}")
            return False

    my_fn = util.elf.get_fn_from_my_elf(name)
    return util.elf.check_function_ex(addr, size, base_fn, my_fn)


def main() -> None:
    failed = False

    nonmatching_fns_with_dump = {p.stem: p.read_bytes() for p in (utils.get_repo_root() / "expected").glob("*.bin")}

    for func in utils.get_functions():
        if not func.decomp_name:
            continue

        try:
            util.elf.get_fn_from_my_elf(func.decomp_name)
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
