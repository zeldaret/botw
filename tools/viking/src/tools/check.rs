use anyhow::bail;
use anyhow::Context;
use anyhow::Result;
use capstone as cs;
use capstone::arch::BuildsCapstone;
use colored::*;
use rayon::prelude::*;
use std::cell::RefCell;
use std::sync::atomic::AtomicBool;
use viking::checks::FunctionChecker;
use viking::elf;
use viking::functions;
use viking::functions::Status;
use viking::ui;

use mimalloc::MiMalloc;

#[global_allocator]
static GLOBAL: MiMalloc = MiMalloc;

/// Returns false if the program should exit with a failure code at the end.
fn check_function(
    checker: &FunctionChecker,
    mut cs: &mut capstone::Capstone,
    orig_elf: &elf::OwnedElf,
    decomp_elf: &elf::OwnedElf,
    decomp_symtab: &elf::SymbolTableByName,
    function: &functions::Info,
) -> Result<bool> {
    if !function.is_decompiled() {
        return Ok(true);
    }

    let name = function.name.as_str();
    let decomp_fn = elf::get_function_by_name(&decomp_elf, &decomp_symtab, &name);

    if decomp_fn.is_err() {
        let error = decomp_fn.err().unwrap();
        ui::print_warning(&format!(
            "couldn't check {}: {}",
            ui::format_symbol_name(name),
            error.to_string().dimmed(),
        ));
        return Ok(true);
    }

    let decomp_fn = decomp_fn.unwrap();

    let get_orig_fn = || {
        elf::get_function(&orig_elf, function.addr, function.size as u64).with_context(|| {
            format!(
                "failed to get function {} ({}) from the original executable",
                name,
                ui::format_address(function.addr),
            )
        })
    };

    match function.status {
        Status::Matching => {
            let orig_fn = get_orig_fn()?;

            let result = checker
                .check(&mut cs, &orig_fn, &decomp_fn)
                .with_context(|| format!("checking {}", name))?;

            if let Some(mismatch) = result {
                let stderr = std::io::stderr();
                let mut lock = stderr.lock();
                ui::print_error_ex(
                    &mut lock,
                    &format!(
                        "function {} is marked as matching but does not match",
                        ui::format_symbol_name(name),
                    ),
                );
                ui::print_detail_ex(&mut lock, &format!("{}", mismatch));
                return Ok(false);
            }
        }

        Status::NonMatchingMinor | Status::NonMatchingMajor => {
            let orig_fn = get_orig_fn()?;

            let result = checker
                .check(&mut cs, &orig_fn, &decomp_fn)
                .with_context(|| format!("checking {}", name))?;

            if result.is_none() {
                ui::print_note(&format!(
                    "function {} is marked as non-matching but matches",
                    ui::format_symbol_name(name),
                ));
            }
        }

        Status::NotDecompiled | Status::Library => unreachable!(),
    };

    Ok(true)
}

#[cold]
#[inline(never)]
fn make_cs() -> Result<cs::Capstone> {
    cs::Capstone::new()
        .arm64()
        .mode(cs::arch::arm64::ArchMode::Arm)
        .detail(true)
        .build()
        .or_else(viking::capstone_utils::translate_cs_error)
}

thread_local! {
    static CAPSTONE: RefCell<cs::Capstone> = RefCell::new(make_cs().unwrap());
}

fn main() -> Result<()> {
    let orig_elf = elf::load_orig_elf().with_context(|| "failed to load original ELF")?;
    let decomp_elf = elf::load_decomp_elf().with_context(|| "failed to load decomp ELF")?;

    // Load these in parallel.
    let mut decomp_symtab = None;
    let mut decomp_glob_data_table = None;
    let mut functions = None;

    rayon::scope(|s| {
        s.spawn(|_| decomp_symtab = Some(elf::make_symbol_map_by_name(&decomp_elf)));
        s.spawn(|_| decomp_glob_data_table = Some(elf::build_glob_data_table(&decomp_elf)));
        s.spawn(|_| functions = Some(functions::get_functions()));
    });

    let decomp_symtab = decomp_symtab
        .unwrap()
        .with_context(|| "failed to make symbol map")?;

    let decomp_glob_data_table = decomp_glob_data_table
        .unwrap()
        .with_context(|| "failed to make global data table")?;

    let functions = functions
        .unwrap()
        .with_context(|| "failed to load function CSV")?;

    let checker = FunctionChecker::new(
        &orig_elf,
        &decomp_elf,
        &decomp_symtab,
        decomp_glob_data_table,
        &functions,
    )
    .with_context(|| "failed to construct FunctionChecker")?;

    let failed = AtomicBool::new(false);

    functions.par_iter().try_for_each(|function| {
        CAPSTONE.with(|cs| -> Result<()> {
            let mut cs = cs.borrow_mut();
            let ok = check_function(
                &checker,
                &mut cs,
                &orig_elf,
                &decomp_elf,
                &decomp_symtab,
                function,
            )?;
            if !ok {
                failed.store(true, std::sync::atomic::Ordering::Relaxed);
            }

            Ok(())
        })
    })?;

    if failed.load(std::sync::atomic::Ordering::Relaxed) {
        bail!("found at least one error");
    } else {
        Ok(())
    }
}
