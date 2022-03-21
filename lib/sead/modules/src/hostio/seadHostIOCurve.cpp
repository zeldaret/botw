#include "hostio/seadHostIOCurve.h"
#include <cmath>
#include "math/seadMathCalcCommon.h"
#include "math/seadMathNumbers.h"

namespace sead::hostio
{
template <typename T>
constexpr CurveFunctionTable<T> makeTable_()
{
    return {{
        curveLinear_,
        curveHermit_,
        curveStep_,
        curveSin_,
        curveCos_,
        curveSinPow2_,
        curveLinear2D_,
        curveHermit2D_,
        curveStep2D_,
        curveNonuniformSpline_,
        curveHermit2DSmooth_,
    }};
}

template <typename T>
constexpr CurveFunctionTableVec2<T> makeTableVec2_()
{
    return {{
        curveLinearVec2_,
        curveHermitVec2_,
        curveStepVec2_,
        curveSinVec2_,
        curveCosVec2_,
        curveSinPow2Vec2_,
        curveLinear2DVec2_,
        curveHermit2DVec2_,
        curveStep2DVec2_,
        curveNonuniformSplineVec2_,
        curveHermit2DSmoothVec2_,
    }};
}

CurveFunctionTable<f32> sCurveFunctionTbl_f32 = makeTable_<f32>();
CurveFunctionTable<f64> sCurveFunctionTbl_f64 = makeTable_<f64>();

CurveFunctionTableVec2<f32> sCurveFunctionTbl_Vec2f = makeTableVec2_<f32>();
CurveFunctionTableVec2<f64> sCurveFunctionTbl_Vec2d = makeTableVec2_<f64>();

template <typename T>
static T fracPart(T x)
{
    return x - T(int(x));
}

template <typename T>
T curveLinear_(f32 t, const CurveDataInfo* info, const T* f)
{
    if (t < 0)
        return f[0];

    const auto n = info->numUse - 1;
    const int i = n * t;
    if (i >= n)
        return f[n];
    return f[i] + (fracPart(n * t) * (f[i + 1] - f[i]));
}

// NON_MATCHING: instruction ordering
template <typename T>
T curveHermit_(f32 t, const CurveDataInfo* info, const T* f)
{
    if (info->numUse % 2 == 1)
        return 0;
    if (t < 0)
        return f[0];

    const auto n = (info->numUse / 2) - 1;
    const int i = n * t;
    const int j = 2 * i;
    if (i >= n)
        return f[j];

    const auto x = fracPart(n * t);
    const auto coeff = &f[j];

    return ((2 * x * x * x) - (3 * x * x) + 1) * coeff[0]  // (2t^3 - 3t^2 + 1)p0
           + ((-2 * x * x * x) + (3 * x * x)) * coeff[2]   // (-2t^3 + 2t^2)p1
           + ((x * x * x) - (x * x)) * coeff[3]            // (t^3 - t^2)m1
           + ((x * x * x) - (2 * x * x) + x) * f[j | 1]    // (t^3 - 2t^2 + t)m0
        ;
}

template <typename T>
T curveStep_(f32 t, const CurveDataInfo* info, const T* f)
{
    const f32 x = Mathf::clamp(t, 0.0, 1.0);
    return f[int(x * (info->numUse - 1))];
}

template <typename T>
T curveSin_(f32 t_, const CurveDataInfo*, const T* f)
{
    const T t = t_;
    return std::sin(f[0] * t * (2 * numbers::pi_v<T>)) * f[1];
}

template <typename T>
T curveCos_(f32 t_, const CurveDataInfo*, const T* f)
{
    const T t = t_;
    return std::cos(f[0] * T(t) * (2 * numbers::pi_v<T>)) * f[1];
}

template <typename T>
T curveSinPow2_(f32 t_, const CurveDataInfo*, const T* f)
{
    const T t = t_;
    const auto y = std::sin(f[0] * t * (2 * numbers::pi_v<T>));
    return y * y * f[1];
}

// NON_MATCHING: instruction reordering (which results in localized regalloc differences)
template <typename T>
T curveLinear2D_(f32 t_, const CurveDataInfo* info, const T* f)
{
    const T t = t_;
    if (f[0] >= t)
        return f[1];

    const auto n = info->numUse / 2;
    if (f[2 * (n - 1)] <= t)
        return f[2 * (n - 1) + 1];

    for (s32 i = 0; i < n; ++i)
    {
        const auto j = 2 * i;
        if (f[j + 2] > t)
            return f[j + 1] + ((t - f[j]) / (f[j + 2] - f[j])) * (f[j + 3] - f[j + 1]);
    }
    return 0;
}

// NON_MATCHING: same as curveHermit_<T>
template <typename T>
T curveHermit2D_(f32 t_, const CurveDataInfo* info, const T* f)
{
    const T t = t_;
    const s8 n = info->numUse / 3;
    if (f[0] >= t)
        return f[1];

    if (f[3 * (n - 1)] <= t)
        return f[3 * (n - 1) + 1];

    for (s32 i = 0; i < n; ++i)
    {
        const auto j = 3 * i;
        if (f[j + 3] > t)
        {
            const auto x = (t - f[j]) / (f[j + 3] - f[j]);
            return ((2 * x * x * x) - (3 * x * x) + 1) * f[j + 1]  // (2t^3 - 3t^2 + 1)p0
                   + ((-2 * x * x * x) + (3 * x * x)) * f[j + 4]   // (-2t^3 + 2t^2)p1
                   + ((x * x * x) - (x * x)) * f[j + 5]            // (t^3 - t^2)m1
                   + ((x * x * x) - (2 * x * x) + x) * f[j + 2]    // (t^3 - 2t^2 + t)m0
                ;
        }
    }

    return 0;
}

template <typename T>
T curveStep2D_(f32 t_, const CurveDataInfo* info, const T* f)
{
    const T t = t_;
    const s8 n = info->numUse / 2;
    if (t <= f[0])
        return f[1];

    if (t >= f[2 * (n - 1)])
        return f[2 * (n - 1) + 1];

    for (s32 i = 0; i < n; ++i)
    {
        if (t < f[2 * i + 2])
            return f[2 * i + 1];
    }
    return 0;
}

template <typename T>
T curveNonuniformSpline_(f32, const CurveDataInfo*, const T*)
{
    SEAD_ASSERT_MSG(false, "You must call ICurve::interpolateToVec2 at this curve type.");
    return 0;
}

template <typename T>
Vector2<T> curveLinearVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveLinear_(t, info, f)};
}

template <typename T>
Vector2<T> curveHermitVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveHermit_(t, info, f)};
}

template <typename T>
Vector2<T> curveStepVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveStep_(t, info, f)};
}

template <typename T>
Vector2<T> curveSinVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveSin_(t, info, f)};
}

template <typename T>
Vector2<T> curveCosVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveCos_(t, info, f)};
}

template <typename T>
Vector2<T> curveSinPow2Vec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveSinPow2_(t, info, f)};
}

template <typename T>
Vector2<T> curveLinear2DVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveLinear2D_(t, info, f)};
}

template <typename T>
Vector2<T> curveHermit2DVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveHermit2D_(t, info, f)};
}

template <typename T>
Vector2<T> curveStep2DVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveStep2D_(t, info, f)};
}

// curveNonuniformSplineVec2_ has an assertion

template <typename T>
Vector2<T> curveHermit2DSmoothVec2_(f32 t, const CurveDataInfo* info, const T* f)
{
    return {t, curveHermit2DSmooth_(t, info, f)};
}
}  // namespace sead::hostio
