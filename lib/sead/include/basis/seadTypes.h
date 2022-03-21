#ifndef SEAD_TYPES_H_
#define SEAD_TYPES_H_

#ifdef cafe
#include <types.h>
#else
#include <cstddef>
#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using f32 = float;
using f64 = double;

using char16 = char16_t;
using size_t = std::size_t;
#endif

#endif  // SEAD_NEW_H_
