use crate::repo;
use anyhow::{bail, ensure, Context, Result};
use rustc_hash::FxHashMap;
use std::path::{Path, PathBuf};

pub enum Status {
    Matching,
    NonMatchingMinor,
    NonMatchingMajor,
    NotDecompiled,
    Wip,
    Library,
}

pub struct Info {
    pub addr: u64,
    pub size: u32,
    pub name: String,
    pub status: Status,
}

impl Info {
    pub fn is_decompiled(&self) -> bool {
        !matches!(self.status, Status::NotDecompiled | Status::Library)
    }
}

pub const ADDRESS_BASE: u64 = 0x71_0000_0000;

fn parse_base_16(value: &str) -> Result<u64> {
    if let Some(stripped) = value.strip_prefix("0x") {
        Ok(u64::from_str_radix(stripped, 16)?)
    } else {
        Ok(u64::from_str_radix(value, 16)?)
    }
}

pub fn parse_address(value: &str) -> Result<u64> {
    Ok(parse_base_16(value)? - ADDRESS_BASE)
}

fn parse_function_csv_entry(record: &csv::StringRecord) -> Result<Info> {
    ensure!(record.len() == 4, "invalid record");

    let addr = parse_address(&record[0])?;
    let status_code = record[1].chars().next();
    let size = record[2].parse::<u32>()?;
    let decomp_name = record[3].to_string();

    let status = match status_code {
        Some('m') => Status::NonMatchingMinor,
        Some('M') => Status::NonMatchingMajor,
        Some('O') => Status::Matching,
        Some('U') => Status::NotDecompiled,
        Some('W') => Status::Wip,
        Some('L') => Status::Library,
        Some(code) => bail!("unexpected status code: {}", code),
        None => bail!("missing status code"),
    };

    Ok(Info {
        addr,
        size,
        name: decomp_name,
        status,
    })
}

pub fn get_functions_csv_path() -> Result<PathBuf> {
    let mut path = repo::get_repo_root()?;
    path.push("data");
    path.push("uking_functions.csv");
    Ok(path)
}

/// Returns a Vec of all functions that are listed in the specified CSV.
pub fn get_functions_for_path(csv_path: &Path) -> Result<Vec<Info>> {
    let mut reader = csv::ReaderBuilder::new()
        .has_headers(false)
        .quoting(false)
        .from_path(csv_path)?;

    // We build the result array manually without using csv iterators for performance reasons.
    let mut result = Vec::with_capacity(110_000);
    let mut record = csv::StringRecord::new();
    let mut line_number = 1;
    if reader.read_record(&mut record)? {
        // Verify that the CSV has the correct format.
        ensure!(record.len() == 4, "invalid record; expected 4 fields");
        ensure!(
            &record[0] == "Address"
                && &record[1] == "Quality"
                && &record[2] == "Size"
                && &record[3] == "Name",
            "wrong CSV format; this program only works with the new function list format (added in commit 1d4c815fbae3)"
        );
        line_number += 1;
    }

    while reader.read_record(&mut record)? {
        result.push(
            parse_function_csv_entry(&record)
                .with_context(|| format!("failed to parse CSV record at line {}", line_number))?,
        );
        line_number += 1;
    }
    Ok(result)
}

/// Returns a Vec of all known functions in the executable.
pub fn get_functions() -> Result<Vec<Info>> {
    get_functions_for_path(get_functions_csv_path()?.as_path())
}

pub fn make_known_function_map(functions: &[Info]) -> FxHashMap<u64, &Info> {
    let mut known_functions =
        FxHashMap::with_capacity_and_hasher(functions.len(), Default::default());

    for function in functions {
        if !function.is_decompiled() {
            continue;
        }
        known_functions.insert(function.addr, function);
    }

    known_functions
}

/// Demangle a C++ symbol.
pub fn demangle_str(name: &str) -> Result<String> {
    if !name.starts_with("_Z") {
        bail!("not an external mangled name");
    }

    let symbol = cpp_demangle::Symbol::new(name)?;
    let options = cpp_demangle::DemangleOptions::new();
    Ok(symbol.demangle(&options)?)
}

pub fn get_expected_dir_path() -> Result<PathBuf> {
    let mut path = repo::get_repo_root()?;
    path.push("expected");
    Ok(path)
}
