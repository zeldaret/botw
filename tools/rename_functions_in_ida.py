# Renames functions in an IDA database to match the function names
# in the decompiled source code.

import csv
import idc
import os

csv_path = os.path.join(os.path.dirname(__file__), "../data/uking_functions.csv")

MARKERS = ("|", "?", "!")

with open(csv_path, "r") as f:
    reader = csv.reader(f)
    for fn in reader:
        addr = int(fn[0], 16)
        decomp_name = fn[3]
        if not decomp_name or decomp_name == "l":
            continue

        # Get rid of status markers.
        if decomp_name[-1] in MARKERS:
            decomp_name = decomp_name[:-1]

        idc.set_name(addr, decomp_name)
