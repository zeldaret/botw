#pragma once

#include <basis/seadRawPrint.h>
#include <cmath>
#ifndef SEAD_MATH_MATH_CALC_COMMON_H_
#include <math/seadMathCalcCommon.h>
#endif
#include <prim/seadBitUtil.h>
#include <type_traits>

namespace sead
{
template <>
const MathCalcCommon<float>::SinCosSample MathCalcCommon<float>::cSinCosTbl[];

template <>
const MathCalcCommon<float>::AtanSample MathCalcCommon<float>::cAtanTbl[];

template <>
const MathCalcCommon<float>::ExpSample MathCalcCommon<float>::cExpTbl[];

template <>
const MathCalcCommon<float>::LogSample MathCalcCommon<float>::cLogTbl[];

template <typename T>
inline T MathCalcCommon<T>::sign(T value)
{
    return value < 0 ? -1 : 1;
}

template <typename T>
inline T MathCalcCommon<T>::sqrt(T t)
{
    return std::sqrt(t);
}

template <typename T>
inline T MathCalcCommon<T>::rsqrt(T t)
{
    return 1 / std::sqrt(t);
}

template <typename T>
inline T MathCalcCommon<T>::pow(T x, T y)
{
    return std::pow(x, y);
}

template <typename T>
inline T MathCalcCommon<T>::sin(T t)
{
    if constexpr (std::is_same_v<T, float>)
    {
        const auto as_int = BitUtil::bitCast<u32>(t);
        const SinCosSample& sample = cSinCosTbl[as_int >> 18];
        return sample.sin_val + sample.sin_delta * (as_int & 0xFFFFFFu) * 0x1p-24f;
    }
    else
    {
        static_assert(!std::is_same<T, T>(), "Unsupported type");
    }
}

template <typename T>
inline T MathCalcCommon<T>::cos(T t)
{
    if constexpr (std::is_same_v<T, float>)
    {
        const auto as_int = BitUtil::bitCast<u32>(t);
        const SinCosSample& sample = cSinCosTbl[as_int >> 18];
        return sample.cos_val + sample.cos_delta * (as_int & 0xFFFFFFu) * 0x1p-24f;
    }
    else
    {
        static_assert(!std::is_same<T, T>(), "Unsupported type");
    }
}

template <typename T>
inline T MathCalcCommon<T>::tan(T t)
{
    return std::tan(t);
}

template <typename T>
inline T MathCalcCommon<T>::asin(T t)
{
    if constexpr (std::is_floating_point<T>())
        SEAD_ASSERT_MSG(-1.0 <= t && t <= 1.0, "t(%f) is not in [-1, 1].", t);
    return std::asin(t);
}

template <typename T>
inline T MathCalcCommon<T>::acos(T t)
{
    if constexpr (std::is_floating_point<T>())
        SEAD_ASSERT_MSG(-1.0 <= t && t <= 1.0, "t(%f) is not in [-1, 1].", t);
    return std::acos(t);
}

template <typename T>
inline T MathCalcCommon<T>::atan(T t)
{
    return std::atan(t);
}

template <typename T>
inline T MathCalcCommon<T>::atan2(T y, T x)
{
    return std::atan2(y, x);
}

template <>
inline f32 MathCalcCommon<f32>::sinIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    u32 rest = idx & 0xffffff;

    return cSinCosTbl[index].sin_val + cSinCosTbl[index].sin_delta * rest / 0x1000000;
}

template <>
inline f32 MathCalcCommon<f32>::cosIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    u32 rest = idx & 0xffffff;

    return cSinCosTbl[index].cos_val + cSinCosTbl[index].cos_delta * rest / 0x1000000;
}

template <>
inline f32 MathCalcCommon<f32>::tanIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    f32 rest = static_cast<f32>(idx & 0xffffff) / 0x1000000;
    const SinCosSample& sample = cSinCosTbl[index];

    return (sample.sin_val + sample.sin_delta * rest) / (sample.cos_val + sample.cos_delta * rest);
}

template <>
inline u32 MathCalcCommon<f32>::asinIdx(f32 s)
{
    SEAD_ASSERT_MSG(s <= 1 && s >= -1, "s(%f) is not in [-1, 1].", s);

    const f32 rsqrt_2 = 0.7071067690849304f;  // rsqrt(2)

    if (s >= 0)
    {
        if (s > rsqrt_2)
            return 0x40000000 - atanIdx_(sqrt(1 - s * s) / s);

        else
            return atanIdx_(s / sqrt(1 - s * s));
    }
    else
    {
        if (s < -rsqrt_2)
            return 0xC0000000 + atanIdx_(-sqrt(1 - s * s) / s);

        else
            return -atanIdx_(-s / sqrt(1 - s * s));
    }
}

template <>
inline u32 MathCalcCommon<f32>::acosIdx(f32 c)
{
    SEAD_ASSERT_MSG(c <= 1 && c >= -1, "c(%f) is not in [-1, 1].", c);

    const f32 rsqrt_2 = 0.7071067690849304f;  // rsqrt(2)

    if (c >= 0)
    {
        if (c > rsqrt_2)
            return atanIdx_(sqrt(1 - c * c) / c);

        else
            return 0x40000000 - atanIdx_(c / sqrt(1 - c * c));
    }
    else
    {
        if (c < -rsqrt_2)
            return 0x80000000 - atanIdx_(-sqrt(1 - c * c) / c);

        else
            return 0x40000000 + atanIdx_(-c / sqrt(1 - c * c));
    }
}

template <>
inline u32 MathCalcCommon<f32>::atanIdx(f32 t)
{
    if (t >= 0)
    {
        if (t > 1)
            return 0x40000000 - atanIdx_(1 / t);

        else
            return atanIdx_(t);
    }
    else
    {
        if (t < -1)
            return 0xC0000000 + atanIdx_(-1 / t);

        else
            return -atanIdx_(-t);
    }
}

template <>
inline u32 MathCalcCommon<f32>::atan2Idx(f32 y, f32 x)
{
    if (x == 0 && y == 0)
        return 0;

    if (x >= 0)
    {
        if (y >= 0)
        {
            if (x >= y)
                return atanIdx_(y / x);

            else
                return 0x40000000 - atanIdx_(x / y);
        }
        else
        {
            if (x >= -y)
                return -atanIdx_(-y / x);

            else
                return 0xC0000000 + atanIdx_(x / -y);
        }
    }
    else
    {
        if (y >= 0)
        {
            if (-x >= y)
                return 0x80000000 - atanIdx_(y / -x);

            else
                return 0x40000000 + atanIdx_(-x / y);
        }
        else
        {
            if (x <= y)
                return 0x80000000 + atanIdx_(y / x);

            else
                return 0xC0000000 - atanIdx_(x / y);
        }
    }
}

template <>
inline void MathCalcCommon<f32>::sinCosIdx(f32* pSin, f32* pCos, u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    f32 rest = static_cast<f32>(idx & 0xffffff) / 0x1000000;
    const SinCosSample& sample = cSinCosTbl[index];

    /*if (pSin != NULL)*/ *pSin = sample.sin_val + sample.sin_delta * rest;
    /*if (pCos != NULL)*/ *pCos = sample.cos_val + sample.cos_delta * rest;
}

template <typename T>
inline T MathCalcCommon<T>::exp(T t)
{
    return std::exp(t);
}

template <typename T>
inline T MathCalcCommon<T>::log(T t)
{
    return std::log(t);
}

template <typename T>
inline T MathCalcCommon<T>::log2(T n)
{
    return std::log2(n);
}

template <typename T>
inline T MathCalcCommon<T>::log10(T t)
{
    return std::log10(t);
}

template <typename T>
inline T MathCalcCommon<T>::minNumber()
{
    return std::numeric_limits<T>::min();
}

template <typename T>
inline T MathCalcCommon<T>::maxNumber()
{
    return std::numeric_limits<T>::max();
}

template <>
inline float MathCalcCommon<float>::minNumber()
{
    return -std::numeric_limits<float>::max();
}

template <>
inline float MathCalcCommon<float>::maxNumber()
{
    return std::numeric_limits<float>::max();
}

template <>
inline double MathCalcCommon<double>::minNumber()
{
    return -std::numeric_limits<double>::max();
}

template <>
inline double MathCalcCommon<double>::maxNumber()
{
    return std::numeric_limits<double>::max();
}

template <>
inline long double MathCalcCommon<long double>::minNumber()
{
    return -std::numeric_limits<long double>::max();
}

template <>
inline long double MathCalcCommon<long double>::maxNumber()
{
    return std::numeric_limits<long double>::max();
}

template <typename T>
inline T MathCalcCommon<T>::infinity()
{
    return std::numeric_limits<T>::infinity();
}

template <>
inline f32 MathCalcCommon<f32>::nan()
{
    return BitUtil::bitCast<f32>(0x7FFFFFFF);
}

template <>
inline f64 MathCalcCommon<f64>::nan()
{
    return BitUtil::bitCast<f64>(0x7FFFFFFFFFFFFFFF);
}

template <>
inline s32 MathCalcCommon<s32>::abs(s32 x)
{
    return (x ^ x >> 31) - (x >> 31);
}

template <>
inline u32 MathCalcCommon<u32>::abs(u32 x)
{
    return x;
}

#ifdef cafe

template <>
inline f32 MathCalcCommon<f32>::abs(f32 x)
{
    return std::abs(x);
}

template <>
inline f64 MathCalcCommon<f64>::abs(f64 x)
{
    return std::abs(x);
}

#endif  // cafe

template <typename T>
inline T MathCalcCommon<T>::max(T a, T b)
{
    return a < b ? b : a;
}

template <typename T>
inline T MathCalcCommon<T>::min(T a, T b)
{
    return a < b ? a : b;
}

template <typename T>
inline T MathCalcCommon<T>::max3(T a, T b, T c)
{
    return max(max(a, b), c);
}

template <typename T>
inline T MathCalcCommon<T>::min3(T a, T b, T c)
{
    return min(min(a, b), c);
}

template <typename T>
inline T MathCalcCommon<T>::deg2rad(T deg)
{
    return deg * (numbers::pi_v<T> / static_cast<T>(180));
}

template <typename T>
inline T MathCalcCommon<T>::rad2deg(T rad)
{
    return rad * (static_cast<T>(180) / numbers::pi_v<T>);
}

template <typename T>
inline u32 MathCalcCommon<T>::deg2idx(T a)
{
    return static_cast<u32>(a * (cHalfRoundIdx / static_cast<T>(180)));
}

template <typename T>
inline u32 MathCalcCommon<T>::rad2idx(T a)
{
    return static_cast<u32>(a * (cHalfRoundIdx / pi()));
}

template <typename T>
inline T MathCalcCommon<T>::idx2deg(u32 a)
{
    return static_cast<T>(a * (static_cast<T>(180) / cHalfRoundIdx));
}

template <typename T>
inline T MathCalcCommon<T>::idx2rad(u32 a)
{
    return static_cast<T>(a * (pi() / cHalfRoundIdx));
}

template <typename T>
inline s32 MathCalcCommon<T>::roundOff(T val)
{
    return std::floor(val + 0.5f);
}

template <>
inline s32 MathCalcCommon<s32>::roundOff(s32 val)
{
    return val;
}

template <typename T>
inline s32 MathCalcCommon<T>::floor(T val)
{
    return std::floor(val);
}

template <>
inline s32 MathCalcCommon<s32>::floor(s32 val)
{
    return val;
}

template <typename T>
inline s32 MathCalcCommon<T>::ceil(T val)
{
    return std::ceil(val);
}

template <>
inline s32 MathCalcCommon<s32>::ceil(s32 val)
{
    return val;
}

template <typename T>
inline T MathCalcCommon<T>::roundUp(T x, s32 multNumber)
{
    SEAD_ASSERT(multNumber > 0);
    return (x + multNumber - 1) / multNumber * multNumber;
}

template <>
inline s32 MathCalcCommon<u32>::roundUpPow2(u32 val, s32 base)
{
    SEAD_ASSERT_MSG((u32(base - 1) & u32(base)) == 0, "illegal param[val:%d, base:%d]", val, base);
    return (val + base - 1) & (u32)-base;
}

template <>
inline s32 MathCalcCommon<s32>::roundUpPow2(s32 val, s32 base)
{
    SEAD_ASSERT_MSG(val >= 0 && (u32(base - 1) & u32(base)) == 0, "illegal param[val:%d, base:%d]",
                    val, base);
    return (val + base - 1) & (u32)-base;
}

template <typename T>
inline T MathCalcCommon<T>::clampMax(T val, T max_)
{
    return min(val, max_);
}

template <typename T>
inline T MathCalcCommon<T>::clampMin(T val, T min_)
{
    return max(val, min_);
}

template <typename T>
inline T MathCalcCommon<T>::clamp(T value, T low, T high)
{
    if (value < low)
        value = low;
    else if (value > high)
        value = high;
    return value;
}

template <typename T>
inline bool MathCalcCommon<T>::chase(T* value, T target, T step)
{
    const T current = *value;

    if (current < target)
    {
        const T new_value = current + step;
        if (target <= new_value || new_value < current)
        {
            *value = target;
            return true;
        }
        *value = new_value;
        return false;
    }

    if (current > target)
    {
        const T new_value = current - step;
        if (target >= new_value || current < new_value)
        {
            *value = target;
            return true;
        }
        *value = new_value;
        return false;
    }

    return true;
}

template <typename T, typename T2>
inline T lerp(T a, T b, T2 t)
{
    return a + (b - a) * t;
}

}  // namespace sead
