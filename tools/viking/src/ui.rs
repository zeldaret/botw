use colored::*;
use std::io::StderrLock;
use std::io::Write;
use textwrap::indent;

use crate::functions;

pub fn print_note(msg: &str) {
    eprintln!("{}{}{}", "note".bold().cyan(), ": ".bold(), msg.bold())
}

pub fn print_warning(msg: &str) {
    eprintln!("{}{}{}", "warning".bold().yellow(), ": ".bold(), msg.bold())
}

pub fn print_error(msg: &str) {
    let stderr = std::io::stderr();
    let mut lock = stderr.lock();
    print_error_ex(&mut lock, msg);
}

pub fn print_error_ex(lock: &mut StderrLock, msg: &str) {
    writeln!(
        lock,
        "{}{}{}",
        "error".bold().red(),
        ": ".bold(),
        msg.bold()
    )
    .unwrap();
}

pub fn format_symbol_name(name: &str) -> String {
    functions::demangle_str(name).map_or(name.blue().to_string(), |demangled| {
        format!("{} ({})", demangled.blue(), name.blue().dimmed(),)
    })
}

pub fn format_address(addr: u64) -> String {
    format!("{:#x}", addr).green().to_string()
}

pub fn print_detail(msg: &str) {
    let stderr = std::io::stderr();
    let mut lock = stderr.lock();
    print_detail_ex(&mut lock, msg);
}

pub fn print_detail_ex(lock: &mut StderrLock, msg: &str) {
    writeln!(
        lock,
        "{}\n",
        indent(
            &msg.clear().to_string(),
            &"  │  ".bold().dimmed().to_string()
        )
    )
    .unwrap();
}
