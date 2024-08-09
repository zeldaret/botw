import os

DATA_SYMBOLS = os.path.join(os.path.dirname(__file__), '../data/data_symbols.csv')

if __name__ == "__main__":
    lines = {}

    with open(DATA_SYMBOLS, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            hex = "0x" + (line[2:18].upper())
            name = line[19:].strip()
            new_line = f"{hex},{name}"
            lines[hex] = new_line

    with open(DATA_SYMBOLS, "w", encoding="utf-8") as f:
        for hex in sorted(lines):
            f.write(f"{lines[hex]}\n")
    print("data_symbols.csv updated")

