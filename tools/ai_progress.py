#!/usr/bin/env python3
import argparse
from typing import Dict, Optional

import yaml
from colorama import Fore

from util import utils

# TODO: add behaviors after they have been generated
_TYPES = ("action", "ai", "query")


def main() -> None:
    parser = argparse.ArgumentParser("Print AI class decompilation progress.")
    parser.add_argument("-t", "--type", help="AI class type", choices=_TYPES)
    args = parser.parse_args()

    filter_type: Optional[str] = args.type

    data_path = utils.get_repo_root() / "data"
    for class_type in _TYPES:
        if filter_type is not None and class_type != filter_type:
            continue

        with (data_path / f"status_{class_type}.yml").open() as f:
            fns: Dict[str, dict] = yaml.load(f, Loader=yaml.CSafeLoader)

        for name, info in fns.items():
            status = info["status"]
            if status == "done":
                color = Fore.GREEN
            elif status == "wip":
                color = Fore.YELLOW
            elif status == "pending":
                color = ""
            else:
                assert False, f"unexpected status {status}"
            print(f"{color}{name:<50} {color}{info['status']}{Fore.RESET}")


if __name__ == '__main__':
    main()
