#!/usr/bin/env python3

import argparse
import csv
import sys
from pathlib import Path
from typing import Set, List

from util import utils


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("csv_path", help="Path to function CSV to merge")
    args = parser.parse_args()

    csv_path = Path(args.csv_path)

    known_fn_addrs: Set[int] = {func.addr for func in utils.get_functions()}
    new_fns: List[utils.FunctionInfo] = []
    for func in utils.get_functions(csv_path):
        if func.addr not in known_fn_addrs:
            new_fns.append(func)

    new_fn_list: List[utils.FunctionInfo] = []
    new_fn_list.extend(utils.get_functions())
    new_fn_list.extend(new_fns)
    new_fn_list.sort(key=lambda func: func.addr)

    # Output the modified function CSV.
    writer = csv.writer(sys.stdout, lineterminator="\n")
    for func in new_fn_list:
        writer.writerow(func.raw_row)


if __name__ == "__main__":
    main()
