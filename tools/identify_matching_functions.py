#!/usr/bin/env python3

import argparse
from colorama import Fore
import csv
import sys
from pathlib import Path
from typing import Dict

import util.checker
import util.elf
from util import utils


def read_candidates(path: Path) -> Dict[str, util.elf.Function]:
    candidates: Dict[str, util.elf.Function] = dict()

    for candidate in path.read_text().splitlines():
        columns = candidate.split()
        if len(columns) == 3:
            candidate = columns[2]

        candidates[candidate] = util.elf.get_fn_from_my_elf(candidate)

    return candidates


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("csv_path",
                        help="Path to a list of functions to identify (in the same format as the main function CSV)")
    parser.add_argument("candidates_path",
                        help="Path to a list of candidates (names only)")
    args = parser.parse_args()

    csv_path = Path(args.csv_path)
    candidates_path = Path(args.candidates_path)

    candidates = read_candidates(candidates_path)

    new_matches: Dict[int, str] = dict()
    checker = util.checker.FunctionChecker()

    # Given a list L of functions to identify and a small list of candidates C, this tool will attempt to
    # automatically identify matches by checking each function in L against each function in C.
    #
    # This matching algorithm is quite naive (quadratic time complexity if both lists have about the same size)
    # but this should work well enough for short lists of candidates...
    for func in utils.get_functions(csv_path):
        if func.status != utils.FunctionStatus.NotDecompiled:
            continue

        match_name = ""

        for candidate_name, candidate in candidates.items():
            if len(candidate.data) != func.size:
                continue
            if checker.check(util.elf.get_fn_from_base_elf(func.addr, func.size), candidate):
                match_name = candidate_name
                break

        if match_name:
            new_matches[func.addr] = match_name
            utils.print_note(
                f"found new match: {Fore.BLUE}{match_name}{Fore.RESET} ({func.addr | 0x71_00000000:#018x})")
            # This is no longer a candidate.
            del candidates[match_name]
        else:
            utils.warn(f"no match found for {Fore.BLUE}{func.name}{Fore.RESET} ({func.addr | 0x71_00000000:#018x})")

    # Output the modified function CSV.
    writer = csv.writer(sys.stdout, lineterminator="\n")
    for func in utils.get_functions():
        if func.status == utils.FunctionStatus.NotDecompiled and func.addr in new_matches:
            func.raw_row[3] = new_matches[func.addr]
        writer.writerow(func.raw_row)


if __name__ == "__main__":
    main()
