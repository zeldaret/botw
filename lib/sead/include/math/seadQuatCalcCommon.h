#pragma once

#include <math/seadMathPolicies.h>

namespace sead
{
template <typename T>
class QuatCalcCommon
{
public:
    using Base = typename Policies<T>::QuatBase;
    using Vec3 = typename Policies<T>::Vec3Base;

    static T length(const Base& v);
    static T normalize(Base& v);
    static T dot(const Base& u, const Base& v);
    static void setMul(Base& out, const Base& u, const Base& v);
    static void slerpTo(Base& out, const Base& q1, const Base& q2, f32 t);
    static void makeUnit(Base& q);
    static bool makeVectorRotation(Base& q, const Vec3& from, const Vec3& to);
    static void set(Base& q, T w, T x, T y, T z);
    static void setRPY(Base& q, T roll, T pitch, T yaw);
    static void calcRPY(Vec3& rpy, const Base& q);
};

}  // namespace sead

#define SEAD_MATH_QUAT_CALC_COMMON_H_
#include "math/seadQuatCalcCommon.hpp"
#undef SEAD_MATH_QUAT_CALC_COMMON_H_
