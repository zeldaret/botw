import os
import csv

DATA_SYMBOLS = os.path.join(os.path.dirname(__file__), '../data/data_symbols.csv')

if __name__ == "__main__":
    addr2symbol = {}

    with open(DATA_SYMBOLS, "r", encoding="utf-8") as f:
        reader = csv.reader(f)
        # doesn't come with header
        for row in reader:
            if not row: # skip empty
                continue
            addr = int(row[0].strip(), 16)
            name = ""
            if len(row) > 1:
                name = row[1].strip()
            addr2symbol[addr] = name

    with open(DATA_SYMBOLS, "w", encoding="utf-8") as f:
        writer = csv.writer(f, lineterminator="\n")
        for hex in sorted(addr2symbol):
            writer.writerow([f"0x{hex:016X}", addr2symbol[hex]])
    print("data_symbols.csv updated")

