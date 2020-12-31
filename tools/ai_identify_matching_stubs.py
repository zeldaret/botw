#!/usr/bin/env python3

import argparse

import oead
from colorama import Fore
import cxxfilt
from pathlib import Path
from typing import Dict, Iterable

import util.checker
import util.elf
from util import utils, ai_common


def identify(functions: Dict[str, utils.FunctionInfo], checker: util.checker.FunctionChecker,
             new_matches: Dict[int, str], class_names: Iterable[str], get_pairs) -> None:
    for name in class_names:
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
                utils.print_note(f"new match: {Fore.BLUE}{cxxfilt.demangle(fn_name)}{Fore.RESET}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Identifies matching AI class functions.")
    parser.add_argument("aidef")
    parser.add_argument("--type", choices=["Action", "AI", "Behavior", "Query"], required=True)
    args = parser.parse_args()

    type_: str = args.type

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
            (f"AI_F_Query_{orig_name}",
             f"_ZN4ksys3act2ai12QueryFactory4makeIN5uking5query{len(name)}{name}EEEPNS1_5QueryERKNS7_7InitArgEPN4sead4HeapE"),
        ]

    def get_action_pairs(orig_name, name):
        pairs = []

        def add_pair(x):
            pairs.append((x, x))

        pairs.append(
            (f"AI_Action_{orig_name}::ctor",
             f"_ZN5uking6action{len(name)}{name}C1ERKN4ksys3act2ai10ActionBase7InitArgE"))
        pairs.append(
            (f"AI_Action{orig_name}::ctor",
             f"_ZN5uking6action{len(name)}{name}C1ERKN4ksys3act2ai10ActionBase7InitArgE"))
        pairs.append((f"AI_F_Action_{orig_name}",
                      f"_ZN4ksys3act2ai13ActionFactory4makeIN5uking6action{len(name)}{name}EEEPNS1_6ActionERKNS1_10ActionBase7InitArgEPN4sead4HeapE"))
        add_pair(f"_ZN5uking6action{len(name)}{name}D1Ev")
        add_pair(f"_ZN5uking6action{len(name)}{name}D0Ev")
        add_pair(f"_ZN5uking6action{len(name)}{name}11loadParams_Ev")
        add_pair(f"_ZN5uking6action{len(name)}{name}5init_EPN4sead4HeapE")
        add_pair(f"_ZN5uking6action{len(name)}{name}6enter_EPN4ksys3act2ai15InlineParamPackE")
        add_pair(f"_ZN5uking6action{len(name)}{name}6leave_Ev")
        add_pair(f"_ZN5uking6action{len(name)}{name}5calc_Ev")
        add_pair(
            f"_ZNK5uking6action{len(name)}{name}27checkDerivedRuntimeTypeInfoEPKN4sead15RuntimeTypeInfo9InterfaceE")
        add_pair(f"_ZNK5uking6action{len(name)}{name}18getRuntimeTypeInfoEv")
        return pairs

    def get_ai_pairs(orig_name, name):
        pairs = []

        def add_pair(x):
            pairs.append((x, x))

        pairs.append(
            (f"AI_AI_{orig_name}::ctor", f"_ZN5uking2ai{len(name)}{name}C1ERKN4ksys3act2ai10ActionBase7InitArgE"))
        pairs.append(
            (f"AI_AI{orig_name}::ctor", f"_ZN5uking2ai{len(name)}{name}C1ERKN4ksys3act2ai10ActionBase7InitArgE"))
        pairs.append((f"AI_F_AI_{orig_name}",
                      f"_ZN4ksys3act2ai9AiFactory4makeIN5uking2ai{len(name)}{name}EEEPNS1_2AiERKNS1_10ActionBase7InitArgEPN4sead4HeapE"))
        add_pair(f"_ZN5uking2ai{len(name)}{name}D1Ev")
        add_pair(f"_ZN5uking2ai{len(name)}{name}D0Ev")
        add_pair(f"_ZN5uking2ai{len(name)}{name}11loadParams_Ev")
        add_pair(f"_ZN5uking2ai{len(name)}{name}5init_EPN4sead4HeapE")
        add_pair(f"_ZN5uking2ai{len(name)}{name}6enter_EPN4ksys3act2ai15InlineParamPackE")
        add_pair(f"_ZN5uking2ai{len(name)}{name}6leave_Ev")
        add_pair(f"_ZN5uking2ai{len(name)}{name}5calc_Ev")
        add_pair(f"_ZNK5uking2ai{len(name)}{name}27checkDerivedRuntimeTypeInfoEPKN4sead15RuntimeTypeInfo9InterfaceE")
        add_pair(f"_ZNK5uking2ai{len(name)}{name}18getRuntimeTypeInfoEv")
        return pairs

    if type_ == "Action":
        action_vtable_names = ai_common.get_action_vtable_names()
        identify(functions, checker, new_matches, action_vtable_names.values(), get_action_pairs)
    if type_ == "AI":
        ai_vtable_names = ai_common.get_ai_vtable_names()
        identify(functions, checker, new_matches, ai_vtable_names.values(), get_ai_pairs)
    elif type_ == "Query":
        identify(functions, checker, new_matches, aidef["Querys"].keys(), get_query_pairs)

    utils.add_decompiled_functions(new_matches)


if __name__ == "__main__":
    main()
