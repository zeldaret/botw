#!/usr/bin/env python3
from common.util import utils

prev = None

for info in utils.get_functions():
    if prev is not None:
        if (prev.addr <= info.addr < prev.addr + prev.size) or \
                (prev.addr <= info.addr + info.size < prev.addr + prev.size):
            print(
                f"overlap between {prev.addr:x} and {info.addr:x} (expected size: {info.addr - prev.addr:06})")

    prev = info
