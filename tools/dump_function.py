#!/usr/bin/env python3

import argparse

import util.elf
from util import utils


def dump_fn(name: str) -> None:
    expected_dir = utils.get_repo_root() / "expected"
    try:
        fn = util.elf.get_fn_from_my_elf(name)
        path = expected_dir / f"{name}.bin"
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(fn.data)
    except KeyError:
        utils.fail("could not find function")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("function_name", help="Name of the function to dump")
    args = parser.parse_args()

    dump_fn(args.function_name)


if __name__ == "__main__":
    main()
