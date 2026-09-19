#!/usr/bin/env python3

import argparse
import csv
from collections import Counter, defaultdict
import os
from pathlib import Path
import re
import sys
import subprocess
import time

# Ensure running in tools venv
sys.path.append(str(Path(__file__).resolve().parent))
from common.setup_venv import enter_venv

if __name__ == "__main__":
    enter_venv()

from capstone import Cs, CS_ARCH_ARM64, CS_MODE_ARM
import cxxfilt
from colorama import Fore, Style, init
init(autoreset=True)

ROOT = Path(__file__).resolve().parent.parent
ELF_PATH = ROOT / "data" / "main.elf"
CSV_PATH = ROOT / "data" / "uking_functions.csv"
SRC_DIR = ROOT / "src"

# Text segment offset in main.elf
TEXT_OFFSET = 0x788
BASE_ADDR = 0x7100000000

# Classification Patterns
PAT_VOID_STUB = "VOID_STUB"                  # ret
PAT_RETURN_FALSE = "RETURN_FALSE_OR_ZERO"     # mov w0, wzr; ret
PAT_RETURN_TRUE = "RETURN_TRUE_OR_ONE"       # mov w0, #1; ret
PAT_RETURN_NULLPTR = "RETURN_NULLPTR"         # mov x0, xzr; ret
PAT_RETURN_FLOAT_ZERO = "RETURN_FLOAT_ZERO"   # fmov s0, wzr; ret
PAT_RETURN_FLOAT_ONE = "RETURN_FLOAT_ONE"     # fmov s0, #1.0; ret
PAT_RETURN_CONST_INT = "RETURN_CONST_INT"     # mov w0, #N; ret
PAT_RETURN_MINUS_ONE = "RETURN_MINUS_ONE"     # mov w0, #-1; ret
PAT_GETTER_U8 = "GETTER_U8_OR_BOOL"           # ldrb w0, [x0, #off]; ret
PAT_GETTER_U32 = "GETTER_U32"                 # ldr w0, [x0, #off]; ret
PAT_GETTER_U64 = "GETTER_U64_OR_PTR"          # ldr x0, [x0, #off]; ret
PAT_SETTER_32 = "SETTER_32"                   # str w1, [x0, #off]; ret
PAT_OFFSET_THIS = "OFFSET_THIS"               # add x0, x0, #off; ret
PAT_OTHER = "OTHER"

METHOD_SPECS = {
    "hasUpdateForPreDeleteCb": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": False,
        "override": True,
    },
    "hasPreDeleteCb": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": False,
        "override": True,
    },
    "isChangeable": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": True,
        "override": True,
    },
    "isFailed": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": True,
        "override": True,
    },
    "isFinished": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": True,
        "override": True,
    },
    "updateForPreDelete": {
        "access": "public",
        "ret": "bool",
        "params": "",
        "const": False,
        "override": True,
    },
    "oneShot_": {
        "access": "protected",
        "ret": "bool",
        "params": "",
        "const": False,
        "override": True,
    },
    "init_": {
        "access": "public",
        "ret": "bool",
        "params": "sead::Heap* heap",
        "const": False,
        "override": True,
    },
    "leave_": {
        "access": "public",
        "ret": "void",
        "params": "",
        "const": False,
        "override": True,
    },
    "loadParams_": {
        "access": "public",
        "ret": "void",
        "params": "",
        "const": False,
        "override": True,
    },
    "calc_": {
        "access": "protected",
        "ret": "void",
        "params": "",
        "const": False,
        "override": True,
    },
    "onPreDelete": {
        "access": "public",
        "ret": "void",
        "params": "",
        "const": False,
        "override": True,
    },
    "handleMessage_": {
        "access": "protected",
        "ret": "bool",
        "params": "const ksys::Message& message",
        "const": False,
        "override": True,
    },
    "postLeave": {
        "access": "public",
        "ret": "void",
        "params": "",
        "const": False,
        "override": True,
    },
}


class TrivialFunction:
    def __init__(self, addr_int, size, mangled_name, instructions):
        self.addr = addr_int
        self.size = size
        self.mangled = mangled_name
        self.insns = instructions  # list of (mnemonic, op_str)
        self.asm_str = "; ".join(f"{m} {op}".strip() for m, op in instructions).strip()
        self.pattern, self.pattern_arg = self._classify()
        self.demangled = self._demangle()
        self.class_name, self.method_name = self._parse_symbol()

    def _classify(self):
        asm = self.asm_str
        if asm == "ret":
            return PAT_VOID_STUB, None
        if asm == "mov w0, wzr; ret":
            return PAT_RETURN_FALSE, 0
        if asm == "mov w0, #1; ret":
            return PAT_RETURN_TRUE, 1
        if asm == "mov x0, xzr; ret":
            return PAT_RETURN_NULLPTR, 0
        if asm == "fmov s0, wzr; ret":
            return PAT_RETURN_FLOAT_ZERO, 0.0
        if "fmov s0, #1.0" in asm and asm.endswith("ret"):
            return PAT_RETURN_FLOAT_ONE, 1.0
        if asm == "mov w0, #-1; ret":
            return PAT_RETURN_MINUS_ONE, -1
        
        # Check mov w0, #N; ret
        m = re.match(r"^mov w0, #([0-9a-fx\-]+); ret$", asm)
        if m:
            val = int(m.group(1), 0)
            return PAT_RETURN_CONST_INT, val

        # Check ldrb w0, [x0, #off]; ret
        m = re.match(r"^ldrb w0, \[x0(?:, #([0-9a-fx]+))?\]; ret$", asm)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            return PAT_GETTER_U8, off

        # Check ldr w0, [x0, #off]; ret
        m = re.match(r"^ldr w0, \[x0(?:, #([0-9a-fx]+))?\]; ret$", asm)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            return PAT_GETTER_U32, off

        # Check ldr x0, [x0, #off]; ret
        m = re.match(r"^ldr x0, \[x0(?:, #([0-9a-fx]+))?\]; ret$", asm)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            return PAT_GETTER_U64, off

        # Check add x0, x0, #off; ret
        m = re.match(r"^add x0, x0, #([0-9a-fx]+); ret$", asm)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            return PAT_OFFSET_THIS, off

        # Check str w1, [x0, #off]; ret
        m = re.match(r"^str w1, \[x0(?:, #([0-9a-fx]+))?\]; ret$", asm)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            return PAT_SETTER_32, off

        return PAT_OTHER, None

    def _demangle(self):
        if not self.mangled:
            return ""
        try:
            return cxxfilt.demangle(self.mangled)
        except Exception:
            return self.mangled

    def _parse_symbol(self):
        if not self.demangled:
            return "", ""
        sig = self.demangled.split("(")[0].strip()
        parts = sig.split("::")
        if len(parts) >= 2:
            return parts[-2], parts[-1]
        return "", sig

    def suggest_cpp(self):
        """Returns a suggested C++ method signature/body."""
        is_const = " const" in self.demangled
        const_str = " const" if is_const else ""
        
        if self.pattern == PAT_VOID_STUB:
            return f"void {self.method_name}(){const_str} {{}}"
        if self.pattern == PAT_RETURN_TRUE:
            return f"bool {self.method_name}(){const_str} {{ return true; }}"
        if self.pattern == PAT_RETURN_FALSE:
            return f"bool {self.method_name}(){const_str} {{ return false; }}"
        if self.pattern == PAT_RETURN_NULLPTR:
            return f"void* {self.method_name}(){const_str} {{ return nullptr; }}"
        if self.pattern == PAT_RETURN_FLOAT_ZERO:
            return f"float {self.method_name}(){const_str} {{ return 0.0f; }}"
        if self.pattern == PAT_RETURN_FLOAT_ONE:
            return f"float {self.method_name}(){const_str} {{ return 1.0f; }}"
        if self.pattern == PAT_RETURN_CONST_INT:
            return f"s32 {self.method_name}(){const_str} {{ return {self.pattern_arg}; }}"
        if self.pattern == PAT_RETURN_MINUS_ONE:
            return f"s32 {self.method_name}(){const_str} {{ return -1; }}"
        if self.pattern == PAT_GETTER_U8:
            return f"u8 {self.method_name}(){const_str} {{ /* offset 0x{self.pattern_arg:x} */ return mField_{self.pattern_arg:x}; }}"
        if self.pattern == PAT_GETTER_U32:
            return f"u32 {self.method_name}(){const_str} {{ /* offset 0x{self.pattern_arg:x} */ return mField_{self.pattern_arg:x}; }}"
        if self.pattern == PAT_GETTER_U64:
            return f"u64 {self.method_name}(){const_str} {{ /* offset 0x{self.pattern_arg:x} */ return mField_{self.pattern_arg:x}; }}"
        return f"// Pattern {self.pattern}: {self.asm_str}"


def build_class_to_header_map():
    class_map = {}
    class_regex = re.compile(r'\b(class|struct)\s+([A-Za-z0-9_]+)\b\s*(?::|\{)')
    for h in SRC_DIR.rglob("*.h"):
        try:
            txt = h.read_text(encoding="utf-8")
            for m in class_regex.finditer(txt):
                cname = m.group(2)
                if cname not in class_map or (cname.lower() in h.stem.lower()):
                    class_map[cname] = h
        except Exception:
            pass
    return class_map


def load_trivial_functions(max_size=32, mangled_only=True):
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    functions = []

    with open(ELF_PATH, "rb") as elf_f, open(CSV_PATH, "r", encoding="utf-8") as csv_f:
        reader = csv.reader(csv_f)
        next(reader)  # header
        for row in reader:
            addr_str, quality, size_str, name = row
            if quality != "U":
                continue
            if mangled_only and not name.startswith("_Z"):
                continue
            size = int(size_str)
            if size > max_size or size < 4:
                continue

            addr_int = int(addr_str, 16) - BASE_ADDR
            elf_f.seek(TEXT_OFFSET + addr_int)
            code = elf_f.read(size)
            insns = [(i.mnemonic, i.op_str) for i in md.disasm(code, addr_int)]

            fn = TrivialFunction(addr_int, size, name, insns)
            functions.append(fn)

    return functions


def find_source_file_for_class(class_name, class_map=None):
    if not class_name:
        return None
    if class_map and class_name in class_map:
        return class_map[class_name]
    return None


def inject_method_into_header(header_path, class_name, method_name, method_code, access="public"):
    content = header_path.read_text(encoding="utf-8")
    
    # Locate class definition
    class_match = re.search(r'\bclass\s+' + re.escape(class_name) + r'\b[^{]*\{', content)
    if not class_match:
        return None, "class not found in header"
    
    class_start = class_match.end()
    # Find matching closing brace of class
    brace_count = 1
    class_end = -1
    for i in range(class_start, len(content)):
        if content[i] == '{':
            brace_count += 1
        elif content[i] == '}':
            brace_count -= 1
            if brace_count == 0:
                class_end = i
                break
    
    if class_end == -1:
        return None, "could not find closing brace of class"

    class_body = content[class_start:class_end]

    # Check if method already declared or defined
    if re.search(r'\b' + re.escape(method_name) + r'\b', class_body):
        # Check if declared with semicolon: e.g. "bool isChangeable() const override;"
        decl_pattern = re.compile(
            r'([ \t]*[^\n;]*\b' + re.escape(method_name) + r'\b[^\n;]*);'
        )
        m = decl_pattern.search(class_body)
        if m:
            # Replace declaration with inline body
            decl_full = m.group(1)
            # e.g., replace semicolon with body
            body_only = method_code.split(")", 1)[-1].strip()
            # If method_code has const or override, keep them
            new_decl = decl_full + " " + body_only
            new_class_body = class_body[:m.start()] + new_decl + class_body[m.end():]
            new_content = content[:class_start] + new_class_body + content[class_end:]
            return new_content, "replaced declaration"
        else:
            return None, "method already defined or complex declaration"

    # Not in class body: insert under access label
    indent = "    "
    line_to_insert = f"{indent}{method_code}\n"
    
    access_label = f"{access}:"
    access_idx = class_body.find(access_label)
    if access_idx != -1:
        insert_pos = class_start + access_idx + len(access_label)
        # Find newline after access label
        nl = content.find("\n", insert_pos)
        if nl != -1:
            insert_pos = nl + 1
        new_content = content[:insert_pos] + line_to_insert + content[insert_pos:]
        return new_content, f"inserted under {access_label}"
    else:
        # Create access section before class_end
        new_section = f"\n{access_label}\n{line_to_insert}"
        new_content = content[:class_end] + new_section + content[class_end:]
        return new_content, f"created {access_label} section"


def mark_csv_as_matching(fn):
    addr_str = f"0x{fn.addr + BASE_ADDR:016x}"
    lines = CSV_PATH.read_text(encoding="utf-8").splitlines()
    updated = False
    for i, line in enumerate(lines):
        if line.startswith(addr_str + ","):
            parts = line.split(",")
            if len(parts) >= 4:
                parts[1] = "O"
                if not parts[3] or parts[3].strip() == "":
                    parts[3] = fn.mangled
                lines[i] = ",".join(parts)
                updated = True
                break
    if updated:
        CSV_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")
        return True
    return False


def try_auto_solve_candidate(fn, header_path):
    spec = METHOD_SPECS.get(fn.method_name)
    if not spec:
        return False, "no method spec"

    # Formulate method code
    ret_type = spec["ret"]
    params = spec["params"]
    const_str = " const" if spec["const"] else ""
    override_str = " override" if spec["override"] else ""
    access = spec["access"]

    if fn.pattern == PAT_RETURN_TRUE:
        body = "{ return true; }"
    elif fn.pattern == PAT_RETURN_FALSE:
        body = "{ return false; }"
    elif fn.pattern == PAT_VOID_STUB:
        body = "{}"
    elif fn.pattern == PAT_RETURN_NULLPTR:
        body = "{ return nullptr; }"
    elif fn.pattern == PAT_RETURN_CONST_INT:
        body = f"{{ return {fn.pattern_arg}; }}"
    elif fn.pattern == PAT_RETURN_MINUS_ONE:
        body = "{ return -1; }"
    else:
        return False, f"unsupported pattern {fn.pattern}"

    method_code = f"{ret_type} {fn.method_name}({params}){const_str}{override_str} {body}"

    # Backup header
    orig_content = header_path.read_text(encoding="utf-8")
    new_content, note = inject_method_into_header(header_path, fn.class_name, fn.method_name, method_code, access=access)
    if not new_content:
        return False, f"injection failed: {note}"

    # Apply changes
    header_path.write_text(new_content, encoding="utf-8")

    # Compile with Ninja
    build_ret = subprocess.run(["ninja", "-C", "build"], capture_output=True, text=True)
    if build_ret.returncode != 0:
        header_path.write_text(orig_content, encoding="utf-8")
        err_msg = build_ret.stderr.splitlines()[-1] if build_ret.stderr else "build error"
        return False, f"build failed ({err_msg})"

    # Verify with tools/check
    check_ret = subprocess.run(["tools/check", "--no-pager", fn.mangled], capture_output=True, text=True)
    check_out = check_ret.stdout + check_ret.stderr
    if check_ret.returncode == 0 and "OK" in check_out:
        mark_csv_as_matching(fn)
        return True, "MATCHED OK"
    else:
        # Revert
        header_path.write_text(orig_content, encoding="utf-8")
        # Re-link uking after revert
        subprocess.run(["ninja", "-C", "build"], capture_output=True, text=True)
        return False, "check mismatch"


def cmd_auto(args):
    print(f"{Fore.CYAN}=== Iniciando Auto-Inyección de Funciones Triviales ==={Style.RESET_ALL}\n")
    class_map = build_class_to_header_map()
    fns = load_trivial_functions(max_size=16, mangled_only=True)

    candidates = []
    for fn in fns:
        if fn.method_name not in METHOD_SPECS:
            continue
        if fn.pattern == PAT_OTHER:
            continue
        if args.method and fn.method_name != args.method:
            continue
        if args.pattern and fn.pattern != args.pattern:
            continue
        hdr = find_source_file_for_class(fn.class_name, class_map)
        if hdr:
            candidates.append((fn, hdr))

    print(f"Candidatos con archivo fuente identificados: {Fore.YELLOW}{len(candidates)}{Style.RESET_ALL}")
    if args.limit:
        candidates = candidates[:args.limit]
        print(f"Límite establecido a: {args.limit}")

    success_count = 0
    fail_count = 0

    for i, (fn, hdr) in enumerate(candidates, 1):
        print(f"[{i}/{len(candidates)}] Probando {Fore.CYAN}{fn.class_name}::{fn.method_name}{Style.RESET_ALL} (0x{fn.addr + BASE_ADDR:x}) en {hdr.name}...")
        if args.dry_run:
            spec = METHOD_SPECS[fn.method_name]
            print(f"  [DRY RUN] {fn.suggest_cpp()} -> {hdr.relative_to(ROOT)}")
            continue

        ok, msg = try_auto_solve_candidate(fn, hdr)
        if ok:
            success_count += 1
            print(f"  {Fore.GREEN}✓ {msg}! Estado actualizado a Matching en CSV.{Style.RESET_ALL}")
        else:
            fail_count += 1
            print(f"  {Fore.RED}✗ {msg}{Style.RESET_ALL}")

    print(f"\n{Fore.CYAN}=== Resumen de Auto-Inyección ==={Style.RESET_ALL}")
    print(f"Exitosas: {Fore.GREEN}{success_count}{Style.RESET_ALL}")
    print(f"Fallidas: {Fore.RED}{fail_count}{Style.RESET_ALL}")


def cmd_scan(args):
    print(f"{Fore.CYAN}=== Escaneando funciones triviales en 'U' (tamaño <= {args.max_size} bytes) ==={Style.RESET_ALL}\n")
    fns = load_trivial_functions(max_size=args.max_size, mangled_only=not args.all_symbols)
    
    total = len(fns)
    pat_counts = Counter(fn.pattern for fn in fns)
    
    print(f"Total de funciones analizadas: {Fore.YELLOW}{total}{Style.RESET_ALL}")
    print("\nDesglose por patrón identificado:")
    for pat, count in pat_counts.most_common():
        pct = (count / total) * 100 if total else 0
        color = Fore.GREEN if pat != PAT_OTHER else Fore.LIGHTBLACK_EX
        print(f"  {color}{pat:<25}{Style.RESET_ALL} : {count:5d} ({pct:5.1f}%)")

    # Group by class
    class_map = build_class_to_header_map()
    class_counts = Counter(fn.class_name for fn in fns if fn.class_name and fn.pattern != PAT_OTHER)
    print(f"\nTop 15 clases con más funciones triviales pendientes:")
    for cls, count in class_counts.most_common(15):
        hdr = find_source_file_for_class(cls, class_map)
        status_file = f"{Fore.GREEN}[Fuente: {hdr.name}]{Style.RESET_ALL}" if hdr else f"{Fore.RED}[Sin archivo]{Style.RESET_ALL}"
        print(f"  {Fore.YELLOW}{cls:<35}{Style.RESET_ALL} : {count:3d} funciones {status_file}")


def cmd_list(args):
    class_map = build_class_to_header_map()
    fns = load_trivial_functions(max_size=args.max_size, mangled_only=not args.all_symbols)
    
    filtered = []
    for fn in fns:
        if args.pattern and fn.pattern.lower() != args.pattern.lower():
            continue
        if args.class_name and args.class_name.lower() not in fn.class_name.lower():
            continue
        if args.filter and args.filter.lower() not in fn.demangled.lower():
            continue
        filtered.append(fn)

    print(f"Mostrando {len(filtered)} funciones coincidentes:\n")
    for fn in filtered[:args.limit]:
        hdr = find_source_file_for_class(fn.class_name, class_map)
        file_hint = str(hdr.relative_to(ROOT)) if hdr else "no localizado en src/"
        print(f"{Fore.CYAN}0x{fn.addr + BASE_ADDR:x}{Style.RESET_ALL} ({fn.size}b) [{Fore.MAGENTA}{fn.pattern}{Style.RESET_ALL}]")
        print(f"  {Fore.YELLOW}Demangled:{Style.RESET_ALL} {fn.demangled}")
        print(f"  {Fore.LIGHTBLACK_EX}Mangled:{Style.RESET_ALL}   {fn.mangled}")
        print(f"  {Fore.BLUE}Asm:{Style.RESET_ALL}       {fn.asm_str}")
        print(f"  {Fore.GREEN}Sugerencia:{Style.RESET_ALL} {fn.suggest_cpp()}")
        print(f"  {Fore.WHITE}Archivo:{Style.RESET_ALL}   {file_hint}")
        print()


def cmd_generate(args):
    class_map = build_class_to_header_map()
    fns = load_trivial_functions(max_size=64, mangled_only=False)
    target = None
    
    query = args.query.strip()
    for fn in fns:
        if query == fn.mangled or query == f"0x{fn.addr + BASE_ADDR:x}" or query == fn.demangled:
            target = fn
            break
        if query.lower() in fn.demangled.lower():
            target = fn
            break

    if not target:
        print(f"{Fore.RED}No se encontró ninguna función trivial con la consulta '{query}'.{Style.RESET_ALL}")
        return

    hdr = find_source_file_for_class(target.class_name, class_map)
    print(f"{Fore.CYAN}Función:{Style.RESET_ALL} {target.demangled}")
    print(f"{Fore.CYAN}Dirección:{Style.RESET_ALL} 0x{target.addr + BASE_ADDR:x} ({target.size} bytes)")
    print(f"{Fore.CYAN}Símbolo:{Style.RESET_ALL} {target.mangled}")
    print(f"{Fore.CYAN}Ensamblador original:{Style.RESET_ALL} {target.asm_str}")
    print(f"{Fore.CYAN}Patrón:{Style.RESET_ALL} {target.pattern}")
    print(f"\n{Fore.GREEN}Código C++ sugerido:{Style.RESET_ALL}")
    print(f"  {target.suggest_cpp()}\n")
    if hdr:
        print(f"{Fore.YELLOW}Archivo fuente encontrado:{Style.RESET_ALL} {hdr.relative_to(ROOT)}")
    else:
        print(f"{Fore.RED}No se encontró archivo existente para la clase '{target.class_name}'.{Style.RESET_ALL}")


def main():
    parser = argparse.ArgumentParser(description="BotW Decomp Trivial Functions Auto-Solver & Scanner")
    subparsers = parser.add_subparsers(dest="subcommand", required=True)

    # scan
    p_scan = subparsers.add_parser("scan", help="Escanear y mostrar estadísticas de funciones triviales en U")
    p_scan.add_argument("--max-size", type=int, default=16, help="Tamaño máximo en bytes (default: 16)")
    p_scan.add_argument("--all-symbols", action="store_true", help="Incluir también símbolos sin mangling _Z")

    # list
    p_list = subparsers.add_parser("list", help="Listar funciones triviales con sugerencias")
    p_list.add_argument("--max-size", type=int, default=16, help="Tamaño máximo en bytes")
    p_list.add_argument("--pattern", type=str, help="Filtrar por patrón (ej. RETURN_TRUE_OR_ONE, VOID_STUB, etc.)")
    p_list.add_argument("--class-name", type=str, help="Filtrar por nombre de clase")
    p_list.add_argument("--filter", type=str, help="Filtro de texto libre en el nombre")
    p_list.add_argument("--limit", type=int, default=20, help="Límite de funciones a mostrar (default: 20)")
    p_list.add_argument("--all-symbols", action="store_true", help="Incluir también símbolos sin mangling _Z")

    # generate
    p_gen = subparsers.add_parser("generate", help="Generar sugerencia detallada para un símbolo o dirección específica")
    p_gen.add_argument("query", type=str, help="Nombre de símbolo, función o dirección 0x...")

    # auto
    p_auto = subparsers.add_parser("auto", help="Auto-inyectar y verificar funciones triviales automáticamente")
    p_auto.add_argument("--method", type=str, help="Filtrar por nombre de método específico (ej. hasUpdateForPreDeleteCb, isChangeable)")
    p_auto.add_argument("--pattern", type=str, help="Filtrar por patrón")
    p_auto.add_argument("--limit", type=int, help="Límite de candidatos a probar")
    p_auto.add_argument("--dry-run", action="store_true", help="Simular sin modificar archivos")

    args = parser.parse_args()

    if args.subcommand == "scan":
        cmd_scan(args)
    elif args.subcommand == "list":
        cmd_list(args)
    elif args.subcommand == "generate":
        cmd_generate(args)
    elif args.subcommand == "auto":
        cmd_auto(args)


if __name__ == "__main__":
    main()
