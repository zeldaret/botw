#pragma once

#include <math/seadVector.h>

namespace sead
{
template <typename T>
struct BoundBox2
{
    using Vector2 = sead::Vector2<T>;

    BoundBox2() { setUndef(); }
    BoundBox2(T x0, T y0, T x1, T y1) { set(x0, y0, x1, y1); }
    BoundBox2(const Vector2& min, const Vector2& max) : mMin(min), mMax(max) {}

    T getSizeX() const { return mMax.x - mMin.x; }
    T getSizeY() const { return mMax.y - mMin.y; }

    T getHalfSizeX() const { return (mMax.x - mMin.x) / 2.0f; }
    T getHalfSizeY() const { return (mMax.y - mMin.y) / 2.0f; }

    const Vector2& getMin() const { return mMin; }
    const Vector2& getMax() const { return mMax; }

    Vector2 getTL() const { return mMin; }
    Vector2 getTR() const { return Vector2(mMax.x, mMin.y); }
    Vector2 getBL() const { return Vector2(mMin.x, mMax.y); }
    Vector2 getBR() const { return mMax; }

    Vector2 getCenter() const;
    void getCenter(Vector2* p) const;
    bool isUndef() const;
    bool isInside(const Vector2& p) const;

    void setUndef();
    void set(T x0, T y0, T x1, T y1);
    void set(const Vector2& min, const Vector2& max);
    void setMin(const Vector2& min);
    void setMax(const Vector2& max);
    void setFromCenterAndXY(T centerX, T centerY, T sizeX, T sizeY);
    void setFromCornerAndXY(T cornerX, T cornerY, T sizeX, T sizeY);
    void setFromCenterAndXY(const Vector2& center, T sizeX, T sizeY)
    {
        setFromCenterAndXY(center.x, center.y, sizeX, sizeY);
    }
    void setFromCornerAndXY(const Vector2& corner, T sizeX, T sizeY);
    void offset(T dx, T dy);
    void offset(const Vector2& dv);
    void scaleX(T sx);
    void scaleY(T sy);

private:
    Vector2 mMin;
    Vector2 mMax;

    static const BoundBox2<T> cUndefined;
};

template <typename T>
struct BoundBox3
{
    using Vector3 = sead::Vector3<T>;

    BoundBox3() { setUndef(); }
    BoundBox3(T x0, T y0, T z0, T x1, T y1, T z1) { set(x0, y0, z0, x1, y1, z1); }
    BoundBox3(const Vector3& min, const Vector3& max) { set(min, max); }

    T getSizeX() const { return mMax.x - mMin.x; }
    T getSizeY() const { return mMax.y - mMin.y; }
    T getSizeZ() const { return mMax.z - mMin.z; }

    T getHalfSizeX() const { return (mMax.x - mMin.x) / 2.0f; }
    T getHalfSizeY() const { return (mMax.y - mMin.y) / 2.0f; }
    T getHalfSizeZ() const { return (mMax.z - mMin.z) / 2.0f; }

    const Vector3& getMin() const { return mMin; }
    const Vector3& getMax() const { return mMax; }

    Vector3 getCenter() const;
    void getCenter(Vector3* p) const;
    bool isUndef() const;
    bool isInside(const Vector3& p) const;

    void setUndef();
    void set(T x0, T y0, T z0, T x1, T y1, T z1);
    void set(const Vector3& min, const Vector3& max);
    void setMin(const Vector3& min);
    void setMax(const Vector3& max);
    void offset(T dx, T dy, T dz);
    void offset(const Vector3& dv);
    void scaleX(T sx);
    void scaleY(T sy);
    void scaleZ(T sz);

private:
    Vector3 mMin;
    Vector3 mMax;

    static const BoundBox3<T> cUndefined;
};

typedef BoundBox2<f32> BoundBox2f;
typedef BoundBox3<f32> BoundBox3f;

}  // namespace sead

#define SEAD_MATH_BOUND_BOX_H_
#include <math/seadBoundBox.hpp>
#undef SEAD_MATH_BOUND_BOX_H_
