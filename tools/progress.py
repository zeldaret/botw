#!/usr/bin/env python3
import argparse
from colorama import Back, Fore, Style
import utils

parser = argparse.ArgumentParser()
parser.add_argument("--print-nm", "-n", action="store_true",
                    help="Print non-matching functions")
parser.add_argument("--print-eq", "-e", action="store_true",
                    help="Print non-matching, semantically equivalent functions")
parser.add_argument("--print-ok", "-m", action="store_true",
                    help="Print matching functions")
args = parser.parse_args()


num_total = 0
num_matching = 0
num_equivalent = 0
num_nonmatching = 0
num_wip = 0

num_ai_action_done = 0
num_ai_ai_done = 0
num_ai_behavior_done = 0
num_ai_query_done = 0

num_ai_action = 0
num_ai_ai = 0
num_ai_behavior = 0
num_ai_query = 0

for info in utils.get_functions():
    num_total += 1

    if info.name.startswith("AI_F_Action_"):
        num_ai_action += 1
        num_ai_action_done += bool(info.decomp_name)
    if info.name.startswith("AI_F_AI_"):
        num_ai_ai += 1
        num_ai_ai_done += bool(info.decomp_name)
    if info.name.startswith("AI_F_Behavior_"):
        num_ai_behavior += 1
        num_ai_behavior_done += bool(info.decomp_name)
    if info.name.startswith("AI_F_Query_"):
        num_ai_query += 1
        num_ai_query_done += bool(info.decomp_name)

    if not info.decomp_name:
        continue

    if info.status == utils.FunctionStatus.NonMatching:
        num_nonmatching += 1
        if args.print_nm:
            print(f"{Fore.RED}NM{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
    elif info.status == utils.FunctionStatus.Equivalent:
        num_equivalent += 1
        if args.print_eq:
            print(f"{Fore.YELLOW}EQ{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
    elif info.status == utils.FunctionStatus.Matching:
        num_matching += 1
        if args.print_ok:
            print(f"{Fore.GREEN}OK{Fore.RESET} {utils.format_symbol_name(info.decomp_name)}")
    elif info.status == utils.FunctionStatus.Wip:
        num_wip += 1
        print(f"{Back.RED}{Style.BRIGHT}{Fore.WHITE} WIP {Style.RESET_ALL} {utils.format_symbol_name(info.decomp_name)}{Style.RESET_ALL}")

print()
print(f"{num_total} functions")
print(f"{num_matching + num_equivalent} {Fore.CYAN}matching or equivalent{Fore.RESET} ({round(100 * (num_matching + num_equivalent) / num_total, 3)}%)")
print(f"{num_matching} {Fore.GREEN}matching{Fore.RESET} ({round(100 * num_matching / num_total, 3)}%)")
print(f"{num_equivalent} {Fore.YELLOW}equivalent{Fore.RESET} ({round(100 * num_equivalent / num_total, 3)}%)")
print(f"{num_nonmatching} {Fore.RED}non-matching{Fore.RESET} ({round(100 * num_nonmatching / num_total, 3)}%)")

print()
print(f"{num_ai_action_done}/{num_ai_action} actions ({round(100 * num_ai_action_done / num_ai_action, 3)}%)")
print(f"{num_ai_ai_done}/{num_ai_ai} AIs ({round(100 * num_ai_ai_done / num_ai_ai, 3)}%)")
print(f"{num_ai_behavior_done}/{num_ai_behavior} behaviors ({round(100 * num_ai_behavior_done / num_ai_behavior, 3)}%)")
print(f"{num_ai_query_done}/{num_ai_query} queries ({round(100 * num_ai_query_done / num_ai_query, 3)}%)")
