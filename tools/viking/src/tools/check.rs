use anyhow::bail;
use anyhow::ensure;
use anyhow::Context;
use anyhow::Result;
use capstone as cs;
use capstone::arch::BuildsCapstone;
use colored::*;
use itertools::Itertools;
use rayon::prelude::*;
use std::cell::RefCell;
use std::sync::atomic::AtomicBool;
use viking::checks::FunctionChecker;
use viking::elf;
use viking::functions;
use viking::functions::Status;
use viking::repo;
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
    let name = function.name.as_str();
    let decomp_fn = elf::get_function_by_name(&decomp_elf, &decomp_symtab, &name);

    match function.status {
        Status::NotDecompiled if decomp_fn.is_err() => return Ok(true),
        Status::Library => return Ok(true),
        _ => (),
    }

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

        Status::NotDecompiled
        | Status::NonMatchingMinor
        | Status::NonMatchingMajor
        | Status::Wip => {
            let orig_fn = get_orig_fn()?;

            let result = checker
                .check(&mut cs, &orig_fn, &decomp_fn)
                .with_context(|| format!("checking {}", name))?;

            if result.is_none() {
                ui::print_note(&format!(
                    "function {} is marked as {} but matches",
                    ui::format_symbol_name(name),
                    function.status.description(),
                ));
            }
        }

        Status::Library => unreachable!(),
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

fn check_all(
    functions: &[functions::Info],
    checker: &FunctionChecker,
    orig_elf: &elf::OwnedElf,
    decomp_elf: &elf::OwnedElf,
    decomp_symtab: &elf::SymbolTableByName,
) -> Result<()> {
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

fn get_function_to_check_from_args(args: &[String]) -> Result<String> {
    let mut maybe_fn_to_check: Vec<String> = args
        .iter()
        .filter(|s| !s.starts_with("-"))
        .map(|s| s.clone())
        .collect();

    ensure!(
        maybe_fn_to_check.len() == 1,
        "expected only one function name (one argument that isn't prefixed with '-')"
    );

    Ok(maybe_fn_to_check.remove(0))
}

fn check_single(
    functions: &[functions::Info],
    checker: &FunctionChecker,
    orig_elf: &elf::OwnedElf,
    decomp_elf: &elf::OwnedElf,
    decomp_symtab: &elf::SymbolTableByName,
    args: &Vec<String>,
) -> Result<()> {
    let fn_to_check = get_function_to_check_from_args(&args)?;
    let function = functions::find_function_fuzzy(&functions, &fn_to_check)
        .with_context(|| format!("unknown function: {}", ui::format_symbol_name(&fn_to_check)))?;
    let name = function.name.as_str();

    eprintln!("{}", ui::format_symbol_name(name).bold());

    if matches!(function.status, Status::Library) {
        bail!("L functions should not be decompiled");
    }

    let decomp_fn =
        elf::get_function_by_name(&decomp_elf, &decomp_symtab, &name).with_context(|| {
            format!(
                "failed to get decomp function: {}",
                ui::format_symbol_name(name)
            )
        })?;

    let orig_fn = elf::get_function(&orig_elf, function.addr, function.size as u64)?;

    let maybe_mismatch = checker
        .check(&mut make_cs()?, &orig_fn, &decomp_fn)
        .with_context(|| format!("checking {}", name))?;

    let mut should_show_diff = args
        .iter()
        .find(|s| s.as_str() == "--always-diff")
        .is_some();

    if let Some(mismatch) = &maybe_mismatch {
        eprintln!("{}\n{}", "mismatch".red().bold(), &mismatch);
        should_show_diff = true;
    } else {
        eprintln!("{}", "OK".green().bold());
    }

    if should_show_diff {
        let diff_args = args
            .iter()
            .filter(|s| s.as_str() != &fn_to_check && s.as_str() != "--always-diff");

        std::process::Command::new(repo::get_tools_path()?.join("asm-differ").join("diff.py"))
            .arg("-I")
            .arg("-e")
            .arg(name)
            .arg(format!("0x{:016x}", function.addr))
            .arg(format!("0x{:016x}", function.addr + function.size as u64))
            .args(diff_args)
            .status()?;
    }

    let new_status = match maybe_mismatch {
        None => Status::Matching,
        Some(_) => Status::Wip,
    };

    // Update the function status if needed.
    if function.status != new_status {
        ui::print_note(&format!(
            "changing status from {:?} to {:?}",
            function.status, new_status
        ));

        let mut new_functions = functions.iter().cloned().collect_vec();
        new_functions
            .iter_mut()
            .find(|info| info.addr == function.addr)
            .unwrap()
            .status = new_status;
        functions::write_functions(&new_functions)?;
    }

    Ok(())
}

fn main() -> Result<()> {
    let args: Vec<String> = std::env::args().skip(1).collect();

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

    if args.len() >= 1 {
        // Single function mode.
        check_single(
            &functions,
            &checker,
            &orig_elf,
            &decomp_elf,
            &decomp_symtab,
            &args,
        )?;
    } else {
        // Normal check mode.
        check_all(&functions, &checker, &orig_elf, &decomp_elf, &decomp_symtab)?;
    }

    Ok(())
}
