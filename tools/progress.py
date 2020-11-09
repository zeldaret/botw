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
parser.add_argument("--print-nm", "-n", action="store_true",
                    help="Print non-matching functions with major issues")
parser.add_argument("--print-eq", "-e", action="store_true",
                    help="Print non-matching functions with minor issues")
parser.add_argument("--print-ok", "-m", action="store_true",
                    help="Print matching functions")
parser.add_argument("--hide-nonmatchings-with-dumps", "-H", help="Hide non-matching functions that have expected "
                                                                 "output dumps", action="store_true")
args = parser.parse_args()


class AIClassType(enum.Enum):
    Action = 0
    AI = 1
    Behavior = 2
    Query = 3


code_size_total = 0
num_total = 0
code_size: tp.DefaultDict[FunctionStatus, int] = defaultdict(int)
counts: tp.DefaultDict[FunctionStatus, int] = defaultdict(int)
ai_counts: tp.DefaultDict[AIClassType, int] = defaultdict(int)
ai_counts_done: tp.DefaultDict[AIClassType, int] = defaultdict(int)

nonmatching_fns_with_dump = {p.stem for p in (Path(__file__).parent.parent / "expected").glob("*.bin")}


def should_hide_nonmatching(name: str) -> bool:
    if not args.hide_nonmatchings_with_dumps:
        return False
    return name in nonmatching_fns_with_dump


for info in utils.get_functions():
    code_size_total += info.size
    num_total += 1

    ai_class_type: tp.Optional[AIClassType] = None
    if info.name.startswith("AI_F_Action_"):
        ai_class_type = AIClassType.Action
    elif info.name.startswith("AI_F_AI_"):
        ai_class_type = AIClassType.AI
    elif info.name.startswith("AI_F_Behavior_"):
        ai_class_type = AIClassType.Behavior
    elif info.name.startswith("AI_F_Query_"):
        ai_class_type = AIClassType.Query

    if ai_class_type is not None:
        ai_counts[ai_class_type] += 1
        if info.decomp_name:
            ai_counts_done[ai_class_type] += 1

    if not info.decomp_name:
        continue

    counts[info.status] += 1
    code_size[info.status] += info.size

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


def format_ai_progress(label: str, class_type: AIClassType):
    percentage = round(100 * ai_counts_done[class_type] / ai_counts[class_type], 3)
    return f"{ai_counts_done[class_type]:>7d} {label}{Fore.RESET} ({percentage}%)"


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
print(format_ai_progress("actions", AIClassType.Action))
print(format_ai_progress("AIs", AIClassType.AI))
print(format_ai_progress("behaviors", AIClassType.Behavior))
print(format_ai_progress("queries", AIClassType.Query))
