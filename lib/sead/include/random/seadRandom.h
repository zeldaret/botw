#pragma once

#include "basis/seadRawPrint.h"
#include "basis/seadTypes.h"
#include "prim/seadBitUtil.h"

namespace sead
{
/// A fast non-cryptographically secure pseudorandom number generator based on Xorshift128.
class Random
{
public:
    Random() { init(); }
    Random(u32 seed) { init(seed); }
    /// @warning Parameters have to be chosen carefully to get a long period. Using this is not
    /// recommended.
    Random(u32 seed_x, u32 seed_y, u32 seed_z, u32 seed_w) { init(seed_x, seed_y, seed_z, seed_w); }

    /// Reset and seed the engine with the current system tick count.
    void init();
    /// Reset and seed the engine with the specified value.
    void init(u32 seed);
    /// @warning Parameters have to be chosen carefully to get a long period. Using this is not
    /// recommended.
    void init(u32 seed_x, u32 seed_y, u32 seed_z, u32 seed_w);

    /// Generate a random u32.
    u32 getU32();
    /// Generate a random u64.
    u64 getU64();
    /// Generate a random u32 in [0 .. max).
    u32 getU32(u32 max);
    /// Generate a random s32 in [a .. b).
    /// Note that this does not provide a uniform distribution.
    s32 getS32Range(s32 a, s32 b);
    /// Generate a random s64 in [a .. b).
    /// Note that this does not provide a uniform distribution.
    s64 getS64Range(s64 a, s64 b);
    /// Generate a random f32 in [0, 1).
    f32 getF32();
    /// Generate a random f32 in [a, b).
    f32 getF32Range(f32 a, f32 b);
    /// Generate a random f64 in [0, 1).
    f64 getF64();
    /// Generate a random f64 in [a, b).
    f64 getF64Range(f64 a, f64 b);
    /// Generate a random boolean.
    bool getBool();

    void getContext(u32* x, u32* y, u32* z, u32* w) const;

private:
    u32 mX;
    u32 mY;
    u32 mZ;
    u32 mW;
};

inline u32 Random::getU32(u32 max)
{
    return getU32() * u64(max) >> 32u;
}

inline s32 Random::getS32Range(s32 a, s32 b)
{
    SEAD_ASSERT_MSG(a <= b, "b[%d] >= a[%d]", a, b);
    return getU32(b - a) + static_cast<u32>(a);
}

// UNCHECKED
inline s64 Random::getS64Range(s64 a, s64 b)
{
    SEAD_ASSERT_MSG(a <= b, "b[%ld] >= a[%ld]", a, b);
    return (getU32() * u64(b - a) >> 32u) + a;
}

inline f32 Random::getF32()
{
    return BitUtil::bitCast<f32>((getU32() >> 9u) | 0x3F800000u) - 1.0f;
}

inline f32 Random::getF32Range(f32 a, f32 b)
{
    SEAD_ASSERT_MSG(a <= b, "b[%f] >= a[%f]", a, b);
    return a + (b - a) * getF32();
}

// UNCHECKED
inline f64 Random::getF64()
{
    return BitUtil::bitCast<f64>((getU64() >> 12u) | 0x3FF0'0000'0000'0000lu) - 1.0;
}

// UNCHECKED
inline f64 Random::getF64Range(f64 a, f64 b)
{
    SEAD_ASSERT_MSG(a <= b, "b[%f] >= a[%f]", a, b);
    return a + (b - a) * getF64();
}

// UNCHECKED
inline bool Random::getBool()
{
    return getU32() & 0x80000000u;
}

}  // namespace sead
