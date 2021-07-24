use anyhow::{bail, Result};
use capstone as cs;
use cs::arch::arm64::{Arm64Insn, Arm64OpMem, Arm64Operand, Arm64OperandType};
use cs::{arch::ArchOperand, RegId};

pub fn translate_cs_error<T>(err: cs::Error) -> Result<T> {
    bail!("capstone error: {}", err)
}

#[inline]
pub fn map_two<'a, T, R, F: FnMut(&'a T) -> R>(x: &'a T, y: &'a T, mut f: F) -> (R, R) {
    (f(x), f(y))
}

#[inline]
pub fn map_pair<'a, T, R, F: FnMut(&'a T) -> R>(pair: &'a (T, T), f: F) -> (R, R) {
    map_two(&pair.0, &pair.1, f)
}

#[inline]
pub fn try_map_two<'a, T, R, F: FnMut(&'a T) -> Result<R, cs::Error>>(
    x: &'a T,
    y: &'a T,
    mut f: F,
) -> Result<(R, R)> {
    Ok((
        f(x).or_else(translate_cs_error)?,
        f(y).or_else(translate_cs_error)?,
    ))
}

/// Checks if `id` is in [start, end] (inclusive range).
#[inline]
pub fn is_id_in_range(start: Arm64Insn, end: Arm64Insn, id: Arm64Insn) -> bool {
    let range = (start as u32)..=(end as u32);
    range.contains(&(id as u32))
}

/// Used to make accessing arch-specific data less cumbersome.
pub trait CsArchOperandUtil {
    fn arm64(&self) -> &Arm64Operand;
}

impl CsArchOperandUtil for ArchOperand {
    fn arm64(&self) -> &Arm64Operand {
        match self {
            Self::Arm64Operand(x) => x,
            _ => unreachable!(),
        }
    }
}

/// Used to make accessing arch-specific data less cumbersome.
pub trait CsArm64OperandTypeUtil {
    fn reg(&self) -> RegId;
    fn imm(&self) -> i64;
    fn try_mem(&self) -> Option<Arm64OpMem>;
    fn mem(&self) -> Arm64OpMem;
}

impl CsArm64OperandTypeUtil for Arm64OperandType {
    fn reg(&self) -> RegId {
        match self {
            Self::Reg(x) => *x,
            _ => panic!("expected Reg, got {:#?}", &self),
        }
    }

    fn imm(&self) -> i64 {
        match self {
            Self::Imm(x) => *x,
            _ => panic!("expected Imm, got {:#?}", &self),
        }
    }

    fn try_mem(&self) -> Option<Arm64OpMem> {
        match self {
            Self::Mem(x) => Some(*x),
            _ => None,
        }
    }

    fn mem(&self) -> Arm64OpMem {
        match self {
            Self::Mem(x) => *x,
            _ => panic!("expected Mem, got {:#?}", &self),
        }
    }
}
