#!/usr/bin/env python3
import argparse
from collections import defaultdict
from colorama import Back, Fore, Style
import enum
from pathlib import Path
from util import utils
from util.utils import FunctionStatus
import typing as tp

parser = argparse.ArgumentParser()
parser.add_argument("--csv", "-c", action="store_true",
                    help="Print a CSV line rather than a human-readable progress report")
parser.add_argument("--print-nm", "-n", action="store_true",
                    help="Print non-matching functions with major issues")
parser.add_argument("--print-eq", "-e", action="store_true",
                    help="Print non-matching functions with minor issues")
parser.add_argument("--print-ok", "-m", action="store_true",
                    help="Print matching functions")
parser.add_argument("--hide-nonmatchings-with-dumps", "-H", help="Hide non-matching functions that have expected "
                                                                 "output dumps", action="store_true")
args = parser.parse_args()

code_size_total = 0
num_total = 0
code_size: tp.DefaultDict[FunctionStatus, int] = defaultdict(int)
counts: tp.DefaultDict[FunctionStatus, int] = defaultdict(int)

nonmatching_fns_with_dump = {p.stem for p in (Path(__file__).parent.parent / "expected").glob("*.bin")}


def should_hide_nonmatching(name: str) -> bool:
    if not args.hide_nonmatchings_with_dumps:
        return False
    return name in nonmatching_fns_with_dump


for info in utils.get_functions():
    code_size_total += info.size
    num_total += 1

    if not info.decomp_name:
        continue

    counts[info.status] += 1
    code_size[info.status] += info.size

    if not args.csv:
        if info.status == FunctionStatus.NonMatching:
            if args.print_nm and not should_hide_nonmatching(info.decomp_name):
                print(f"{Fore.RED}NM{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
        elif info.status == FunctionStatus.Equivalent:
            if args.print_eq and not should_hide_nonmatching(info.decomp_name):
                print(f"{Fore.YELLOW}EQ{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
        elif info.status == FunctionStatus.Matching:
            if args.print_ok:
                print(f"{Fore.GREEN}OK{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
        elif info.status == FunctionStatus.Wip:
            print(
                f"{Back.RED}{Style.BRIGHT}{Fore.WHITE} WIP {Style.RESET_ALL} {utils.format_symbol_name(info.decomp_name)}{Style.RESET_ALL}")


def format_progress(label: str, num: int, size: int):
    percentage = round(100 * num / num_total, 3)
    size_percentage = round(100 * size / code_size_total, 3)
    return f"{num:>7d} {label}{Fore.RESET} ({percentage}% | size: {size_percentage}%)"


def format_progress_for_status(label: str, status: FunctionStatus):
    return format_progress(label, counts[status], code_size[status])


if args.csv:
    import git

    version = 1
    git_object = git.Repo().head.object
    timestamp = str(git_object.committed_date)
    git_hash = git_object.hexsha

    fields = [
        str(version),
        timestamp,
        git_hash,

        str(num_total),
        str(code_size_total),

        str(counts[FunctionStatus.Matching]),
        str(code_size[FunctionStatus.Matching]),

        str(counts[FunctionStatus.Equivalent]),
        str(code_size[FunctionStatus.Equivalent]),

        str(counts[FunctionStatus.NonMatching]),
        str(code_size[FunctionStatus.NonMatching]),
    ]
    print(",".join(fields))

else:
    print()

    print(f"{num_total:>7d} functions (size: ~{code_size_total} bytes)")

    count_decompiled = counts[FunctionStatus.Matching] + counts[FunctionStatus.Equivalent] + counts[
        FunctionStatus.NonMatching]
    code_size_decompiled = code_size[FunctionStatus.Matching] + code_size[FunctionStatus.Equivalent] + code_size[
        FunctionStatus.NonMatching]

    print(format_progress(f"{Fore.CYAN}decompiled", count_decompiled, code_size_decompiled))
    print(format_progress_for_status(f"{Fore.GREEN}matching", FunctionStatus.Matching))
    print(format_progress_for_status(f"{Fore.YELLOW}non-matching (minor issues)", FunctionStatus.Equivalent))
    print(format_progress_for_status(f"{Fore.RED}non-matching (major issues)", FunctionStatus.NonMatching))
    print()
