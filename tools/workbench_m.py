#!/usr/bin/env python3

import argparse
import csv
import json
import os
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
UKING_ELF = ROOT / "build" / "uking"
MAIN_ELF = ROOT / "data" / "main.elf"
CSV_PATH = ROOT / "data" / "uking_functions.csv"
TOOLCHAIN_DIR = ROOT / "toolchain" / "clang-4.0.1" / "bin"
LLVM_SYMBOLIZER = TOOLCHAIN_DIR / "llvm-symbolizer"
LLVM_NM = TOOLCHAIN_DIR / "llvm-nm"
CACHE_FILE = ROOT / "tools" / ".workbench_m_cache.json"

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

try:
    from colorama import Fore, Style, init
    init(autoreset=True)
except ImportError:
    class _EmptyStr:
        def __getattr__(self, name):
            return ""
    Fore = _EmptyStr()
    Style = _EmptyStr()


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
    """Return (function_name, file_path, line_number) from binary address."""
    if not LLVM_SYMBOLIZER.exists() or not UKING_ELF.exists():
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
        # Format: /path/to/file.cpp:186:0
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


def load_m_functions():
    """Load all functions marked with 'm' (minor non-matching) from CSV."""
    fns = []
    with open(CSV_PATH, "r", encoding="utf-8") as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            if len(row) < 4:
                continue
            addr_str, quality, size_str, mangled = row
            if quality == "m":
                try:
                    demangled = cxxfilt.demangle(mangled) if mangled.startswith("_Z") else mangled
                except Exception:
                    demangled = mangled
                fns.append({
                    "addr": addr_str,
                    "size": int(size_str),
                    "mangled": mangled,
                    "demangled": demangled
                })
    return fns


def run_diff_check(mangled_symbol):
    """Run tools/check and parse diff statistics."""
    check_bin = ROOT / "tools" / "check"
    ret = subprocess.run(
        [str(check_bin), "--no-pager", mangled_symbol],
        capture_output=True,
        text=True
    )
    output = ret.stdout + ret.stderr
    is_ok = ret.returncode == 0 and "OK" in output

    diff_lines = 0
    mod_lines = 0
    missing_lines = 0
    extra_lines = 0
    reorder_lines = 0
    diff_table = []
    in_table = False

    ansi_escape = re.compile(r'\x1b\[[0-9;]*m')

    for line in output.splitlines():
        clean_line = ansi_escape.sub('', line)
        if "TARGET" in clean_line and "CURRENT" in clean_line:
            in_table = True
            diff_table.append(clean_line)
            continue
        if in_table:
            if "still mismatching" in clean_line or "mismatch at" in clean_line or "wrong mnemonic" in clean_line:
                in_table = False
                continue
            diff_table.append(clean_line)
            # Count diff markers: | (mismatch), < (missing), > (extra), i (reordered)
            if " | " in clean_line:
                mod_lines += 1
                diff_lines += 1
            elif " < " in clean_line or clean_line.rstrip().endswith("<"):
                missing_lines += 1
                diff_lines += 1
            elif " > " in clean_line or " > " in clean_line:
                extra_lines += 1
                diff_lines += 1
            elif " i " in clean_line:
                reorder_lines += 1
                diff_lines += 1

    return {
        "ok": is_ok,
        "raw": output,
        "diff_table": "\n".join(diff_table),
        "total_diff_lines": diff_lines,
        "mod": mod_lines,
        "missing": missing_lines,
        "extra": extra_lines,
        "reorder": reorder_lines
    }


def mark_csv_as_matching(mangled_symbol, addr_str):
    """Update function quality from 'm' to 'O' in CSV."""
    lines = CSV_PATH.read_text(encoding="utf-8").splitlines()
    updated = False
    for i, line in enumerate(lines):
        if line.startswith(addr_str + ","):
            parts = line.split(",")
            if len(parts) >= 4:
                parts[1] = "O"
                if not parts[3] or parts[3].strip() == "":
                    parts[3] = mangled_symbol
                lines[i] = ",".join(parts)
                updated = True
                break
    if updated:
        CSV_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")
        return True
    return False


def get_source_snippet(file_path_str, line_num, radius=12):
    """Read a window of C++ lines around target line."""
    p = ROOT / file_path_str
    if not p.is_file():
        return ""
    lines = p.read_text(encoding="utf-8", errors="replace").splitlines()
    start = max(0, line_num - 1 - radius)
    end = min(len(lines), line_num - 1 + radius + 1)
    snippet = []
    for idx in range(start, end):
        prefix = f"{Fore.GREEN}--> {idx+1:4d} | {Style.RESET_ALL}" if idx == (line_num - 1) else f"    {idx+1:4d} | "
        snippet.append(prefix + lines[idx])
    return "\n".join(snippet)


def cmd_list(args):
    print(f"{Fore.CYAN}=== Cargando banco de trabajo de funciones 'm' ==={Style.RESET_ALL}\n")
    m_fns = load_m_functions()
    sym_map = get_symbols_from_binary()

    print(f"Total de funciones 'm' identificadas: {Fore.YELLOW}{len(m_fns)}{Style.RESET_ALL}")
    
    # Sort primarily by size as a proxy for complexity, secondary by address
    m_fns.sort(key=lambda f: f["size"])

    if args.max_size:
        m_fns = [f for f in m_fns if f["size"] <= args.max_size]

    if args.filter:
        flt = args.filter.lower()
        m_fns = [f for f in m_fns if flt in f["demangled"].lower() or flt in f["mangled"].lower()]

    limit = args.limit or 25
    displayed = m_fns[:limit]

    print(f"Mostrando {len(displayed)} funciones prioritarias:\n")
    print(f"{'Idx':<4} {'Tam':<6} {'Dificultad':<12} {'Archivo:Línea':<40} {'Función'}")
    print("-" * 105)

    for i, fn in enumerate(displayed, 1):
        mangled = fn["mangled"]
        size = fn["size"]
        addr_bin = sym_map.get(mangled)
        file_loc = "no localizado"
        if addr_bin:
            _, src_file, line_no = symbolize_address(addr_bin)
            if src_file:
                file_loc = f"{src_file}:{line_no}"

        # Difficulty heuristic
        if size <= 48:
            diff_label = f"{Fore.GREEN}★☆☆ (Fácil){Style.RESET_ALL}"
        elif size <= 128:
            diff_label = f"{Fore.YELLOW}★★☆ (Medio){Style.RESET_ALL}"
        else:
            diff_label = f"{Fore.RED}★★★ (Alto){Style.RESET_ALL}"

        print(f"#{i:<3} {size:<4}b  {diff_label:<21} {file_loc:<40} {Fore.CYAN}{fn['demangled'][:45]}{Style.RESET_ALL}")

    print(f"\n{Fore.WHITE}Para inspeccionar los detalles y el diff asm de cualquiera: {Style.RESET_ALL}")
    print(f"  {Fore.YELLOW}python3 tools/workbench_m.py inspect <índice # | nombre | mangled>{Style.RESET_ALL}\n")


def cmd_inspect(args):
    query = args.query.strip()
    m_fns = load_m_functions()
    sym_map = get_symbols_from_binary()

    target = None
    clean_query = query.lstrip("#")
    if clean_query.isdigit():
        idx = int(clean_query) - 1
        m_fns.sort(key=lambda f: f["size"])
        if 0 <= idx < len(m_fns):
            target = m_fns[idx]
    else:
        for fn in m_fns:
            if query == fn["mangled"] or query == fn["addr"] or query.lower() in fn["demangled"].lower():
                target = fn
                break

    if not target:
        print(f"{Fore.RED}No se encontró ninguna función 'm' que coincida con '{query}'.{Style.RESET_ALL}")
        return

    mangled = target["mangled"]
    addr_bin = sym_map.get(mangled)
    src_file, line_no = "", 0
    if addr_bin:
        _, src_file, line_no = symbolize_address(addr_bin)

    print(f"{Fore.CYAN}================== BANCO DE TRABAJO DE FUNCIÓN =================={Style.RESET_ALL}")
    print(f"{Fore.YELLOW}Función:{Style.RESET_ALL}   {target['demangled']}")
    print(f"{Fore.YELLOW}Símbolo:{Style.RESET_ALL}   {mangled}")
    print(f"{Fore.YELLOW}Dirección:{Style.RESET_ALL} {target['addr']} | Tamaño: {target['size']} bytes")
    if src_file:
        print(f"{Fore.YELLOW}Archivo:{Style.RESET_ALL}   {Fore.GREEN}{src_file}:{line_no}{Style.RESET_ALL}")
    print(f"{Fore.CYAN}----------------------------------------------------------------{Style.RESET_ALL}")

    # Check diff
    print("Ejecutando tools/check...")
    diff_info = run_diff_check(mangled)
    if diff_info["ok"]:
        print(f"{Fore.GREEN}¡LA FUNCIÓN YA COINCIDE AL 100% (OK)!{Style.RESET_ALL}")
        mark_csv_as_matching(mangled, target["addr"])
        return

    print(f"Líneas de discrepancia detectadas: {Fore.YELLOW}{diff_info['total_diff_lines']}{Style.RESET_ALL} "
          f"(Modificadas: {diff_info['mod']}, Faltantes: {diff_info['missing']}, Extras: {diff_info['extra']}, Reordenadas: {diff_info['reorder']})")

    # Automated hints
    print(f"\n{Fore.MAGENTA}--- DIAGNÓSTICO AUTOMÁTICO ---{Style.RESET_ALL}")
    if diff_info["missing"] == 0 and diff_info["extra"] == 0:
        if diff_info["reorder"] > 0 and diff_info["mod"] == 0:
            print(f"{Fore.GREEN}💡 Discrepancia pura de reordenamiento. El compilador generó las mismas instrucciones pero en orden distinto.{Style.RESET_ALL}")
            print(f"   Revisa el orden de asignación de variables miembro o evaluación de argumentos.")
        else:
            print(f"{Fore.YELLOW}💡 Mismo número de instrucciones pero con operandos, registros o constantes distintas.{Style.RESET_ALL}")
    elif diff_info["missing"] > 0 or diff_info["extra"] > 0:
        print(f"{Fore.LIGHTBLUE_EX}💡 Hay instrucciones adicionales o faltantes. Posible branch condicional invertido o inline no deseado.{Style.RESET_ALL}")

    # Show asm diff
    if diff_info["diff_table"]:
        print(f"\n{Fore.CYAN}--- DIFF DE ENSAMBLADOR (tools/check) ---{Style.RESET_ALL}")
        print(diff_info["diff_table"])

    # Show C++ snippet
    if src_file and line_no > 0:
        print(f"\n{Fore.CYAN}--- CÓDIGO FUENTE C++ ({src_file}:{line_no}) ---{Style.RESET_ALL}")
        snippet = get_source_snippet(src_file, line_no, radius=args.radius)
        print(snippet)
        print(f"{Fore.CYAN}----------------------------------------------------------------{Style.RESET_ALL}")


def cmd_test(args):
    """Recompile with Ninja and check function."""
    query = args.query.strip()
    m_fns = load_m_functions()
    target = None
    clean_query = query.lstrip("#")
    if clean_query.isdigit():
        idx = int(clean_query) - 1
        m_fns.sort(key=lambda f: f["size"])
        if 0 <= idx < len(m_fns):
            target = m_fns[idx]
    else:
        for fn in m_fns:
            if query == fn["mangled"] or query == fn["addr"] or query.lower() in fn["demangled"].lower():
                target = fn
                break

    if not target:
        # Maybe already matching
        with open(CSV_PATH) as f:
            for row in csv.reader(f):
                if len(row) >= 4 and (query == row[3] or query.lower() in row[3].lower()):
                    target = {"addr": row[0], "mangled": row[3], "demangled": row[3], "size": int(row[2])}
                    break

    if not target:
        print(f"{Fore.RED}No se encontró la función '{query}'.{Style.RESET_ALL}")
        return

    mangled = target["mangled"]
    print(f"Compilando con Ninja...")
    build_ret = subprocess.run(["ninja", "-C", "build"], capture_output=True, text=True)
    if build_ret.returncode != 0:
        print(f"{Fore.RED}Error de compilación Ninja:{Style.RESET_ALL}")
        print(build_ret.stderr)
        return

    print(f"Verificando {target['demangled']}...")
    diff_info = run_diff_check(mangled)
    if diff_info["ok"]:
        print(f"{Fore.GREEN}✓ ¡100% MATCHING (OK)!{Style.RESET_ALL}")
        mark_csv_as_matching(mangled, target["addr"])
        print(f"{Fore.GREEN}Estado actualizado a 'O' en data/uking_functions.csv.{Style.RESET_ALL}")
    else:
        print(f"{Fore.YELLOW}✗ Sigue habiendo discrepancias ({diff_info['total_diff_lines']} líneas de diff):{Style.RESET_ALL}")
        if diff_info["diff_table"]:
            print(diff_info["diff_table"][:1500])


def main():
    parser = argparse.ArgumentParser(description="BotW Decompilation 'm' Functions Workbench & Closed-Loop Optimizer")
    subparsers = parser.add_subparsers(dest="subcommand", required=True)

    # list
    p_list = subparsers.add_parser("list", help="Listar y categorizar funciones 'm' por dificultad")
    p_list.add_argument("--limit", type=int, default=25, help="Límite a mostrar (default: 25)")
    p_list.add_argument("--max-size", type=int, help="Tamaño máximo en bytes")
    p_list.add_argument("--filter", type=str, help="Filtro de texto en nombre de función")

    # inspect
    p_inspect = subparsers.add_parser("inspect", help="Inspeccionar una función, código fuente y diff asm")
    p_inspect.add_argument("query", type=str, help="Nombre de función, índice (#1, #2) o mangled")
    p_inspect.add_argument("--radius", type=int, default=12, help="Líneas de contexto C++ a mostrar (default: 12)")

    # test
    p_test = subparsers.add_parser("test", help="Recompilar y verificar si la función modificada coincide")
    p_test.add_argument("query", type=str, help="Nombre de función o mangled")

    args = parser.parse_args()

    if args.subcommand == "list":
        cmd_list(args)
    elif args.subcommand == "inspect":
        cmd_inspect(args)
    elif args.subcommand == "test":
        cmd_test(args)


if __name__ == "__main__":
    main()
