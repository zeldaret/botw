#pragma once

#ifdef cafe
#include <cafe.h>
#endif  // cafe

#include <math/seadMathCalcCommon.h>
#ifndef SEAD_MATH_VECTOR_CALC_COMMON_H_
#include <math/seadVectorCalcCommon.h>
#endif

namespace sead
{
template <typename T>
inline void Vector2CalcCommon<T>::add(Base& o, const Base& a, const Base& b)
{
    o.x = a.x + b.x;
    o.y = a.y + b.y;
}

template <typename T>
inline void Vector2CalcCommon<T>::sub(Base& o, const Base& a, const Base& b)
{
    o.x = a.x - b.x;
    o.y = a.y - b.y;
}

template <typename T>
inline void Vector2CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
}

template <typename T>
inline void Vector2CalcCommon<T>::set(Base& v, T x, T y)
{
    v.x = x;
    v.y = y;
}

template <typename T>
inline void Vector3CalcCommon<T>::add(Base& o, const Base& a, const Base& b)
{
    o.x = a.x + b.x;
    o.y = a.y + b.y;
    o.z = a.z + b.z;
}

#ifdef cafe

template <>
inline void Vector3CalcCommon<f32>::add(Base& o, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    ASM_VECAdd((const Vec*)&a, (const Vec*)&b, (Vec*)&o);
}

#endif  // cafe

template <typename T>
inline void Vector3CalcCommon<T>::sub(Base& o, const Base& a, const Base& b)
{
    o.x = a.x - b.x;
    o.y = a.y - b.y;
    o.z = a.z - b.z;
}

#ifdef cafe

template <>
inline void Vector3CalcCommon<f32>::sub(Base& o, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    ASM_VECSubtract((const Vec*)&a, (const Vec*)&b, (Vec*)&o);
}

#endif  // cafe

template <typename T>
inline void Vector3CalcCommon<T>::mul(Base& o, const Mtx33& m, const Base& a)
{
    const Base tmp = a;
    o.x = m.m[0][0] * tmp.x + m.m[0][1] * tmp.y + m.m[0][2] * tmp.z;
    o.y = m.m[1][0] * tmp.x + m.m[1][1] * tmp.y + m.m[1][2] * tmp.z;
    o.z = m.m[2][0] * tmp.x + m.m[2][1] * tmp.y + m.m[2][2] * tmp.z;
}

template <typename T>
inline void Vector3CalcCommon<T>::mul(Base& o, const Mtx34& m, const Base& a)
{
    const Base tmp = a;
    o.x = m.m[0][0] * tmp.x + m.m[0][1] * tmp.y + m.m[0][2] * tmp.z + m.m[0][3];
    o.y = m.m[1][0] * tmp.x + m.m[1][1] * tmp.y + m.m[1][2] * tmp.z + m.m[1][3];
    o.z = m.m[2][0] * tmp.x + m.m[2][1] * tmp.y + m.m[2][2] * tmp.z + m.m[2][3];
}

template <typename T>
inline void Vector3CalcCommon<T>::cross(Base& o, const Base& a, const Base& b)
{
    Vector3CalcCommon<T>::set(o, (a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z),
                              (a.x * b.y) - (a.y * b.x));
}

#ifdef cafe

template <>
inline void Vector3CalcCommon<f32>::cross(Base& o, const Base& a, const Base& b)
{
    ASM_VECCrossProduct((const Vec*)&a, (const Vec*)&b, (Vec*)&o);
}

#endif  // cafe

template <typename T>
inline T Vector3CalcCommon<T>::dot(const Base& a, const Base& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

#ifdef cafe

template <>
inline f32 Vector3CalcCommon<f32>::dot(const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    return ASM_VECDotProduct((const Vec*)&a, (const Vec*)&b);
}

#endif  // cafe

template <typename T>
inline T Vector3CalcCommon<T>::squaredLength(const Base& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template <typename T>
inline T Vector3CalcCommon<T>::length(const Base& v)
{
    return MathCalcCommon<T>::sqrt(squaredLength(v));
}

#ifdef cafe

template <>
inline f32 Vector3CalcCommon<f32>::length(const Base& v)
{
    return ASM_VECMag((const Vec*)&v);
}

#endif  // cafe

template <typename T>
inline bool Vector3CalcCommon<T>::equals(const Base& lhs, const Base& rhs, T epsilon)
{
    return MathCalcCommon<T>::equalsEpsilon(lhs.x, rhs.x, epsilon) &&
           MathCalcCommon<T>::equalsEpsilon(lhs.y, rhs.y, epsilon) &&
           MathCalcCommon<T>::equalsEpsilon(lhs.z, rhs.z, epsilon);
}

template <typename T>
inline void Vector3CalcCommon<T>::multScalar(Base& o, const Base& v, T t)
{
    o.x = v.x * t;
    o.y = v.y * t;
    o.z = v.z * t;
}

#ifdef cafe

template <>
inline void Vector3CalcCommon<f32>::multScalar(Base& o, const Base& v, f32 t)
{
    // TODO: Implement using intrinsics
    ASM_VECScale((const Vec*)&v, (Vec*)&o, t);
}

#endif  // cafe

template <typename T>
inline void Vector3CalcCommon<T>::multScalarAdd(Base& o, T t, const Base& a, const Base& b)
{
    o.x = a.x * t + b.x;
    o.y = a.y * t + b.y;
    o.z = a.z * t + b.z;
}

#ifdef cafe

template <>
inline void Vector3CalcCommon<f32>::multScalarAdd(Base& o, f32 t, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    ASM_VECScale((const Vec*)&a, (Vec*)&o, t);
    ASM_VECAdd((const Vec*)&o, (const Vec*)&b, (Vec*)&o);
}

#endif  // cafe

template <typename T>
T Vector3CalcCommon<T>::normalize(Base& v)
{
    const T len = length(v);
    if (len > 0)
    {
        const T inv_len = 1 / len;
        v.x *= inv_len;
        v.y *= inv_len;
        v.z *= inv_len;
    }

    return len;
}

template <typename T>
inline void Vector3CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
    o.z = v.z;
}

template <typename T>
inline void Vector3CalcCommon<T>::set(Base& v, T x, T y, T z)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

template <typename T>
inline void Vector4CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
    o.z = v.z;
    o.w = v.w;
}

template <typename T>
inline void Vector4CalcCommon<T>::set(Base& v, T x, T y, T z, T w)
{
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
}

}  // namespace sead
