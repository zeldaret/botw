#pragma once

#ifndef AGL_UTILS_PARAMETER_H_
#include "agl/Utils/aglParameter.h"
#endif

namespace agl::utl {

template <u32 N>
inline ParameterCurve<N>::ParameterCurve(const sead::SafeString& name,
                                         const sead::SafeString& label, IParameterObj* param_obj)
    : ParameterBase(name, label, param_obj) {
    reset();
}

template <u32 N>
inline void ParameterCurve<N>::reset() {
    static f32 s_initialize[9] = {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5};
    for (s32 i = 0; i < N; ++i) {
        sead::MemUtil::copy(mCurveData[i].f, s_initialize, sizeof(s_initialize));
        for (s32 j = 9; j < cUnitCurveParamNum; ++j)
            mCurveData[i].f[j] = 1.0;
        mCurves[i].setData(&mCurveData[i], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum,
                           9);
    }
}

template <u32 N>
inline bool ParameterCurve<N>::copy(const ParameterBase& other) {
    if (getParameterType() != other.getParameterType())
        return false;

    if (getName() != other.getName())
        return false;

    copyUnsafe(other);
    return true;
}

template <u32 N>
inline void ParameterCurve<N>::copyUnsafe(const ParameterBase& other) {
    if (getParameterType() != other.getParameterType()) {
        SEAD_ASSERT_MSG(false, "getParameterType() == src.getParameterType()");
        return;
    }

    sead::MemUtil::copy(ptr(), other.ptr(), size());
    for (s32 i = 0; i < N; ++i) {
        auto& curve = mCurves[i];
        auto& curve_other = static_cast<const ParameterCurve<N>&>(other).mCurves[i];
        curve.setCurveType(curve_other.getCurveType());
        curve.mInfo.numUse = curve_other.mInfo.numUse;
    }
}

template <u32 N>
inline ParameterType ParameterCurve<N>::getParameterType() const {
    if constexpr (N == 1)
        return ParameterType::Curve1;
    else if constexpr (N == 2)
        return ParameterType::Curve2;
    else if constexpr (N == 3)
        return ParameterType::Curve3;
    else if constexpr (N == 4)
        return ParameterType::Curve4;
    else
        static_assert(N == 1, "Invalid number of curves");
}

template <u32 N>
inline ParameterBase* ParameterCurve<N>::clone(sead::Heap* heap, IParameterObj* obj) const {
    auto* instance = new (heap) ParameterCurve<N>(getParameterName(), getLabel(), obj);
    sead::MemUtil::copy(instance->mCurveData.data(), mCurveData.data(), sizeof(mCurveData));
    return instance;
}

template <u32 N>
inline void ParameterCurve<N>::postApplyResource_(const void*, size_t size) {
    if (this->size() == size) {
        for (s32 i = 0; i < N; ++i) {
            mCurves[i].setCurveType(sead::hostio::CurveType(mCurveData[i].curveType));
            mCurves[i].mFloats = mCurveData[i].f;
            mCurves[i].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[i].setNumUse(mCurveData[i].numUse);
        }
    } else {
        for (s32 i = 0; i < N; ++i) {
            mCurves[i].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[i].mFloats = mCurveData[i].f;
        }
    }
}

}  // namespace agl::utl
