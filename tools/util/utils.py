import io

from colorama import Fore, Style
import csv
import warnings
import enum
from pathlib import Path
import sys
import typing as tp

try:
    import cxxfilt
except:
    # cxxfilt cannot be used on Windows.
    warnings.warn("cxxfilt could not be imported; demangling functions will fail")


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
    library: bool
    status: FunctionStatus
    raw_row: tp.List[str]


_markers = {
    "O": FunctionStatus.Matching,
    "m": FunctionStatus.Equivalent,
    "M": FunctionStatus.NonMatching,
    "W": FunctionStatus.Wip,
    "U": FunctionStatus.NotDecompiled,
    "L": FunctionStatus.NotDecompiled,
}


def parse_function_csv_entry(row) -> FunctionInfo:
    ea, stat, size, name = row
    status = _markers.get(stat, FunctionStatus.NotDecompiled)
    decomp_name = ""

    if status != FunctionStatus.NotDecompiled:
        decomp_name = name

    addr = int(ea, 16) - 0x7100000000
    return FunctionInfo(addr, name, int(size), decomp_name, stat == "L", status, row)


def get_functions_csv_path() -> Path:
    return get_repo_root() / "data" / "uking_functions.csv"


def get_functions(path: tp.Optional[Path] = None) -> tp.Iterable[FunctionInfo]:
    if path is None:
        path = get_functions_csv_path()
    with path.open() as f:
        reader = csv.reader(f)
        # Skip headers
        next(reader)
        for row in reader:
            try:
                entry = parse_function_csv_entry(row)
                # excluded library function
                if entry.library:
                    continue
                yield entry
            except ValueError as e:
                raise Exception(f"Failed to parse line {reader.line_num}") from e


def add_decompiled_functions(new_matches: tp.Dict[int, str],
                             new_orig_names: tp.Optional[tp.Dict[int, str]] = None) -> None:
    buffer = io.StringIO()
    writer = csv.writer(buffer, lineterminator="\n")
    for func in get_functions():
        if new_orig_names is not None and func.status == FunctionStatus.NotDecompiled and func.addr in new_orig_names:
            func.raw_row[3] = new_orig_names[func.addr]
        if func.status == FunctionStatus.NotDecompiled and func.addr in new_matches:
            func.raw_row[3] = new_matches[func.addr]
        writer.writerow(func.raw_row)
    get_functions_csv_path().write_text(buffer.getvalue())


def format_symbol_name(name: str) -> str:
    try:
        return f"{cxxfilt.demangle(name)} {Style.DIM}({name}){Style.RESET_ALL}"
    except:
        return name


def format_symbol_name_for_msg(name: str) -> str:
    try:
        return f"{Fore.BLUE}{cxxfilt.demangle(name)}{Fore.RESET} {Style.DIM}({name}){Style.RESET_ALL}{Style.BRIGHT}"
    except:
        return name


def are_demangled_names_equal(name1: str, name2: str):
    return cxxfilt.demangle(name1) == cxxfilt.demangle(name2)


def print_note(msg: str, prefix: str = ""):
    sys.stderr.write(f"{Style.BRIGHT}{prefix}{Fore.CYAN}note:{Fore.RESET} {msg}{Style.RESET_ALL}\n")


def warn(msg: str, prefix: str = ""):
    sys.stderr.write(f"{Style.BRIGHT}{prefix}{Fore.MAGENTA}warning:{Fore.RESET} {msg}{Style.RESET_ALL}\n")


def print_error(msg: str, prefix: str = ""):
    sys.stderr.write(f"{Style.BRIGHT}{prefix}{Fore.RED}error:{Fore.RESET} {msg}{Style.RESET_ALL}\n")


def fail(msg: str, prefix: str = ""):
    print_error(msg, prefix)
    sys.exit(1)


def get_repo_root() -> Path:
    return Path(__file__).parent.parent.parent
