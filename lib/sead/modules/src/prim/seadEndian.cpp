#include <prim/seadEndian.h>

namespace
{
u8 Swap8(u8 val)
{
    return val;
}

u8 Null8(u8 val)
{
    return val;
}

u16 Swap16(u16 val)
{
    return (val << 8 | val >> 8) & 0xFFFF;
}

u16 Null16(u16 val)
{
    return val;
}

u32 Swap32(u32 val)
{
    return val << 24 | (val & 0xFF00) << 8 | val >> 24 | (val >> 8 & 0xFF00);
}

u32 Null32(u32 val)
{
    return val;
}

u64 Swap64(u64 val)
{
    // Couldn't make an implementation that matches the original assembly
    // But this should be much more efficient
    return val << 56 | (val & 0xFF00) << 40 | (val & 0xFF0000) << 24 | (val & 0xFF000000) << 8 |
           val >> 56 | (val >> 40 & 0xFF00) | (val >> 24 & 0xFF0000) | (val >> 8 & 0xFF000000);
}

u64 Null64(u64 val)
{
    return val;
}
}  // anonymous namespace

namespace sead
{
const Endian::Types Endian::cHostEndian = Endian::markToEndian(0xfeff);

const Endian::ConvFuncTable Endian::cConvFuncTable = {
    {&Null8, &Swap8},
    {&Null16, &Swap16},
    {&Null32, &Swap32},
    {&Null64, &Swap64},
};

}  // namespace sead
