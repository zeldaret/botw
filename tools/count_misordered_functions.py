#!/usr/bin/env python3

import argparse
import bisect
import re
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable, NamedTuple, TypeVar

from colorama import Fore, Style

from common.util import config, tools, utils

ORIGINAL_BASE = 0x7100000000

T = TypeVar("T")


class Symbol(NamedTuple):
    path: Path
    address: int
    is_weak: bool


class Function(NamedTuple):
    orig_addr: int
    decomp_addr: int
    name: str
    obj: str


@dataclass
class MatchedFunctions:
    functions: list[Function] = field(default_factory=list)
    not_in_binary: int = 0
    shared_inline: int = 0
    ambiguous: int = 0


@dataclass
class Report:
    misordered_objects: list[str]
    stray_functions: list[str]
    misordered_functions: list[str]

    SECTIONS = {
        "misordered objects": "misordered_objects",
        "functions outside their object's main block in the original": "stray_functions",
        "misordered functions within their object": "misordered_functions",
    }
    SUMMARY_NAMES = ("objects", "stray functions", "functions in objects")

    def sections(self) -> dict[str, list[str]]:
        return {title: getattr(self, attribute) for title, attribute in self.SECTIONS.items()}

    def save(self, path: Path) -> None:
        path.write_text("".join(f"# {title}\n" + "".join(f"{line}\n" for line in lines)
                                for title, lines in self.sections().items()))

    @classmethod
    def load(cls, path: Path) -> "Report":
        sections: dict[str, list[str]] = {}
        lines: list[str] = []
        for line in path.read_text().splitlines():
            if line.startswith("# "):
                lines = sections.setdefault(line[2:], [])
            else:
                lines.append(line)
        return cls(**{attribute: sections.get(title, []) for title, attribute in cls.SECTIONS.items()})


def get_function_symbols(paths: list[Path]) -> dict[str, list[Symbol]]:
    objdump = tools.find_tool("llvm-objdump")
    symbols: dict[str, list[Symbol]] = defaultdict(list)
    for i in range(0, len(paths), 500):
        output = subprocess.run([objdump, "--syms", *paths[i:i + 500]], check=True, capture_output=True,
                                text=True).stdout
        path = paths[i]
        for line in output.splitlines():
            if line.endswith("file format elf64-littleaarch64"):
                path = Path(line.partition(":\t")[0])
                continue
            # address, 7 flag columns (binding, weak, ..., type), section<TAB>size name
            if len(line) < 26 or line[23] != "F" or line[25:].startswith("*UND*"):
                continue
            name = line.split()[-1]
            symbols[name].append(Symbol(path, int(line[:16], 16), line[18] == "w"))
    return symbols


def get_link_objects(build_dir: Path) -> list[Path]:
    link_step = f"build {config.get_build_target()}:"
    for line in (build_dir / "build.ninja").read_text().splitlines():
        if line.startswith(link_step):
            inputs = line.split()[3:]
            return [build_dir / path for path in inputs[:inputs.index("||")] if path.endswith(".obj")]
    utils.fail(f"link step not found in {build_dir / 'build.ninja'}")


def get_object_name(path: Path, build_dir: Path) -> str:
    return re.sub(r"CMakeFiles/[^/]+\.dir/", "", str(path.relative_to(build_dir))).removesuffix(".obj")


def match_functions(decomp_elf: Path, build_dir: Path) -> MatchedFunctions:
    binary_symbols = get_function_symbols([decomp_elf])
    object_symbols = get_function_symbols(get_link_objects(build_dir))

    matched = MatchedFunctions()
    for info in utils.get_functions():
        if not info.decomp_name:
            continue
        in_binary = binary_symbols.get(info.decomp_name, [])
        definitions = object_symbols.get(info.decomp_name, [])
        if not in_binary:
            matched.not_in_binary += 1
        elif len(in_binary) == 1 and len(definitions) == 1:
            obj = get_object_name(definitions[0].path, build_dir)
            matched.functions.append(Function(info.addr, in_binary[0].address, info.decomp_name, obj))
        elif all(definition.is_weak for definition in definitions):
            matched.shared_inline += 1
        else:
            matched.ambiguous += 1

    matched.functions.sort()
    return matched


def split_into_runs(functions: list[Function],
                    is_separator: Callable[[Function], bool]) -> dict[str, list[list[Function]]]:
    runs: dict[str, list[list[Function]]] = defaultdict(list)
    separators_seen = 0
    separators_seen_after_object: dict[str, int] = {}
    for function in functions:
        if separators_seen_after_object.get(function.obj) != separators_seen:
            runs[function.obj].append([])
        runs[function.obj][-1].append(function)
        if is_separator(function):
            separators_seen += 1
        separators_seen_after_object[function.obj] = separators_seen
    return runs


def split_into_blocks(functions: list[Function]) -> dict[str, list[list[Function]]]:
    # A stray function must not split the object it lands in, so only functions in their
    # object's longest run separate the other objects' functions.
    runs = split_into_runs(functions, lambda function: True)
    main_run_functions = {function for object_runs in runs.values() for function in max(object_runs, key=len)}
    return split_into_runs(functions, lambda function: function in main_run_functions)


def longest_increasing_subsequence(values: list[int]) -> set[int]:
    tail_values: list[int] = []
    tail_indices: list[int] = []
    predecessors: list[int] = []
    for i, value in enumerate(values):
        position = bisect.bisect_right(tail_values, value)
        predecessors.append(tail_indices[position - 1] if position else -1)
        if position == len(tail_values):
            tail_values.append(value)
            tail_indices.append(i)
        else:
            tail_values[position] = value
            tail_indices[position] = i

    indices: set[int] = set()
    i = tail_indices[-1] if tail_indices else -1
    while i != -1:
        indices.add(i)
        i = predecessors[i]
    return indices


def out_of_order(items: list[T], key: Callable[[T], int]) -> list[T]:
    in_order = longest_increasing_subsequence([key(item) for item in items])
    return [item for i, item in enumerate(items) if i not in in_order]


def describe(function: Function) -> str:
    return f"0x{function.orig_addr + ORIGINAL_BASE:016x} {function.obj} {function.name}"


def colorize(line: str) -> str:
    address, obj, *name = line.split(" ", 2)
    text = f"{address} {Fore.CYAN}{obj}{Fore.RESET}"
    if name:
        text += f" {utils.format_symbol_name(name[0])}"
    return text


def by_address(lines: list[str]) -> dict[int, str]:
    return {int(line.partition(" ")[0], 16): line for line in lines}


def print_comparison(baseline: Report, report: Report) -> bool:
    deltas: list[int] = []
    for (title, old_lines), new_lines in zip(baseline.sections().items(), report.sections().values()):
        old, new = by_address(old_lines), by_address(new_lines)
        changes = sorted([(address, f"{Fore.GREEN}-", line) for address, line in old.items() if address not in new] +
                         [(address, f"{Fore.RED}+", line) for address, line in new.items() if address not in old])
        renamed = sum(1 for address, line in old.items() if address in new and new[address] != line)
        delta = len(new_lines) - len(old_lines)
        deltas.append(delta)
        color = Fore.RED if delta > 0 else Fore.GREEN if delta < 0 else ""
        print(f"{Style.BRIGHT}{title}: {len(old_lines)} -> {len(new_lines)} "
              f"{color}({delta:+d}){Style.RESET_ALL}")
        for _, sign, line in changes:
            print(f"{sign}{Fore.RESET} {colorize(line)}")
        if renamed:
            print(f"{Style.DIM}  {renamed} unchanged except for their object or function name{Style.RESET_ALL}")
        print()

    changes = ", ".join(f"{name} {delta:+d}" for name, delta in zip(Report.SUMMARY_NAMES, deltas))
    print(f"order change: {changes}")
    return any(delta > 0 for delta in deltas)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Measure how closely object and function order in the decomp binary follows the original executable")
    parser.add_argument("-v", "--verbose", action="store_true", help="list the misplaced objects and functions")
    parser.add_argument("--save", type=Path, metavar="FILE", help="save the misplaced objects and functions to FILE")
    parser.add_argument("--baseline", type=Path, metavar="FILE",
                        help="compare against a file written by --save and fail if any misplacement count grew")
    args = parser.parse_args()

    decomp_elf = config.get_decomp_elf().resolve()
    matched = match_functions(decomp_elf, decomp_elf.parent)

    main_runs: dict[str, list[Function]] = {}
    split_objects: list[str] = []
    stray_functions: list[Function] = []
    for obj, runs in split_into_blocks(matched.functions).items():
        main_run = max(runs, key=len)
        main_runs[obj] = main_run
        if len(runs) > 1:
            split_objects.append(obj)
            stray_functions += [function for run in runs if run is not main_run for function in run]
    stray_functions.sort()

    objects_in_original_order = sorted(main_runs, key=lambda obj: main_runs[obj][0].orig_addr)
    misordered_objects = out_of_order(objects_in_original_order,
                                      lambda obj: min(function.decomp_addr for function in main_runs[obj]))

    misordered_functions: list[Function] = []
    for obj in objects_in_original_order:
        misordered_functions += out_of_order(main_runs[obj], lambda function: function.decomp_addr)

    report = Report(
        misordered_objects=[f"0x{main_runs[obj][0].orig_addr + ORIGINAL_BASE:016x} {obj}" for obj in misordered_objects],
        stray_functions=[describe(function) for function in stray_functions],
        misordered_functions=[describe(function) for function in misordered_functions],
    )

    if args.save:
        report.save(args.save)

    if args.verbose:
        for title, lines in report.sections().items():
            print(f"{Style.BRIGHT}{title}{Style.RESET_ALL}")
            for line in lines:
                print(colorize(line))
            print()

    print(f"{len(matched.functions):>7d} compared functions")
    print(f"{Style.DIM}{matched.not_in_binary:>7d} skipped, not in the decomp binary")
    print(f"{matched.shared_inline:>7d} skipped, inline in several objects")
    print(f"{matched.ambiguous:>7d} skipped, ambiguous name{Style.RESET_ALL}")
    print(f"{len(main_runs):>7d} objects")
    print(f"{len(misordered_objects):>7d} {Fore.RED}misordered objects{Fore.RESET}")
    print(f"{len(split_objects):>7d} {Fore.YELLOW}objects split in the original{Fore.RESET} "
          f"({len(stray_functions)} stray functions)")
    print(f"{len(misordered_functions):>7d} {Fore.YELLOW}misordered functions within objects{Fore.RESET}")

    if args.baseline:
        print()
        if print_comparison(Report.load(args.baseline), report):
            sys.stdout.flush()
            utils.fail("this change makes the object or function order worse")


if __name__ == "__main__":
    main()
