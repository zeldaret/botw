from colorama import Fore, Style
import csv
import cxxfilt
import enum
from pathlib import Path
import sys
import typing as tp


class FunctionStatus(enum.Enum):
    Matching = 0
    Equivalent = 1  # semantically equivalent but not perfectly matching
    NonMatching = 2
    Wip = 3
    NotDecompiled = 4


class FunctionInfo(tp.NamedTuple):
    addr: int  # without the 0x7100000000 base
    name: str
    size: int
    decomp_name: str
    status: FunctionStatus


_markers = {
    "?": FunctionStatus.Equivalent,
    "!": FunctionStatus.NonMatching,
    "|": FunctionStatus.Wip,
}


def parse_function_csv_entry(row) -> FunctionInfo:
    ea, name, size, decomp_name = row
    if decomp_name:
        status = FunctionStatus.Matching

        for marker, new_status in _markers.items():
            if decomp_name[-1] == marker:
                status = new_status
                decomp_name = decomp_name[:-1]
                break
    else:
        status = FunctionStatus.NotDecompiled

    addr = int(ea, 16) - 0x7100000000
    return FunctionInfo(addr, name, int(size, 0), decomp_name, status)


def get_functions() -> tp.Iterable[FunctionInfo]:
    with (Path(__file__).parent.parent / "data" / "uking_functions.csv").open() as f:
        for row in csv.reader(f):
            yield parse_function_csv_entry(row)


def format_symbol_name(name: str) -> str:
    try:
        return f"{cxxfilt.demangle(name)} {Style.DIM}({name}){Style.RESET_ALL}"
    except:
        return name


def are_demangled_names_equal(name1: str, name2: str):
    return cxxfilt.demangle(name1) == cxxfilt.demangle(name2)


def warn(msg: str):
    sys.stderr.write(f"{Fore.MAGENTA}{Style.BRIGHT}warning:{Fore.RESET} {msg}{Style.RESET_ALL}\n")


def print_error(msg: str):
    sys.stderr.write(f"{Fore.RED}{Style.BRIGHT}error:{Fore.RESET} {msg}{Style.RESET_ALL}\n")


def fail(msg: str):
    print_error(msg)
    sys.exit(1)
