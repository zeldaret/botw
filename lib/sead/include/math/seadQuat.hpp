#pragma once

#include <math/seadQuatCalcCommon.h>
#ifndef SEAD_MATH_QUAT_H_
#include <math/seadQuat.h>
#endif

namespace sead
{
template <typename T>
inline Quat<T>::Quat(T w_, T x_, T y_, T z_)
{
    QuatCalcCommon<T>::set(*this, w_, x_, y_, z_);
}

template <typename T>
inline Quat<T>& Quat<T>::operator*=(const Quat<T>& t)
{
    QuatCalcCommon<T>::setMul(*this, *this, t);
    return *this;
}

template <typename T>
inline T Quat<T>::length() const
{
    return QuatCalcCommon<T>::length(*this);
}

template <typename T>
inline T Quat<T>::normalize()
{
    return QuatCalcCommon<T>::normalize(*this);
}

template <typename T>
inline T Quat<T>::dot(const Self& q)
{
    return QuatCalcCommon<T>::dot(*this, q);
}

// reference?
// conjugate(q) / dot(q)?
template <typename T>
inline void Quat<T>::inverse(Self* q)
{
    T prod = dot(*this);
    if (prod > std::numeric_limits<T>::epsilon())
    {
        T inv = T(1) / prod;
        q->w = inv * this->w;
        q->x = inv * -this->x;
        q->y = inv * -this->y;
        q->z = inv * -this->z;
    }
    else
    {
        q->w = this->w;
        q->x = -this->x;
        q->y = -this->y;
        q->z = -this->z;
    }
}

template <typename T>
inline void Quat<T>::makeUnit()
{
    QuatCalcCommon<T>::makeUnit(*this);
}

template <typename T>
inline bool Quat<T>::makeVectorRotation(const Vec3& from, const Vec3& to)
{
    return QuatCalcCommon<T>::makeVectorRotation(*this, from, to);
}

template <typename T>
inline void Quat<T>::set(T w_, T x_, T y_, T z_)
{
    QuatCalcCommon<T>::set(*this, w_, x_, y_, z_);
}

template <typename T>
inline void Quat<T>::setRPY(T roll, T pitch, T yaw)
{
    QuatCalcCommon<T>::setRPY(*this, roll, pitch, yaw);
}

template <typename T>
inline void Quat<T>::calcRPY(Vec3& vec) const
{
    QuatCalcCommon<T>::calcRPY(vec, *this);
}

}  // namespace sead
