#pragma once

#include <math/seadVectorCalcCommon.h>
#ifndef SEAD_MATH_VECTOR_H_
#include <math/seadVector.h>
#endif

namespace sead
{
template <typename T>
inline Vector2<T>::Vector2(T x_, T y_)
{
    Vector2CalcCommon<T>::set(*this, x_, y_);
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
{
    Vector2CalcCommon<T>::add(*this, *this, other);
    return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
{
    Vector2CalcCommon<T>::sub(*this, *this, other);
    return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator*=(T t)
{
    this->x *= t;
    this->y *= t;
    return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator/=(T t)
{
    this->x /= t;
    this->y /= t;
    return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& other)
{
    Vector2CalcCommon<T>::set(*this, other);
    return *this;
}

template <typename T>
inline void Vector2<T>::set(const Vector2<T>& other)
{
    Vector2CalcCommon<T>::set(*this, other);
}

template <typename T>
inline void Vector2<T>::set(T x_, T y_)
{
    Vector2CalcCommon<T>::set(*this, x_, y_);
}

template <typename T>
inline Vector3<T>::Vector3(T x_, T y_, T z_)
{
    Vector3CalcCommon<T>::set(*this, x_, y_, z_);
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& other)
{
    Vector3CalcCommon<T>::set(*this, other);
    return *this;
}

template <typename T>
inline bool Vector3<T>::operator==(const Vector3& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

template <typename T>
inline bool Vector3<T>::operator!=(const Vector3& rhs) const
{
    return !operator==(rhs);
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other)
{
    Vector3CalcCommon<T>::add(*this, *this, other);
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other)
{
    Vector3CalcCommon<T>::sub(*this, *this, other);
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator*=(T t)
{
    Vector3CalcCommon<T>::multScalar(*this, *this, t);
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Mtx33& m)
{
    mul(m);
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Mtx34& m)
{
    mul(m);
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator/=(T t)
{
    this->x /= t;
    this->y /= t;
    this->z /= t;
    return *this;
}

template <typename T>
inline T Vector3<T>::dot(const Vector3<T>& t) const
{
    return Vector3CalcCommon<T>::dot(*this, t);
}

template <typename T>
inline T Vector3<T>::length() const
{
    return Vector3CalcCommon<T>::length(*this);
}

template <typename T>
inline T Vector3<T>::squaredLength() const
{
    return Vector3CalcCommon<T>::squaredLength(*this);
}

template <typename T>
inline bool Vector3<T>::equals(const Vector3<T>& rhs, T epsilon) const
{
    return Vector3CalcCommon<T>::equals(*this, rhs, epsilon);
}

template <typename T>
inline void Vector3<T>::add(const Vector3<T>& a)
{
    Vector3CalcCommon<T>::add(*this, *this, a);
}

template <typename T>
inline void Vector3<T>::mul(const Mtx33& m)
{
    setMul(m, *this);
}

template <typename T>
inline void Vector3<T>::mul(const Mtx34& m)
{
    setMul(m, *this);
}

template <typename T>
inline void Vector3<T>::multScalar(T t)
{
    Vector3CalcCommon<T>::multScalar(*this, *this, t);
}

template <typename T>
inline T Vector3<T>::normalize()
{
    return Vector3CalcCommon<T>::normalize(*this);
}

template <typename T>
inline void Vector3<T>::set(const Vector3<T>& other)
{
    Vector3CalcCommon<T>::set(*this, other);
}

template <typename T>
inline void Vector3<T>::set(T x_, T y_, T z_)
{
    Vector3CalcCommon<T>::set(*this, x_, y_, z_);
}

template <typename T>
inline void Vector3<T>::setCross(const Vector3<T>& a, const Vector3<T>& b)
{
    Vector3CalcCommon<T>::cross(*this, a, b);
}

template <typename T>
inline void Vector3<T>::setScaleAdd(T t, const Vector3<T>& a, const Vector3<T>& b)
{
    Vector3CalcCommon<T>::multScalarAdd(*this, t, a, b);
}

template <typename T>
inline void Vector3<T>::setMul(const Mtx33& m, const Vector3<T>& a)
{
    Vector3CalcCommon<T>::mul(*this, m, a);
}

template <typename T>
inline void Vector3<T>::setMul(const Mtx34& m, const Vector3<T>& a)
{
    Vector3CalcCommon<T>::mul(*this, m, a);
}

template <typename T>
inline Vector4<T>::Vector4(T x_, T y_, T z_, T w_)
{
    Vector4CalcCommon<T>::set(*this, x_, y_, z_, w_);
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator*=(T t)
{
    this->x *= t;
    this->y *= t;
    this->z *= t;
    this->w *= t;
    return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator/=(T t)
{
    this->x /= t;
    this->y /= t;
    this->z /= t;
    this->w /= t;
    return *this;
}

template <typename T>
inline Vector4<T>& Vector4<T>::operator=(const Vector4<T>& other)
{
    Vector4CalcCommon<T>::set(*this, other);
    return *this;
}

template <typename T>
inline void Vector4<T>::set(const Vector4<T>& other)
{
    Vector4CalcCommon<T>::set(*this, other);
}

template <typename T>
inline void Vector4<T>::set(T x_, T y_, T z_, T w_)
{
    Vector4CalcCommon<T>::set(*this, x_, y_, z_, w_);
}

}  // namespace sead
