#!/usr/bin/env python3
import argparse
from colorama import Fore, Style
import cxxfilt
import subprocess
import sys
import utils

parser = argparse.ArgumentParser(description="Diff assembly")
parser.add_argument(
    "function", help="Name of the function to diff. Pass | to get a WIP function", nargs="?", default="|")
args, unknown = parser.parse_known_args()

find_wip = args.function == "|"


def find_function_info(name: str):
    for info in utils.get_functions():
        if info.decomp_name == name or (find_wip and info.status == utils.FunctionStatus.Wip):
            return info

    for info in utils.get_functions():
        if name in cxxfilt.demangle(info.decomp_name):
            return info

    return None


info = find_function_info(args.function)
if info is not None:
    if not info.decomp_name:
        utils.fail(f"{args.function} has not been decompiled")

    print(f"diffing: {Style.BRIGHT}{Fore.BLUE}{cxxfilt.demangle(info.decomp_name)}{Style.RESET_ALL} {Style.DIM}({info.decomp_name}){Style.RESET_ALL}")
    addr_end = info.addr + info.size
    subprocess.call(["tools/asm-differ/diff.py", "-I", "-e", info.decomp_name, "0x%016x" %
                     info.addr, "0x%016x" % addr_end] + unknown)

    if info.status == utils.FunctionStatus.NonMatching:
        utils.warn(
            f"{info.decomp_name} is marked as non-matching and possibly NOT functionally equivalent")
    elif info.status == utils.FunctionStatus.Equivalent:
        utils.warn(f"{info.decomp_name} is marked as functionally equivalent but non-matching")

else:
    if find_wip:
        utils.fail("no WIP function")

    utils.fail(
        f"unknown function '{args.function}'\nfor constructors and destructors, list the complete object constructor (C1) or destructor (D1)")
