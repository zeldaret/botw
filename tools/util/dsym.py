import csv
from pathlib import Path
import typing as tp

import util.elf


class DataSymbol(tp.NamedTuple):
    addr: int  # without the 0x7100000000 base
    name: str
    size: int


_IDA_BASE = 0x7100000000


class DataSymbolContainer:
    def __init__(self) -> None:
        self.symbols: tp.List[DataSymbol] = []

    def load_from_csv(self, path: Path):
        symtab = util.elf.build_name_to_symbol_table(util.elf.my_symtab)

        with path.open("r") as f:
            for i, line in enumerate(csv.reader(f)):
                if len(line) != 2:
                    raise RuntimeError(f"Invalid line format at line {i}")

                addr = int(line[0], 16) - _IDA_BASE
                name = line[1]
                if name not in symtab:
                    continue
                size = symtab[name].size

                self.symbols.append(DataSymbol(addr, name, size))

        # Sort the list, just in case the entries were not sorted in the CSV.
        self.symbols.sort(key=lambda sym: sym.addr)

    def get_symbol(self, addr: int) -> tp.Optional[DataSymbol]:
        """If addr is part of a known data symbol, this function returns the corresponding symbol."""

        # Perform a binary search on self.symbols.
        a = 0
        b = len(self.symbols) - 1
        while a <= b:
            m = (a + b) // 2

            symbol: DataSymbol = self.symbols[m]
            addr_begin = symbol.addr
            addr_end = addr_begin + symbol.size

            if addr_begin <= addr < addr_end:
                return symbol
            if addr <= addr_begin:
                b = m - 1
            elif addr >= addr_end:
                a = m + 1
            else:
                return None

        return None
