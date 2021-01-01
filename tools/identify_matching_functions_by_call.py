#!/usr/bin/env python3
from typing import Dict, List
import argparse

import cxxfilt
from colorama import Fore

from util import utils, checker, elf


class Checker(checker.FunctionChecker):
    def __init__(self):
        super().__init__()
        self.checking = ""
        self.invalid_call_descriptions: List[str] = []
        self.addr_to_symbol = elf.build_addr_to_symbol_table(elf.my_symtab)
        self._possible_calls: Dict[int, int] = dict()

    def reset(self) -> None:
        self._possible_calls.clear()

    def get_possible_calls(self) -> Dict[int, int]:
        return self._possible_calls

    def on_unknown_fn_call(self, orig_addr: int, decomp_addr: int):
        existing_addr = self._possible_calls.get(orig_addr)
        if existing_addr is not None and existing_addr != decomp_addr:
            self.invalid_call_descriptions.append(
                f"{orig_addr | 0x7100000000:#x} was mapped to {self.addr_to_symbol[existing_addr]} "
                f"({existing_addr:#x}) "
                f"but now maps to {self.addr_to_symbol[decomp_addr]} ({decomp_addr:#x})"
                f" (while checking {self.checking})")
            return
        self._possible_calls[orig_addr] = decomp_addr


def main() -> None:
    parser = argparse.ArgumentParser("Identifies matching functions by looking at function calls in matching functions")
    parser.add_argument("-f", "--fn", help="Functions to analyze", nargs="*")
    args = parser.parse_args()

    functions_to_analyze = set(args.fn) if args.fn else set()

    functions_by_addr: Dict[int, utils.FunctionInfo] = {fn.addr: fn for fn in utils.get_functions()}
    fn_checker = Checker()
    for fn in functions_by_addr.values():
        if functions_to_analyze and fn.decomp_name not in functions_to_analyze:
            continue

        if fn.status != utils.FunctionStatus.Matching:
            continue

        base_fn = elf.get_fn_from_base_elf(fn.addr, fn.size)
        try:
            my_fn = elf.get_fn_from_my_elf(fn.decomp_name)
        except KeyError:
            utils.warn(f"could not find function {fn.decomp_name}")
            continue

        fn_checker.checking = fn.decomp_name
        fn_checker.check(base_fn, my_fn)

    if fn_checker.invalid_call_descriptions:
        for x in fn_checker.invalid_call_descriptions:
            utils.print_note(x)
        utils.fail("invalid calls detected")

    new_matches: Dict[int, str] = dict()
    calls = fn_checker.get_possible_calls().copy()
    for base_target, my_target in calls.items():
        target_info = functions_by_addr.get(base_target)
        if target_info is None:
            continue
        if target_info.status != utils.FunctionStatus.NotDecompiled:
            continue

        base_fn = elf.get_fn_from_base_elf(target_info.addr, target_info.size)
        try:
            name = fn_checker.addr_to_symbol[my_target]
            my_fn = elf.get_fn_from_my_elf(name)
        except KeyError:
            continue

        if fn_checker.check(base_fn, my_fn):
            new_matches[base_target] = name
            utils.print_note(f"new match: {Fore.BLUE}{cxxfilt.demangle(name)}{Fore.RESET}")

    utils.add_decompiled_functions(new_matches)


if __name__ == '__main__':
    main()
