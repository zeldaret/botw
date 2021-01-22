#!/usr/bin/env python3
import argparse
from colorama import Fore, Style
import diff_settings
import subprocess
from util import utils

parser = argparse.ArgumentParser(description="Prints build/uking.elf symbols")
parser.add_argument("--print-undefined", "-u",
                    help="Print symbols that are undefined", action="store_true")
parser.add_argument("--print-c2-d2", "-c",
                    help="Print C2/D2 (base object constructor/destructor) symbols", action="store_true")
parser.add_argument("--hide-unknown", "-H",
                    help="Hide symbols that are not present in the original game", action="store_true")
parser.add_argument("--all", "-a", action="store_true")
args = parser.parse_args()

listed_decomp_symbols = {info.decomp_name for info in utils.get_functions()}
original_symbols = {info.name for info in utils.get_functions()}

config: dict = dict()
diff_settings.apply(config, {})
myimg: str = config["myimg"]

entries = [x.strip().split() for x in subprocess.check_output(["nm", "-n", myimg], universal_newlines=True).split("\n")]

for entry in entries:
    if len(entry) == 3:
        addr = int(entry[0], 16)
        symbol_type: str = entry[1]
        name = entry[2]

        if (symbol_type == "t" or symbol_type == "T" or symbol_type == "W") and (
                args.all or name not in listed_decomp_symbols):
            c1_name = name.replace("C2", "C1")
            is_c2_ctor = "C2" in name and c1_name in listed_decomp_symbols and utils.are_demangled_names_equal(
                c1_name, name)

            d1_name = name.replace("D2", "D1")
            is_d2_dtor = "D2" in name and d1_name in listed_decomp_symbols and utils.are_demangled_names_equal(
                d1_name, name)

            if args.print_c2_d2 or not (is_c2_ctor or is_d2_dtor):
                color = Fore.YELLOW
                if name in original_symbols:
                    color = Fore.RED
                elif args.hide_unknown:
                    continue
                if is_c2_ctor or is_d2_dtor:
                    color += Style.DIM
                print(f"{color}UNLISTED {Fore.RESET} {utils.format_symbol_name(name)}")

    elif len(entry) == 2:
        symbol_type = entry[0]
        name = entry[1]

        if symbol_type.upper() == "U" and args.print_undefined:
            print(f"{Fore.CYAN}UNDEFINED{Style.RESET_ALL} {utils.format_symbol_name(name)}")
