#!/usr/bin/env python3

import csv
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor

ROOT = Path(__file__).resolve().parent.parent
UKING_ELF = ROOT / "build" / "uking"
CSV_PATH = ROOT / "data" / "uking_functions.csv"
TOOLCHAIN_DIR = ROOT / "toolchain" / "clang-4.0.1" / "bin"
LLVM_SYMBOLIZER = TOOLCHAIN_DIR / "llvm-symbolizer"
LLVM_NM = TOOLCHAIN_DIR / "llvm-nm"
CHECK_BIN = ROOT / "tools" / "check"
OUTPUT_JSON = ROOT / "data" / "m_functions_analyzed.json"

try:
    import cxxfilt
except ImportError:
    class _FallbackCxxfilt:
        @staticmethod
        def demangle(name):
            try:
                res = subprocess.run([str(TOOLCHAIN_DIR / "llvm-cxxfilt"), name], capture_output=True, text=True)
                if res.returncode == 0:
                    return res.stdout.strip()
            except Exception:
                pass
            return name
    cxxfilt = _FallbackCxxfilt()


def get_symbols_from_binary():
    """Extract symbol name to address map from build/uking."""
    if not UKING_ELF.exists():
        return {}
    res = subprocess.run([str(LLVM_NM), str(UKING_ELF)], capture_output=True, text=True)
    syms = {}
    for line in res.stdout.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1] in ("T", "t", "W", "w"):
            syms[parts[2]] = parts[0]
    return syms


def symbolize_address(addr_hex):
    if not LLVM_SYMBOLIZER.exists() or not UKING_ELF.exists() or not addr_hex:
        return "", "", 0
    p = subprocess.run(
        [str(LLVM_SYMBOLIZER), f"--obj={UKING_ELF}"],
        input=f"0x{addr_hex}\n",
        capture_output=True,
        text=True
    )
    lines = p.stdout.strip().splitlines()
    if len(lines) >= 2:
        fn_name = lines[0].strip()
        loc = lines[1].strip()
        match = re.match(r'^(.*?):(\d+)(?::\d+)?$', loc)
        if match:
            file_path = match.group(1)
            line_num = int(match.group(2))
            try:
                rel_path = Path(file_path).relative_to(ROOT)
            except ValueError:
                rel_path = Path(file_path)
            return fn_name, str(rel_path), line_num
    return "", "", 0


def analyze_function(fn, sym_map):
    mangled = fn["mangled"]
    size = fn["size"]

    # Symbolize using decomp binary symbol address
    bin_addr = sym_map.get(mangled)
    if bin_addr:
        _, file_path, line_num = symbolize_address(bin_addr)
        fn["file"] = file_path or "Unknown"
        fn["line"] = line_num
    else:
        fn["file"] = "Unknown"
        fn["line"] = 0

    # Run check
    ret = subprocess.run(
        [str(CHECK_BIN), "--no-pager", mangled],
        capture_output=True,
        text=True
    )
    output = ret.stdout + ret.stderr
    is_ok = ret.returncode == 0 and "OK" in output

    ansi_escape = re.compile(r'\x1b\[[0-9;]*m')
    clean_lines = [ansi_escape.sub('', l) for l in output.splitlines()]

    if is_ok:
        fn["status"] = "ALREADY_OK"
        fn["category"] = "ALREADY_OK"
        fn["diff_count"] = 0
        return fn

    # Parse diff table
    diff_lines = 0
    mod_lines = 0
    missing_lines = 0
    extra_lines = 0
    reorder_lines = 0
    in_table = False

    for line in clean_lines:
        if "TARGET" in line and "CURRENT" in line:
            in_table = True
            continue
        if in_table:
            if "still mismatching" in line or "mismatch at" in line or "wrong mnemonic" in line:
                in_table = False
                continue
            if " | " in line:
                mod_lines += 1
                diff_lines += 1
            elif " < " in line or line.rstrip().endswith("<"):
                missing_lines += 1
                diff_lines += 1
            elif " > " in line:
                extra_lines += 1
                diff_lines += 1
            elif " i " in line:
                reorder_lines += 1
                diff_lines += 1

    fn["diff_count"] = diff_lines
    fn["mod_lines"] = mod_lines
    fn["missing_lines"] = missing_lines
    fn["extra_lines"] = extra_lines
    fn["reorder_lines"] = reorder_lines

    # Categorize
    if mangled.startswith("_GLOBAL__sub_I_"):
        fn["category"] = "GLOBAL_INITIALIZER"
    elif missing_lines == 0 and extra_lines == 0 and reorder_lines == 0 and mod_lines > 0:
        fn["category"] = "REG_OR_CONST_DIFF"
    elif missing_lines > 0 and extra_lines == 0:
        fn["category"] = "MISSING_CODE_OR_STRIPPED"
    elif extra_lines > 0 and missing_lines == 0:
        fn["category"] = "EXTRA_CODE"
    elif diff_lines <= 6:
        fn["category"] = "FEW_DIFF_LINES"
    else:
        fn["category"] = "COMPLEX"

    return fn


def main():
    print("=== Extrayendo funciones 'm' de uking_functions.csv ===")
    m_funcs = []
    with open(CSV_PATH, "r", encoding="utf-8") as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            if len(row) >= 4 and row[1] == "m":
                addr, _, size, mangled = row[:4]
                try:
                    demangled = cxxfilt.demangle(mangled) if mangled.startswith("_Z") else mangled
                except Exception:
                    demangled = mangled
                m_funcs.append({
                    "addr": addr,
                    "size": int(size),
                    "mangled": mangled,
                    "demangled": demangled
                })

    total = len(m_funcs)
    print(f"Total de funciones 'm' encontradas: {total}")
    print("Mapeando símbolos del binario compilado...")
    sym_map = get_symbols_from_binary()

    print("Analizando y categorizando con herramientas nativas en paralelo...")
    with ThreadPoolExecutor(max_workers=8) as ex:
        results = list(ex.map(lambda fn: analyze_function(fn, sym_map), m_funcs))

    # Sort results by file, then by size
    results.sort(key=lambda x: (x.get("file", ""), x["size"]))

    # Save to JSON
    with open(OUTPUT_JSON, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)
    print(f"Resultado detallado guardado en: {OUTPUT_JSON}")

    # Summary statistics
    by_category = defaultdict(list)
    by_file = defaultdict(list)
    already_ok = []

    for fn in results:
        cat = fn.get("category", fn.get("status", "UNKNOWN"))
        by_category[cat].append(fn)
        if fn.get("status") == "ALREADY_OK":
            already_ok.append(fn)
        file_key = fn.get("file", "Unknown")
        by_file[file_key].append(fn)

    print("\n" + "=" * 75)
    print(f"RESUMEN EJECUTIVO DE CATEGORIZACIÓN ({total} funciones)")
    print("=" * 75)
    for cat, items in sorted(by_category.items(), key=lambda x: len(x[1]), reverse=True):
        print(f"• {cat:<25}: {len(items):>3} funciones")

    if already_ok:
        print(f"\n¡ATENCIÓN! {len(already_ok)} funciones ya coinciden 100% OK:")
        for fn in already_ok:
            print(f"  - {fn['mangled']} ({fn['file']})")

    print("\n" + "=" * 75)
    print("TOP ARCHIVOS CON MÁS FUNCIONES 'm' PENDIENTES:")
    print("=" * 75)
    sorted_files = sorted(by_file.items(), key=lambda x: len(x[1]), reverse=True)
    for fpath, items in sorted_files[:20]:
        sizes = [fn["size"] for fn in items]
        print(f"• {fpath:<55}: {len(items):>2} fns (tam: {min(sizes)}b .. {max(sizes)}b)")

    print("=" * 75)


if __name__ == "__main__":
    main()
