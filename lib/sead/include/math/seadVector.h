#pragma once

#include <basis/seadTypes.h>
#include <cmath>
#include <math/seadMathPolicies.h>
#include <math/seadVectorCalcCommon.h>

namespace sead
{
template <typename T>
struct Vector2 : public Policies<T>::Vec2Base
{
    /// @warning This constructor leaves member variables uninitialized.
    Vector2() {}
    Vector2(const Vector2& other) = default;
    Vector2(T x, T y);

    Vector2& operator=(const Vector2& other);

    Vector2& operator+=(const Vector2& other);

    friend Vector2 operator+(const Vector2& a, const Vector2& b)
    {
        Vector2 o;
        Vector2CalcCommon<T>::add(o, a, b);
        return o;
    }

    Vector2& operator-=(const Vector2& other);

    friend Vector2 operator-(const Vector2& a, const Vector2& b)
    {
        Vector2 o;
        Vector2CalcCommon<T>::sub(o, a, b);
        return o;
    }

    Vector2& operator*=(T t);

    friend Vector2 operator*(const Vector2& a, T t)
    {
        Vector2 o;
        o.x = a.x * t;
        o.y = a.y * t;
        return o;
    }

    friend Vector2 operator*(T t, const Vector2& a) { return operator*(a, t); }

    Vector2& operator/=(T t);

    friend Vector2 operator/(const Vector2& a, T t) { return {a.x / t, a.y / t}; }

    bool operator==(const Vector2& rhs) const { return this->x == rhs.x && this->y == rhs.y; }
    bool operator!=(const Vector2& rhs) const { return !operator==(rhs); }

    void set(const Vector2& other);
    void set(T x_, T y_);

    static const Vector2 zero;
    static const Vector2 ex;
    static const Vector2 ey;
    static const Vector2 ones;
};

template <typename T>
struct Vector3 : public Policies<T>::Vec3Base
{
    using Mtx33 = typename Policies<T>::Mtx33Base;
    using Mtx34 = typename Policies<T>::Mtx34Base;

    /// @warning This constructor leaves member variables uninitialized.
    Vector3() {}
    Vector3(const Vector3& other) = default;
    Vector3(T x, T y, T z);

    Vector3& operator=(const Vector3& other);
    bool operator==(const Vector3& rhs) const;
    bool operator!=(const Vector3& rhs) const;

    Vector3& operator+=(const Vector3& other);
    friend Vector3 operator+(const Vector3& a, const Vector3& b)
    {
        Vector3 o;
        Vector3CalcCommon<T>::add(o, a, b);
        return o;
    }

    Vector3& operator-=(const Vector3& other);
    friend Vector3 operator-(const Vector3& a, const Vector3& b)
    {
        Vector3 o;
        Vector3CalcCommon<T>::sub(o, a, b);
        return o;
    }

    Vector3& operator*=(T t);
    Vector3& operator*=(const Mtx33& m);
    Vector3& operator*=(const Mtx34& m);
    friend Vector3 operator*(const Vector3& a, T t)
    {
        Vector3 o;
        Vector3CalcCommon<T>::multScalar(o, a, t);
        return o;
    }
    friend Vector3 operator*(T t, const Vector3& a) { return operator*(a, t); }
    friend Vector3 operator*(const Mtx33& m, const Vector3& a)
    {
        Vector3 o;
        o.setMul(m, a);
        return o;
    }
    friend Vector3 operator*(const Mtx34& m, const Vector3& a)
    {
        Vector3 o;
        o.setMul(m, a);
        return o;
    }

    Vector3& operator/=(T t);
    friend Vector3 operator/(const Vector3& a, T t) { return {a.x / t, a.y / t, a.z / t}; }

    Vector3 operator-() const { return {-this->x, -this->y, -this->z}; }

    T dot(const Vector3& t) const;
    T length() const;
    T squaredLength() const;

    /// Checks if the differences of all components of lhs and rhs are within `epsilon`.
    /// (i.e. -epsilon <= lhs.x - rhs.x <= epsilon, and so on).
    bool equals(const Vector3& rhs, T epsilon = 0) const;

    void add(const Vector3& a);
    /// Multiply m by this vector (self = m * self).
    void mul(const Mtx33& m);
    /// Apply a transformation `m` (rotation + translation) to this vector.
    void mul(const Mtx34& m);
    void multScalar(T t);

    T normalize();
    void set(const Vector3& other);
    void set(T x, T y, T z);
    void setCross(const Vector3<T>& a, const Vector3<T>& b);
    void setScaleAdd(T t, const Vector3<T>& a, const Vector3<T>& b);
    void setMul(const Mtx33& m, const Vector3& a);
    void setMul(const Mtx34& m, const Vector3& a);

    static const Vector3 zero;
    static const Vector3 ex;
    static const Vector3 ey;
    static const Vector3 ez;
    static const Vector3 ones;
};

template <typename T>
struct Vector4 : public Policies<T>::Vec4Base
{
    /// @warning This constructor leaves member variables uninitialized.
    Vector4() {}
    Vector4(const Vector4& other) = default;
    Vector4(T x, T y, T z, T w);

    Vector4& operator=(const Vector4& other);

    Vector4& operator+=(const Vector4& other);

    friend Vector4 operator+(const Vector4& a, const Vector4& b)
    {
        return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    Vector4& operator-=(const Vector4& other);

    friend Vector4 operator-(const Vector4& a, const Vector4& b)
    {
        return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    Vector4& operator*=(T t);

    friend Vector4 operator*(const Vector4& a, T t) { return {a.x * t, a.y * t, a.z * t, a.w * t}; }

    friend Vector4 operator*(T t, const Vector4& a) { return operator*(a, t); }

    Vector4& operator/=(T t);

    friend Vector4 operator/(const Vector4& a, T t) { return {a.x / t, a.y / t, a.z / t, a.w / t}; }

    bool operator==(const Vector4& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
    }
    bool operator!=(const Vector4& rhs) const { return !operator==(rhs); }

    void set(const Vector4& v);
    void set(T x_, T y_, T z_, T w_);

    static const Vector4 zero;
    static const Vector4 ex;
    static const Vector4 ey;
    static const Vector4 ez;
    static const Vector4 ew;
    static const Vector4 ones;
};

typedef Vector2<f32> Vector2f;
typedef Vector3<f32> Vector3f;
typedef Vector4<f32> Vector4f;

template <>
const Vector2<f32> Vector2<f32>::zero;

template <>
const Vector2<f32> Vector2<f32>::ex;

template <>
const Vector2<f32> Vector2<f32>::ey;

template <>
const Vector2<f32> Vector2<f32>::ones;

template <>
const Vector3<f32> Vector3<f32>::zero;

template <>
const Vector3<f32> Vector3<f32>::ex;

template <>
const Vector3<f32> Vector3<f32>::ey;

template <>
const Vector3<f32> Vector3<f32>::ez;

template <>
const Vector3<f32> Vector3<f32>::ones;

template <>
const Vector4<f32> Vector4<f32>::zero;

template <>
const Vector4<f32> Vector4<f32>::ex;

template <>
const Vector4<f32> Vector4<f32>::ey;

template <>
const Vector4<f32> Vector4<f32>::ez;

template <>
const Vector4<f32> Vector4<f32>::ew;

template <>
const Vector4<f32> Vector4<f32>::ones;

}  // namespace sead

#define SEAD_MATH_VECTOR_H_
#include <math/seadVector.hpp>
#undef SEAD_MATH_VECTOR_H_
