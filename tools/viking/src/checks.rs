use anyhow::{ensure, Result};
use capstone as cs;
use cs::arch::arm64::{Arm64Insn, Arm64Operand, Arm64OperandType};
use itertools::zip;
use lazy_init::Lazy;
use rustc_hash::FxHashMap;
use std::collections::{HashMap, HashSet};
use std::convert::TryInto;
use std::path::{Path, PathBuf};

use crate::{capstone_utils::*, elf, functions, repo, ui};

struct DataSymbol {
    /// Address of the symbol in the original executable.
    pub addr: u64,
    /// Name of the symbol in our source code.
    pub name: String,
    /// Size of the symbol in our source code (according to ELF info).
    pub size: u64,
}

/// Keeps track of known data symbols so that data loads can be validated.
#[derive(Default)]
struct KnownDataSymbolMap {
    /// Symbols. Must be sorted by address.
    symbols: Vec<DataSymbol>,
}

impl KnownDataSymbolMap {
    fn new() -> Self {
        Default::default()
    }

    fn load(&mut self, csv_path: &Path, decomp_symtab: &elf::SymbolTableByName) -> Result<()> {
        let mut reader = csv::ReaderBuilder::new()
            .has_headers(false)
            .quoting(false)
            .from_path(csv_path)?;
        for (line, maybe_record) in reader.records().enumerate() {
            let record = &maybe_record?;
            ensure!(
                record.len() == 2,
                "invalid number of fields on line {}",
                line
            );

            let addr = functions::parse_address(&record[0])?;
            let name = &record[1];

            let symbol = decomp_symtab.get(name);
            // Ignore missing symbols.
            if symbol.is_none() {
                continue;
            }
            let symbol = symbol.unwrap();

            self.symbols.push(DataSymbol {
                addr,
                name: name.to_string(),
                size: symbol.st_size,
            });
        }
        self.symbols.sort_by_key(|sym| sym.addr);
        Ok(())
    }

    /// If addr is part of a known data symbol, this function returns the corresponding symbol.
    fn get_symbol(&self, addr: u64) -> Option<&DataSymbol> {
        // Perform a binary search since `symbols` is sorted.
        let mut a: isize = 0;
        let mut b: isize = self.symbols.len() as isize - 1;
        while a <= b {
            let m = a + (b - a) / 2;

            let mid_symbol = &self.symbols[m as usize];
            let mid_addr_begin = mid_symbol.addr;
            let mid_addr_end = mid_addr_begin + mid_symbol.size as u64;

            if mid_addr_begin <= addr && addr < mid_addr_end {
                return Some(mid_symbol);
            }
            if addr <= mid_addr_begin {
                b = m - 1;
            } else if addr >= mid_addr_end {
                a = m + 1;
            } else {
                break;
            }
        }
        None
    }
}

fn get_data_symbol_csv_path() -> Result<PathBuf> {
    let mut path = repo::get_repo_root()?;
    path.push("data");
    path.push("data_symbols.csv");
    Ok(path)
}

#[derive(Debug)]
pub struct ReferenceDiff {
    pub referenced_symbol: u64,
    pub expected_ref_in_decomp: u64,
    pub actual_ref_in_decomp: u64,

    pub expected_symbol_name: String,
    pub actual_symbol_name: String,
}

impl std::fmt::Display for ReferenceDiff {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "wrong reference to {ref} {ref_name}\n\
            --> decomp source code is referencing {actual} {actual_name}\n\
            --> expected to see {expected} to match original code",
            ref=ui::format_address(self.referenced_symbol),
            ref_name=ui::format_symbol_name(&self.expected_symbol_name),
            expected=ui::format_address(self.expected_ref_in_decomp),
            actual=ui::format_address(self.actual_ref_in_decomp),
            actual_name=ui::format_symbol_name(&self.actual_symbol_name),
        )
    }
}

#[derive(Debug)]
pub enum MismatchCause {
    FunctionSize,
    Register,
    Mnemonic,
    BranchTarget,
    FunctionCall(ReferenceDiff),
    DataReference(ReferenceDiff),
    Immediate,
    Unknown,
}

impl std::fmt::Display for MismatchCause {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match &self {
            Self::FunctionSize => write!(f, "wrong function size"),
            Self::Register => write!(f, "wrong register"),
            Self::Mnemonic => write!(f, "wrong mnemonic"),
            Self::BranchTarget => write!(f, "wrong branch target"),
            Self::FunctionCall(diff) => write!(f, "wrong function call\n{}", diff),
            Self::DataReference(diff) => write!(f, "wrong data reference\n{}", diff),
            Self::Immediate => write!(f, "wrong immediate"),
            Self::Unknown => write!(f, "unknown reason; check diff.py"),
        }
    }
}

#[derive(Debug)]
pub struct Mismatch {
    pub addr_orig: u64,
    pub addr_decomp: u64,
    pub cause: MismatchCause,
}

impl std::fmt::Display for Mismatch {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "mismatch at {}: {}",
            ui::format_address(self.addr_orig),
            self.cause,
        )
    }
}

pub struct FunctionChecker<'a, 'functions, 'orig_elf, 'decomp_elf> {
    decomp_elf: &'decomp_elf elf::OwnedElf,
    decomp_symtab: &'a elf::SymbolTableByName<'decomp_elf>,
    decomp_glob_data_table: elf::GlobDataTable,

    // Optional, only initialized when a mismatch is detected.
    decomp_addr_to_name_map: Lazy<elf::AddrToNameMap<'decomp_elf>>,

    known_data_symbols: KnownDataSymbolMap,
    known_functions: FxHashMap<u64, &'functions functions::Info>,

    orig_elf: &'orig_elf elf::OwnedElf,
    orig_got_section: &'orig_elf goblin::elf::SectionHeader,
}

impl<'a, 'functions, 'orig_elf, 'decomp_elf>
    FunctionChecker<'a, 'functions, 'orig_elf, 'decomp_elf>
{
    pub fn new(
        orig_elf: &'orig_elf elf::OwnedElf,
        decomp_elf: &'decomp_elf elf::OwnedElf,
        decomp_symtab: &'a elf::SymbolTableByName<'decomp_elf>,
        decomp_glob_data_table: elf::GlobDataTable,
        functions: &'functions [functions::Info],
    ) -> Result<Self> {
        let mut known_data_symbols = KnownDataSymbolMap::new();
        known_data_symbols.load(get_data_symbol_csv_path()?.as_path(), &decomp_symtab)?;

        let known_functions = functions::make_known_function_map(functions);
        let orig_got_section = elf::find_section(orig_elf, ".got")?;

        Ok(FunctionChecker {
            decomp_elf,
            decomp_symtab,
            decomp_glob_data_table,
            decomp_addr_to_name_map: Lazy::new(),

            known_data_symbols,
            known_functions,

            orig_elf,
            orig_got_section,
        })
    }

    pub fn check(
        &self,
        cs: &mut cs::Capstone,
        orig_fn: &elf::Function,
        decomp_fn: &elf::Function,
    ) -> Result<Option<Mismatch>> {
        // Keep track of registers that are used with ADRP so that we can check global data
        // references even when data is not placed at the same addresses
        // as in the original executable.
        #[derive(Default)]
        struct State {
            gprs1: HashMap<cs::RegId, u64>,
            gprs2: HashMap<cs::RegId, u64>,
            adrp_pair_registers: HashSet<cs::RegId>,
        }

        impl State {
            fn forget_modified_registers(&mut self, detail: &cs::InsnDetail) {
                for reg in detail.regs_write() {
                    self.adrp_pair_registers.remove(&reg);
                }
            }
        }

        let mut state = State::default();

        if orig_fn.code.len() != decomp_fn.code.len() {
            return Ok(Some(Mismatch {
                addr_orig: orig_fn.addr,
                addr_decomp: decomp_fn.addr,
                cause: MismatchCause::FunctionSize,
            }));
        }

        let mut instructions = try_map_two(&orig_fn, &decomp_fn, |func| {
            cs.disasm_iter(func.code, func.addr)
        })?;

        // Check every pair of instructions.
        while let (Some(i1), Some(i2)) = (instructions.0.next(), instructions.1.next()) {
            let ids = map_two(&i1, &i2, |i| i.id().0);
            let detail = try_map_two(&i1, &i2, |insn| cs.insn_detail(&insn))?;
            let arch_detail = map_pair(&detail, |d| d.arch_detail());
            let ops = map_pair(&arch_detail, |a| a.arm64().unwrap().operands_ref());

            if ids.0 != ids.1 {
                return Self::make_mismatch(&i1, &i2, MismatchCause::Mnemonic);
            }

            let id = ids.0;

            match id.into() {
                // Branches or function calls.
                Arm64Insn::ARM64_INS_B | Arm64Insn::ARM64_INS_BL => {
                    let target =
                        map_pair(&ops, |ops| Arm64Operand::from(&ops[0]).op_type.imm() as u64);

                    // If we are branching outside the function, this is likely a tail call.
                    // Treat it as a function call.
                    if !orig_fn.get_addr_range().contains(&target.0) {
                        if let Some(mismatch_cause) = self.check_function_call(target.0, target.1) {
                            return Self::make_mismatch(&i1, &i2, mismatch_cause);
                        }
                    } else {
                        // Otherwise, it's a simple branch, and both targets must match.
                        if i1.bytes() != i2.bytes() {
                            return Self::make_mismatch(&i1, &i2, MismatchCause::BranchTarget);
                        }
                    }
                }

                // Catch ADRP + (ADD/load/store) instruction pairs.
                Arm64Insn::ARM64_INS_ADRP => {
                    let reg = map_pair(&ops, |ops| Arm64Operand::from(&ops[0]).op_type.reg());
                    let imm =
                        map_pair(&ops, |ops| Arm64Operand::from(&ops[1]).op_type.imm() as u64);

                    if reg.0 != reg.1 {
                        return Self::make_mismatch(&i1, &i2, MismatchCause::Register);
                    }

                    state.gprs1.insert(reg.0, imm.0);
                    state.gprs2.insert(reg.1, imm.1);
                    state.adrp_pair_registers.insert(reg.0);
                }

                // Catch ADRP + ADD instruction pairs.
                Arm64Insn::ARM64_INS_ADD => {
                    let mut diff_ok = false;

                    if ops.0.len() == 3 {
                        let dest_reg =
                            map_pair(&ops, |ops| Arm64Operand::from(&ops[0]).op_type.reg());
                        let reg = map_pair(&ops, |ops| Arm64Operand::from(&ops[1]).op_type.reg());

                        if let Arm64OperandType::Imm(_) = Arm64Operand::from(&ops.0[2]).op_type {
                            let imm =
                                map_pair(&ops, |ops| Arm64Operand::from(&ops[2]).op_type.imm());

                            if dest_reg.0 != dest_reg.1 || reg.0 != reg.1 {
                                return Self::make_mismatch(&i1, &i2, MismatchCause::Register);
                            }

                            // Is this an ADRP pair we can check?
                            if state.adrp_pair_registers.contains(&reg.0) {
                                let orig_addr = state.gprs1[&reg.0] + imm.0 as u64;
                                let decomp_addr = state.gprs2[&reg.1] + imm.1 as u64;

                                if let Some(mismatch_cause) =
                                    self.check_data_symbol(orig_addr, decomp_addr)
                                {
                                    return Self::make_mismatch(&i1, &i2, mismatch_cause);
                                }

                                // If the data symbol reference matches, allow the instructions to be different.
                                diff_ok = true;
                            }
                        }
                    }

                    if !diff_ok && i1.bytes() != i2.bytes() {
                        return Self::make_mismatch(&i1, &i2, MismatchCause::Unknown);
                    }

                    state.forget_modified_registers(&detail.0);
                }

                // Loads and stores (single or paired).
                id if is_id_in_range(Arm64Insn::ARM64_INS_LD1, Arm64Insn::ARM64_INS_LDXRH, id)
                    || is_id_in_range(Arm64Insn::ARM64_INS_ST1, Arm64Insn::ARM64_INS_STXR, id) =>
                {
                    let mut diff_ok = false;

                    // Check all operands for mismatches, except the Arm64OpMem which will be checked later.
                    let mut mem = (None, None);
                    for (op1, op2) in zip(ops.0, ops.1) {
                        let op1 = Arm64Operand::from(op1);
                        let op2 = Arm64Operand::from(op2);
                        if let Some(mem1) = op1.op_type.try_mem() {
                            if let Some(mem2) = op2.op_type.try_mem() {
                                ensure!(
                                    mem.0.is_none() && mem.1.is_none(),
                                    "found more than one OpMem"
                                );
                                mem.0 = Some(mem1);
                                mem.1 = Some(mem2);
                                continue;
                            }
                        }

                        if op1 != op2 {
                            return Self::make_mismatch(&i1, &i2, MismatchCause::Unknown);
                        }
                    }

                    ensure!(mem.0.is_some() && mem.1.is_some(), "didn't find an OpMem");

                    let mem = (mem.0.unwrap(), mem.1.unwrap());

                    if mem.0.base() != mem.1.base() {
                        return Self::make_mismatch(&i1, &i2, MismatchCause::Register);
                    }

                    let reg = mem.0.base();

                    // Is this an ADRP pair we can check?
                    if state.adrp_pair_registers.contains(&reg) {
                        let orig_addr_ptr = (state.gprs1[&reg] as i64 + mem.0.disp() as i64) as u64;
                        let decomp_addr_ptr =
                            (state.gprs2[&reg] as i64 + mem.1.disp() as i64) as u64;

                        if let Some(mismatch_cause) =
                            self.check_data_symbol_ptr(orig_addr_ptr, decomp_addr_ptr)
                        {
                            return Self::make_mismatch(&i1, &i2, mismatch_cause);
                        }

                        // If the data symbol reference matches, allow the instructions to be different.
                        diff_ok = true;
                    }

                    if !diff_ok && i1.bytes() != i2.bytes() {
                        return Self::make_mismatch(&i1, &i2, MismatchCause::Unknown);
                    }

                    state.forget_modified_registers(&detail.0);
                }

                // Anything else.
                _ => {
                    if i1.bytes() != i2.bytes() {
                        return Self::make_mismatch(&i1, &i2, MismatchCause::Unknown);
                    }

                    state.forget_modified_registers(&detail.0);
                }
            }
        }

        Ok(None)
    }

    /// Returns None on success and a MismatchCause on failure.
    fn check_function_call(&self, orig_addr: u64, decomp_addr: u64) -> Option<MismatchCause> {
        let info = *self.known_functions.get(&orig_addr)?;
        let name = info.name.as_str();
        let decomp_symbol = self.decomp_symtab.get(name)?;
        let expected = decomp_symbol.st_value;

        if decomp_addr == expected {
            None
        } else {
            let actual_symbol_name = self.translate_decomp_addr_to_name(decomp_addr);

            Some(MismatchCause::FunctionCall(ReferenceDiff {
                referenced_symbol: orig_addr,
                expected_ref_in_decomp: expected,
                actual_ref_in_decomp: decomp_addr,
                expected_symbol_name: name.to_string(),
                actual_symbol_name: actual_symbol_name.unwrap_or("unknown").to_string(),
            }))
        }
    }

    /// Returns None on success and a MismatchCause on failure.
    fn check_data_symbol_ex(
        &self,
        orig_addr: u64,
        decomp_addr: u64,
        symbol: &DataSymbol,
    ) -> Option<MismatchCause> {
        let decomp_symbol = self.decomp_symtab.get(symbol.name.as_str())?;
        let expected = decomp_symbol.st_value;

        if decomp_addr == expected {
            None
        } else {
            let actual_symbol_name = self.translate_decomp_addr_to_name(decomp_addr);

            Some(MismatchCause::DataReference(ReferenceDiff {
                referenced_symbol: orig_addr,
                expected_ref_in_decomp: expected,
                actual_ref_in_decomp: decomp_addr,
                expected_symbol_name: symbol.name.to_string(),
                actual_symbol_name: actual_symbol_name.unwrap_or("unknown").to_string(),
            }))
        }
    }

    /// Returns None on success and a MismatchCause on failure.
    fn check_data_symbol(&self, orig_addr: u64, decomp_addr: u64) -> Option<MismatchCause> {
        let symbol = self.known_data_symbols.get_symbol(orig_addr)?;
        self.check_data_symbol_ex(orig_addr, decomp_addr, symbol)
    }

    /// Returns None on success and a MismatchCause on failure.
    /// Unlike check_data_symbol, this function takes the addresses of *pointers to* possible data symbols,
    /// not the symbols themselves.
    fn check_data_symbol_ptr(
        &self,
        orig_addr_ptr: u64,
        decomp_addr_ptr: u64,
    ) -> Option<MismatchCause> {
        if !elf::is_in_section(&self.orig_got_section, orig_addr_ptr, 8) {
            return None;
        }

        let orig_offset = elf::get_offset_in_file(&self.orig_elf, orig_addr_ptr).ok()? as u64;
        let orig_addr = u64::from_le_bytes(
            elf::get_elf_bytes(&self.orig_elf, orig_offset, 8)
                .ok()?
                .try_into()
                .ok()?,
        );

        let data_symbol = self.known_data_symbols.get_symbol(orig_addr)?;
        let decomp_addr = *self.decomp_glob_data_table.get(&decomp_addr_ptr)?;
        self.check_data_symbol_ex(orig_addr, decomp_addr, &data_symbol)
    }

    fn make_mismatch(
        i1: &cs::Insn,
        i2: &cs::Insn,
        cause: MismatchCause,
    ) -> Result<Option<Mismatch>> {
        Ok(Some(Mismatch {
            addr_orig: i1.address(),
            addr_decomp: i2.address(),
            cause,
        }))
    }

    #[cold]
    #[inline(never)]
    fn translate_decomp_addr_to_name(&self, decomp_addr: u64) -> Option<&'decomp_elf str> {
        let map = self.decomp_addr_to_name_map.get_or_create(|| {
            let map = elf::make_addr_to_name_map(&self.decomp_elf).ok();
            map.unwrap_or_default()
        });
        map.get(&decomp_addr).copied()
    }
}
