use std::{collections::HashMap, ffi::CStr, fs::File, ops::Range, path::Path};

use anyhow::{anyhow, bail, Context, Result};
use goblin::{
    container,
    elf::{
        dynamic, reloc, section_header, sym, Dynamic, Elf, ProgramHeader, RelocSection,
        SectionHeader, Sym, Symtab,
    },
    elf64::program_header::PT_LOAD,
    strtab::Strtab,
};
use memmap::{Mmap, MmapOptions};
use owning_ref::OwningHandle;
use rustc_hash::FxHashMap;

use crate::repo;

pub type OwnedElf = OwningHandle<Box<(Box<File>, Mmap)>, Box<Elf<'static>>>;
pub type SymbolTableByName<'a> = HashMap<&'a str, goblin::elf::Sym>;
pub type SymbolTableByAddr = FxHashMap<u64, goblin::elf::Sym>;
pub type AddrToNameMap<'a> = FxHashMap<u64, &'a str>;
pub type GlobDataTable = FxHashMap<u64, u64>;

pub struct Function<'a> {
    /// The virtual address of the function in its containing executable.
    /// *Note*: does not contain the IDA base (0x7100000000).
    pub addr: u64,
    /// The bytes that make up the code for this function.
    pub code: &'a [u8],
}

impl<'a> Function<'a> {
    #[inline]
    pub fn get_addr_range(&self) -> Range<u64> {
        self.addr..(self.addr + self.code.len() as u64)
    }
}

#[inline]
fn make_goblin_ctx() -> container::Ctx {
    // 64-bit, little endian
    container::Ctx::new(container::Container::Big, container::Endian::Little)
}

/// A stripped down version of `goblin::elf::Elf::parse`, parsing only the sections that we need.
///
/// *Warning*: In particular, `strtab`, `dynstrtab`, `soname` and `libraries` are **not** parsed.
fn parse_elf_faster(bytes: &[u8]) -> Result<Elf> {
    let header = Elf::parse_header(bytes)?;
    let mut elf = Elf::lazy_parse(header)?;
    let ctx = make_goblin_ctx();

    elf.program_headers =
        ProgramHeader::parse(bytes, header.e_phoff as usize, header.e_phnum as usize, ctx)?;

    elf.section_headers =
        SectionHeader::parse(bytes, header.e_shoff as usize, header.e_shnum as usize, ctx)?;

    let get_strtab = |section_headers: &[SectionHeader], section_idx: usize| {
        if section_idx >= section_headers.len() {
            Ok(Strtab::default())
        } else {
            let shdr = &section_headers[section_idx];
            shdr.check_size(bytes.len())?;
            Strtab::parse(bytes, shdr.sh_offset as usize, shdr.sh_size as usize, 0x0)
        }
    };

    let strtab_idx = header.e_shstrndx as usize;
    elf.shdr_strtab = get_strtab(&elf.section_headers, strtab_idx)?;

    for shdr in &elf.section_headers {
        if shdr.sh_type as u32 == section_header::SHT_SYMTAB {
            let size = shdr.sh_entsize;
            let count = if size == 0 { 0 } else { shdr.sh_size / size };
            elf.syms = Symtab::parse(bytes, shdr.sh_offset as usize, count as usize, ctx)?;
        }
    }

    elf.dynamic = Dynamic::parse(bytes, &elf.program_headers, ctx)?;
    if let Some(ref dynamic) = elf.dynamic {
        let dyn_info = &dynamic.info;
        // parse the dynamic relocations
        elf.dynrelas = RelocSection::parse(bytes, dyn_info.rela, dyn_info.relasz, true, ctx)?;
        elf.dynrels = RelocSection::parse(bytes, dyn_info.rel, dyn_info.relsz, false, ctx)?;
        let is_rela = dyn_info.pltrel as u64 == dynamic::DT_RELA;
        elf.pltrelocs =
            RelocSection::parse(bytes, dyn_info.jmprel, dyn_info.pltrelsz, is_rela, ctx)?;
    }

    Ok(elf)
}

pub fn load_elf(path: &Path) -> Result<OwnedElf> {
    let file = Box::new(File::open(path)?);
    let mmap = unsafe { MmapOptions::new().map(&file)? };

    OwningHandle::try_new(Box::new((file, mmap)), |pair| unsafe {
        let elf = parse_elf_faster(&(*pair).1).with_context(|| "failed to load ELF")?;
        Ok(Box::new(elf))
    })
}

pub fn load_orig_elf() -> Result<OwnedElf> {
    let mut path = repo::get_repo_root()?;
    path.push("data");
    path.push("main.elf");
    load_elf(path.as_path())
}

pub fn load_decomp_elf() -> Result<OwnedElf> {
    let mut path = repo::get_repo_root()?;
    path.push("build");
    path.push("uking");
    load_elf(path.as_path())
}

struct SymbolStringTable<'elf> {
    bytes: &'elf [u8],
}

impl<'elf> SymbolStringTable<'elf> {
    pub fn from_elf(elf: &'elf OwnedElf) -> Result<Self> {
        let bytes = &*elf.as_owner().1;
        for shdr in &elf.section_headers {
            if shdr.sh_type as u32 == section_header::SHT_SYMTAB {
                let table_hdr = elf
                    .section_headers
                    .get(shdr.sh_link as usize)
                    .ok_or_else(|| anyhow!("symbol string table index out of bounds"))?;

                table_hdr.check_size(bytes.len())?;

                let start = table_hdr.sh_offset as usize;
                let end = start + table_hdr.sh_size as usize;
                return Ok(SymbolStringTable {
                    bytes: &bytes[start..end],
                });
            }
        }
        bail!("couldn't find symbol string table")
    }

    pub fn get_string(&self, offset: usize) -> &'elf str {
        unsafe {
            std::str::from_utf8_unchecked(
                CStr::from_ptr(self.bytes[offset..self.bytes.len()].as_ptr() as *const i8)
                    .to_bytes(),
            )
        }
    }
}

fn filter_out_useless_syms(sym: &Sym) -> bool {
    matches!(
        sym.st_type(),
        sym::STT_OBJECT | sym::STT_FUNC | sym::STT_COMMON | sym::STT_TLS
    )
}

pub fn make_symbol_map_by_name(elf: &OwnedElf) -> Result<SymbolTableByName> {
    let mut map = SymbolTableByName::with_capacity_and_hasher(
        elf.syms.iter().filter(filter_out_useless_syms).count(),
        Default::default(),
    );

    let strtab = SymbolStringTable::from_elf(&elf)?;

    for symbol in elf.syms.iter().filter(filter_out_useless_syms) {
        map.entry(strtab.get_string(symbol.st_name))
            .or_insert(symbol);
    }
    Ok(map)
}

pub fn make_symbol_map_by_addr(elf: &OwnedElf) -> SymbolTableByAddr {
    let mut map = SymbolTableByAddr::with_capacity_and_hasher(
        elf.syms.iter().filter(filter_out_useless_syms).count(),
        Default::default(),
    );
    for symbol in elf.syms.iter().filter(filter_out_useless_syms) {
        map.entry(symbol.st_value).or_insert(symbol);
    }
    map
}

pub fn make_addr_to_name_map(elf: &OwnedElf) -> Result<AddrToNameMap> {
    let mut map = AddrToNameMap::with_capacity_and_hasher(
        elf.syms.iter().filter(filter_out_useless_syms).count(),
        Default::default(),
    );

    let strtab = SymbolStringTable::from_elf(&elf)?;

    for symbol in elf.syms.iter().filter(filter_out_useless_syms) {
        map.entry(symbol.st_value)
            .or_insert_with(|| strtab.get_string(symbol.st_name));
    }
    Ok(map)
}

fn parse_symtab<'a>(elf: &'a OwnedElf, shdr: &'a SectionHeader) -> Result<Symtab<'a>> {
    let bytes = &elf.as_owner().1;
    let size = shdr.sh_entsize;
    let count = if size == 0 { 0 } else { shdr.sh_size / size };

    let syms = Symtab::parse(
        bytes,
        shdr.sh_offset as usize,
        count as usize,
        make_goblin_ctx(),
    )?;
    Ok(syms)
}

pub fn find_section<'a>(elf: &'a OwnedElf, name: &str) -> Result<&'a SectionHeader> {
    elf.section_headers
        .iter()
        .find(|&header| &elf.shdr_strtab[header.sh_name] == name)
        .ok_or_else(|| anyhow!("failed to find {} section", name))
}

pub fn get_linked_section<'a>(
    elf: &'a OwnedElf,
    shdr: &'a SectionHeader,
) -> Result<&'a SectionHeader> {
    elf.section_headers
        .get(shdr.sh_link as usize)
        .ok_or_else(|| anyhow!("could not get linked section"))
}

#[inline]
pub fn is_in_section(section: &SectionHeader, addr: u64, size: u64) -> bool {
    let begin = section.sh_addr;
    let end = begin + section.sh_size;
    (begin..end).contains(&addr) && (begin..=end).contains(&(addr + size))
}

pub fn build_glob_data_table(elf: &OwnedElf) -> Result<GlobDataTable> {
    let section = &elf.dynrelas;
    let section_hdr = find_section(elf, ".rela.dyn")?;
    // The corresponding symbol table.
    let symtab = parse_symtab(elf, get_linked_section(elf, &section_hdr)?)?;

    let mut table = GlobDataTable::with_capacity_and_hasher(section.len(), Default::default());

    for reloc in section.iter() {
        let symbol_value: u64 = symtab
            .get(reloc.r_sym)
            .ok_or_else(|| anyhow!("invalid symbol index"))?
            .st_value;

        match reloc.r_type {
            reloc::R_AARCH64_GLOB_DAT => {
                table.insert(
                    reloc.r_offset,
                    (symbol_value as i64 + reloc.r_addend.unwrap()) as u64,
                );
            }
            reloc::R_AARCH64_RELATIVE => {
                // FIXME: this should be Delta(S) + A.
                table.insert(
                    reloc.r_offset,
                    (symbol_value as i64 + reloc.r_addend.unwrap()) as u64,
                );
            }
            _ => (),
        }
    }

    Ok(table)
}

pub fn get_offset_in_file(elf: &OwnedElf, addr: u64) -> Result<usize> {
    let addr = addr as usize;
    for segment in elf.program_headers.iter() {
        if segment.p_type != PT_LOAD {
            continue;
        }

        if segment.vm_range().contains(&addr) {
            return Ok(segment.file_range().start + addr - segment.vm_range().start);
        }
    }
    bail!("{:#x} doesn't belong to any segment", addr)
}

pub fn get_elf_bytes(elf: &OwnedElf, addr: u64, size: u64) -> Result<&[u8]> {
    let offset = get_offset_in_file(&elf, addr)?;
    let size = size as usize;
    Ok(&elf.as_owner().1[offset..(offset + size)])
}

pub fn get_function(elf: &OwnedElf, addr: u64, size: u64) -> Result<Function> {
    Ok(Function {
        addr,
        code: get_elf_bytes(&elf, addr, size)?,
    })
}

pub fn get_function_by_name<'a>(
    elf: &'a OwnedElf,
    symbols: &SymbolTableByName,
    name: &str,
) -> Result<Function<'a>> {
    let symbol = symbols
        .get(&name)
        .ok_or_else(|| anyhow!("unknown function: {}", name))?;
    get_function(&elf, symbol.st_value, symbol.st_size)
}
