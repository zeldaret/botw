#!/usr/bin/env python3

import argparse

import oead
from colorama import Fore
import cxxfilt
from pathlib import Path
from typing import Dict

import util.checker
import util.elf
from util import utils


def identify(functions: Dict[str, utils.FunctionInfo], checker: util.checker.FunctionChecker,
             new_matches: Dict[int, str], aidef, aidef_key: str, get_pairs) -> None:
    for name, data in aidef[aidef_key].items():
        orig_name = name
        name = name[0].upper() + name[1:]

        pairs = get_pairs(orig_name, name)
        for orig_fn_name, fn_name in pairs:
            orig_fn_info = functions.get(orig_fn_name, None)
            if orig_fn_info is None:
                continue
            if orig_fn_info.status != utils.FunctionStatus.NotDecompiled:
                continue

            orig_fn = util.elf.get_fn_from_base_elf(orig_fn_info.addr, orig_fn_info.size)
            try:
                decomp_fn = util.elf.get_fn_from_my_elf(fn_name)
            except KeyError:
                continue

            if checker.check(orig_fn, decomp_fn):
                new_matches[orig_fn_info.addr] = fn_name
            else:
                utils.warn(f"non matching: {Fore.BLUE}{cxxfilt.demangle(fn_name)}{Fore.RESET}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Identifies matching AI class functions.")
    parser.add_argument("aidef")
    args = parser.parse_args()

    new_matches: Dict[int, str] = dict()
    checker = util.checker.FunctionChecker()
    functions: Dict[str, utils.FunctionInfo] = {fn.name: fn for fn in utils.get_functions()}

    aidef = oead.byml.from_text(Path(args.aidef).read_text(encoding="utf-8"))

    def get_query_pairs(orig_name, name):
        prefix = f"AI_Query_{orig_name}::"
        return [
            (f"{prefix}ctor", f"_ZN5uking5query{len(name)}{name}C1ERKN4ksys3act2ai5Query7InitArgE"),
            (f"{prefix}dtor", f"_ZN5uking5query{len(name)}{name}D1Ev"),
            (f"{prefix}dtorDelete", f"_ZN5uking5query{len(name)}{name}D0Ev"),
            (f"{prefix}m10", f"_ZN5uking5query{len(name)}{name}10loadParamsERKN4evfl8QueryArgE"),
            (f"{prefix}loadParams", f"_ZN5uking5query{len(name)}{name}10loadParamsEv"),
            (f"{prefix}rtti1",
             f"_ZNK5uking5query{len(name)}{name}27checkDerivedRuntimeTypeInfoEPKN4sead15RuntimeTypeInfo9InterfaceE"),
            (f"{prefix}rtti2", f"_ZNK5uking5query{len(name)}{name}18getRuntimeTypeInfoEv"),
        ]

    identify(functions, checker, new_matches, aidef, "Querys", get_query_pairs)

    utils.add_decompiled_functions(new_matches)


if __name__ == "__main__":
    main()
