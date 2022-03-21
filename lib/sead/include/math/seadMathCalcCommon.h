#pragma once

#include <basis/seadTypes.h>
#include <cmath>
#include <limits>
#include <math/seadMathNumbers.h>
#include <type_traits>

namespace sead
{
template <typename T>
class MathCalcCommon
{
public:
    static const u32 cQuarterRoundIdx = 0x40000000;  //  90 degrees, PI/2 radians
    static const u32 cHalfRoundIdx = 0x80000000;     // 180 degrees, PI   radians

    struct SinCosSample
    {
        T sin_val;
        T sin_delta;
        T cos_val;
        T cos_delta;
    };

    struct AtanSample
    {
        u32 atan_val;
        T atan_delta;
    };

    struct ExpSample
    {
        T exp_val;
        T exp_delta;
    };

    struct LogSample
    {
        T log_val;
        T log_delta;
    };

    static T piHalf() { return numbers::pi_v<T> / static_cast<T>(2); }
    static T pi() { return numbers::pi_v<T>; }
    static T pi2() { return numbers::pi_v<T> * static_cast<T>(2); }
    static T zero() { return static_cast<T>(0); }
    static T one() { return static_cast<T>(1); }
    static T ln2() { return numbers::ln2_v<T>; }
    static T ln2Inv() { return numbers::log2e_v<T>; }

    static T neg(T t);
    static T inv(T t);

    /// Returns -1 for strictly negative values and 1 otherwise.
    static T sign(T value);

    static T fitSign(T value, T sign_value) { return abs(value) * sign(sign_value); }

    static T square(T t) { return t * t; }

    static T sqrt(T t);
    static T rsqrt(T t);

    static T pow(T x, T y);
    static T powTable(T, T);

    static T sin(T t);
    static T cos(T t);
    static T tan(T t);

    static T asin(T s);
    static T acos(T c);
    static T atan(T t);
    static T atan2(T y, T x);

    static T sinIdx(u32 idx);
    static T cosIdx(u32 idx);
    static T tanIdx(u32 idx);

    static u32 asinIdx(T s);
    static u32 acosIdx(T c);
    static u32 atanIdx(T t);
    static u32 atan2Idx(T y, T x);

    static void sinCosIdx(T* p_sin, T* p_cos, u32 idx);

    static T exp(T t);
    static T log(T t);
    static T log2(T n);
    static T log10(T t);

    static T expTable(T x);
    static T logTable(T x);

    static T minNumber();
    static T maxNumber();
    static T infinity();
    static T nan();
    static T epsilon() { return std::numeric_limits<T>::epsilon(); }

    static bool equalsEpsilon(T lhs, T rhs, T eps = epsilon())
    {
        const T diff = lhs - rhs;
        return -eps <= diff && diff <= eps;
    }

    static T abs(T x) { return x > 0 ? x : -x; }

    static T max(T a, T b);
    static T min(T a, T b);
    static T max3(T a, T b, T c);
    static T min3(T a, T b, T c);

    static T deg2rad(T deg);
    static T rad2deg(T rad);

    static u32 deg2idx(T a);
    static u32 rad2idx(T a);
    static T idx2deg(u32 a);
    static T idx2rad(u32 a);

    static T roundAngle(T);
    static T angleDist(T, T);
    static T random();
    static T getRand(T);
    static T getRandRange(T, T);
    static T getRandSign();
    static s32 roundOff(T);
    static s32 floor(T);
    static s32 ceil(T);
    static T roundUp(T x, s32 multNumber);
    static s32 roundUpPow2(T x, s32 y);
    static s32 roundDownN(T val, s32 multNumber);
    static s32 roundDownPow2(T x, s32 y);
    static T clampMax(T val, T max_);
    static T clampMin(T val, T min_);
    static T clamp2(T min_, T val, T max_);  // is this the same function?
    static T clamp(T value, T low, T high);
    static T gcd(T x, T y);
    static T lcm(T x, T y);
    static bool isZero(T, T);
    static bool isNan(T);
    static bool isPow2(T);
    static bool isMultiplePow2(T, T);
    static bool isInfinity(T);
    static bool isIntersect1d(T, T, T, T);

    /// Adds or subtracts `step` from `value` towards `target`.
    /// Returns whether the new value is equal to the target.
    static bool chase(T* value, T target, T step);
    static bool chaseAngle(T*, T, T);
    static bool chaseAngleIdx(u32*, u32, s64);

    static T lerp(T a, T b, f32 ratio);

protected:
    static u32 atanIdx_(T t);
    static T expLn2_(T x);
    static T log1_2_(T x);
    static void assertGreaterThanOrEqualToZero_(T);

public:
    /// Note: this is only defined for T = float at the moment.
    static const SinCosSample cSinCosTbl[256 + 1];
    static const AtanSample cAtanTbl[128 + 1];
    static const ExpSample cExpTbl[32 + 1];
    static const LogSample cLogTbl[256 + 1];
};

typedef MathCalcCommon<s32> Mathi;
typedef MathCalcCommon<u32> Mathu;
typedef MathCalcCommon<f32> Mathf;
typedef MathCalcCommon<size_t> MathSizeT;

template <>
u32 MathCalcCommon<f32>::atanIdx_(f32 t);

template <typename T>
constexpr T log2(T n)
{
    static_assert(std::is_integral<T>(), "T must be an integral type");
    return n <= 1 ? 0 : 1 + log2(n >> 1);
}

}  // namespace sead

#define SEAD_MATH_MATH_CALC_COMMON_H_
#include <math/seadMathCalcCommon.hpp>
#undef SEAD_MATH_MATH_CALC_COMMON_H_
