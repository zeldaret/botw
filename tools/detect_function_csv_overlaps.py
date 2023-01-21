#!/usr/bin/env python3
import csv
import io
from common.util import utils

new_rows = []
prev = None

for info in utils.get_functions(all=True):
    if prev is not None:
        if (prev.addr <= info.addr < prev.addr + prev.size) or \
                (prev.addr <= info.addr + info.size < prev.addr + prev.size):
            print(
                f"overlap between {prev.addr:x} and {info.addr:x} (expected size: {info.addr - prev.addr:06})")

        if prev.addr + prev.size != info.addr:
            print(f"gap between {prev.addr:x} and {info.addr:x}")
            new_rows.append([
                f"0x{(prev.addr + prev.size) | 0x7100000000:016x}",
                "U",
                f"{info.addr - (prev.addr + prev.size):06}",
                "",
            ])

    prev = info
    new_rows.append(info.raw_row)

buffer = io.StringIO()
writer = csv.writer(buffer, lineterminator="\n")
writer.writerow("Address,Quality,Size,Name".split(","))
for row in new_rows:
    writer.writerow(row)
utils.get_functions_csv_path().write_text(buffer.getvalue())
