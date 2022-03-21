#ifndef SEAD_ENDIAN_H_
#define SEAD_ENDIAN_H_

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <prim/seadBitUtil.h>

namespace sead
{
class Endian
{
public:
    enum Types
    {
        cBig = 0,
        cLittle = 1,
    };

    struct ConvFuncTable
    {
        typedef u8 (*CONV8FUNC)(u8);
        typedef u16 (*CONV16FUNC)(u16);
        typedef u32 (*CONV32FUNC)(u32);
        typedef u64 (*CONV64FUNC)(u64);

        CONV8FUNC conv8[2];
        CONV16FUNC conv16[2];
        CONV32FUNC conv32[2];
        CONV64FUNC conv64[2];
    };

    static Types getHostEndian() { return cHostEndian; }

    static Types markToEndian(u16 bom)
    {
        u8* bom_ = reinterpret_cast<u8*>(&bom);
        if (*bom_ == 0xff && *(bom_ + 1) == 0xfe)
            return cLittle;

        if (*bom_ == 0xfe && *(bom_ + 1) == 0xff)
            return cBig;

        SEAD_ASSERT_MSG(false, "Undefined endian mark(0x%02x 0x%02x)", bom_[0], bom_[1]);
        return cLittle;
    }

    static u16 endianToMark(Types endian) { return endian == cBig ? 0xFEFF : 0xFFFE; }

    static u8 swapU8(u8 v) { return cConvFuncTable.conv8[1](v); }
    static u16 swapU16(u16 v) { return cConvFuncTable.conv16[1](v); }
    static u32 swapU32(u32 v) { return cConvFuncTable.conv32[1](v); }
    static u64 swapU64(u64 v) { return cConvFuncTable.conv64[1](v); }
    static s8 swapS8(s8 v) { return swapU8(v); }
    static s16 swapS16(s16 v) { return swapU16(v); }
    static s32 swapS32(s32 v) { return swapU32(v); }
    static s64 swapS64(s64 v) { return swapU64(v); }
    static f32 swapF32(f32 v) { return BitUtil::bitCast<f32>(swapU32(BitUtil::bitCast<u32>(v))); }

    static u8 convertU8(Types from, Types to, u8 v) { return cConvFuncTable.conv8[from ^ to](v); }
    static u16 convertU16(Types from, Types to, u16 v)
    {
        return cConvFuncTable.conv16[from ^ to](v);
    }
    static u32 convertU32(Types from, Types to, u32 v)
    {
        return cConvFuncTable.conv32[from ^ to](v);
    }
    static u64 convertU64(Types from, Types to, u64 v)
    {
        return cConvFuncTable.conv64[from ^ to](v);
    }

    static s8 convertS8(Types from, Types to, s8 v) { return convertU8(from, to, v); }
    static s16 convertS16(Types from, Types to, s16 v) { return convertU16(from, to, v); }
    static s32 convertS32(Types from, Types to, s32 v) { return convertU32(from, to, v); }
    static s64 convertS64(Types from, Types to, s64 v) { return convertU64(from, to, v); }
    static u32 convertF32(Types from, Types to, const void* ptr)
    {
        return convertU32(from, to, *static_cast<const u32*>(ptr));
    }

    static u8 toHostU8(Types from, u8 v) { return convertU8(from, cHostEndian, v); }
    static u16 toHostU16(Types from, u16 v) { return convertU16(from, cHostEndian, v); }
    static u32 toHostU32(Types from, u32 v) { return convertU32(from, cHostEndian, v); }
    static u64 toHostU64(Types from, u64 v) { return convertU64(from, cHostEndian, v); }

    static u8 fromHostU8(Types to, u8 v) { return convertU8(cHostEndian, to, v); }
    static u16 fromHostU16(Types to, u16 v) { return convertU16(cHostEndian, to, v); }
    static u32 fromHostU32(Types to, u32 v) { return convertU32(cHostEndian, to, v); }
    static u64 fromHostU64(Types to, u64 v) { return convertU64(cHostEndian, to, v); }

    static s8 toHostS8(Types from, s8 v) { return toHostU8(from, v); }
    static s16 toHostS16(Types from, s16 v) { return toHostU16(from, v); }
    static s32 toHostS32(Types from, s32 v) { return toHostU32(from, v); }
    static s64 toHostS64(Types from, s64 v) { return toHostU64(from, v); }

    static s8 fromHostS8(Types to, s8 v) { return fromHostU8(to, v); }
    static s16 fromHostS16(Types to, s16 v) { return fromHostU8(to, v); }
    static s32 fromHostS32(Types to, s32 v) { return fromHostU8(to, v); }
    static s64 fromHostS64(Types to, s64 v) { return fromHostU8(to, v); }

    static f32 toHostF32(Types from, const u32* ptr)
    {
        return BitUtil::bitCast<f32>(convertF32(from, cHostEndian, ptr));
    }
    static u32 fromHostF32(Types to, const f32* ptr) { return convertF32(cHostEndian, to, ptr); }

private:
    static const Types cHostEndian;
    static const ConvFuncTable cConvFuncTable;
};
}  // namespace sead

#endif  // SEAD_ENDIAN_H_
