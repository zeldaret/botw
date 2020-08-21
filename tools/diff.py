#!/usr/bin/env python3
import argparse
from colorama import Fore, Style
import subprocess
import sys
import utils

parser = argparse.ArgumentParser(description="Diff assembly")
parser.add_argument("function", help="Name of the function to diff. Pass | to get a WIP function", nargs="?", default="|")
args, unknown = parser.parse_known_args()

find_wip = args.function == "|"

for info in utils.get_functions():
    addr_end = info.addr + info.size

    if info.name == args.function or info.decomp_name == args.function or (find_wip and info.status == utils.FunctionStatus.Wip):
        if not info.decomp_name:
            utils.fail(f"{args.function} has not been decompiled")

        subprocess.call(["tools/asm-differ/diff.py", "-e", info.decomp_name, "0x%016x" %
                         info.addr, "0x%016x" % addr_end] + unknown)

        if info.status == utils.FunctionStatus.NonMatching:
            utils.warn(
                f"{args.function} is marked as non-matching and possibly NOT functionally equivalent")
        elif info.status == utils.FunctionStatus.Equivalent:
            utils.warn(f"{args.function} is marked as functionally equivalent but non-matching")

        if find_wip:
            print(
                f"WIP function name: {Style.BRIGHT}{Fore.BLUE}{info.decomp_name}{Style.RESET_ALL}")

        sys.exit(0)

if find_wip:
    utils.fail("no WIP function")

utils.fail(
    f"unknown function '{args.function}'\nfor constructors and destructors, list the complete object constructor (C1) or destructor (D1)")
