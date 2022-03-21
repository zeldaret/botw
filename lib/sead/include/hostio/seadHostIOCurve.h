#pragma once

#include <array>
#include "basis/seadRawPrint.h"
#include "basis/seadTypes.h"
#include "math/seadVector.h"

namespace sead::hostio
{
class ICurve
{
public:
    virtual f32 interpolateToF32(f32 t) = 0;
    virtual Vector2f interpolateToVec2f(f32 t) = 0;
};

enum class CurveType
{
    Linear = 0,
    Hermit = 1,
    Step = 2,
    Sin = 3,
    Cos = 4,
    SinPow2 = 5,
    Linear2D = 6,
    Hermit2D = 7,
    Step2D = 8,
    NonUniformSpline = 9,
    Hermit2DSmooth = 10,
};
inline constexpr int cNumCurveType = 11;

struct CurveDataInfo
{
    u8 curveType;
    u8 _1;
    u8 numFloats;
    u8 numUse;
};

struct CurveData
{
    u32 numUse;
    u32 curveType;
    f32 f[30];
};
static_assert(sizeof(CurveData) == 0x80);

template <typename T>
class Curve : public ICurve
{
public:
    Curve()
    {
        mInfo.curveType = 0;
        mInfo.numUse = 0;
        mInfo._1 = 4;
        mInfo.numFloats = 0;
        mFloats = nullptr;
    }

    f32 interpolateToF32(f32 t) override;
    Vector2f interpolateToVec2f(f32 t) override;

    CurveType getCurveType() const { return CurveType(mInfo.curveType); }

    void setData(CurveData* data, CurveType type, u32 num_floats, u32 num_use)
    {
        data->curveType = u8(type);
        data->numUse = num_use;
        setCurveType(type);
        setFloats(data, num_floats);
        setNumUse(num_use);
    }

    void setFloats(CurveData* data, u32 num_floats)
    {
        mInfo.numFloats = num_floats;
        mFloats = data->f;
    }

    void setCurveType(CurveType type)
    {
        SEAD_ASSERT(mInfo.curveType < cNumCurveType);
        mInfo.curveType = u8(type);
    }

    void setNumUse(u32 numUse)
    {
        SEAD_ASSERT(numUse <= 0xff);
        mInfo.numUse = numUse;
    }

    f32* mFloats;
    CurveDataInfo mInfo;
};

template <typename T>
T curveLinear_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveHermit_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveStep_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveSin_(f32 t_, const CurveDataInfo* info, const T* f);
template <typename T>
T curveCos_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveSinPow2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveLinear2D_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveHermit2D_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveStep2D_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveNonuniformSpline_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
T curveHermit2DSmooth_(f32 t, const CurveDataInfo* info, const T* f);

template <typename T>
using CurveFunctionTable = std::array<decltype(curveLinear_<T>)*, cNumCurveType>;

extern CurveFunctionTable<f32> sCurveFunctionTbl_f32;
extern CurveFunctionTable<f64> sCurveFunctionTbl_f64;

template <typename T>
Vector2<T> curveLinearVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveHermitVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveStepVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveSinVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveCosVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveSinPow2Vec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveLinear2DVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveHermit2DVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveStep2DVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveNonuniformSplineVec2_(f32 t, const CurveDataInfo* info, const T* f);
template <typename T>
Vector2<T> curveHermit2DSmoothVec2_(f32 t, const CurveDataInfo* info, const T* f);

template <typename T>
using CurveFunctionTableVec2 = std::array<decltype(curveLinearVec2_<T>)*, cNumCurveType>;

extern CurveFunctionTableVec2<f32> sCurveFunctionTbl_Vec2f;
extern CurveFunctionTableVec2<f64> sCurveFunctionTbl_Vec2d;

template <>
inline f32 Curve<f32>::interpolateToF32(f32 t)
{
    return sCurveFunctionTbl_f32[u8(mInfo.curveType)](t, &mInfo, mFloats);
}

template <>
inline Vector2f Curve<f32>::interpolateToVec2f(f32 t)
{
    return sCurveFunctionTbl_Vec2f[u8(mInfo.curveType)](t, &mInfo, mFloats);
}
}  // namespace sead::hostio
