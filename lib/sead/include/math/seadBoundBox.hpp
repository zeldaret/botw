#pragma once

#include <math/seadMathCalcCommon.h>

#ifndef SEAD_MATH_BOUND_BOX_H_
#include <math/seadBoundBox.h>
#endif

namespace sead
{
template <typename T>
inline Vector2<T> BoundBox2<T>::getCenter() const
{
    return Vector2((mMin.x + mMax.x) / 2.0f, (mMin.y + mMax.y) / 2.0f);
}

template <typename T>
inline void BoundBox2<T>::getCenter(Vector2* center) const
{
    center->set((mMin.x + mMax.x) / 2.0f, (mMin.y + mMax.y) / 2.0f);
}

template <typename T>
inline bool BoundBox2<T>::isUndef() const
{
    return mMin.x > mMax.x || mMin.y > mMax.y;
}

template <typename T>
inline bool BoundBox2<T>::isInside(const Vector2& p) const
{
    return mMin.x <= p.x && p.x <= mMax.x && mMin.y <= p.y && p.y <= mMax.y;
}

template <typename T>
inline void BoundBox2<T>::setUndef()
{
    const T max = MathCalcCommon<T>::maxNumber();
    mMin.set(max, max);
    const T min = MathCalcCommon<T>::minNumber();
    mMax.set(min, min);
}

template <typename T>
inline void BoundBox2<T>::set(T x0, T y0, T x1, T y1)
{
    if (x0 < x1)
    {
        mMin.x = x0;
        mMax.x = x1;
    }
    else
    {
        mMin.x = x1;
        mMax.x = x0;
    }

    if (y0 < y1)
    {
        mMin.y = y0;
        mMax.y = y1;
    }
    else
    {
        mMin.y = y1;
        mMax.y = y0;
    }
}

template <typename T>
inline void BoundBox2<T>::set(const Vector2& min, const Vector2& max)
{
    mMin = min;
    mMax = max;
}

template <typename T>
inline void BoundBox2<T>::setMin(const Vector2& min)
{
    mMin = min;
}

template <typename T>
inline void BoundBox2<T>::setMax(const Vector2& max)
{
    mMax = max;
}

template <typename T>
inline void BoundBox2<T>::setFromCenterAndXY(T centerX, T centerY, T sizeX, T sizeY)
{
    mMin.set(centerX - sizeX / 2.0f, centerY - sizeY / 2.0f);
    mMax.set(centerX + sizeX / 2.0f, centerY + sizeY / 2.0f);
}

template <typename T>
inline void BoundBox2<T>::setFromCornerAndXY(T cornerX, T cornerY, T sizeX, T sizeY)
{
    mMin.set(cornerX, cornerY);
    mMax.set(cornerX + sizeX, cornerY + sizeY);
}

template <typename T>
inline void BoundBox2<T>::setFromCornerAndXY(const Vector2& corner, T sizeX, T sizeY)
{
    mMin.set(corner.x, corner.y);
    mMax.set(corner.x + sizeX, corner.y + sizeY);
}

template <typename T>
inline void BoundBox2<T>::offset(T dx, T dy)
{
    mMin.x += dx;
    mMin.y += dy;
    mMax.x += dx;
    mMax.y += dy;
}

template <typename T>
inline void BoundBox2<T>::offset(const Vector2& dv)
{
    offset(dv.x, dv.y);
}

template <typename T>
inline void BoundBox2<T>::scaleX(T sx)
{
    T sizeX = (mMax.x - mMin.x) * (sx / 2.0f);
    T centerX = (mMin.x + mMax.x) / 2.0f;

    mMin.x = centerX - sizeX;
    mMax.x = centerX + sizeX;
}

template <typename T>
inline void BoundBox2<T>::scaleY(T sy)
{
    T sizeY = (mMax.y - mMin.y) * (sy / 2.0f);
    T centerY = (mMin.y + mMax.y) / 2.0f;

    mMin.y = centerY - sizeY;
    mMax.y = centerY + sizeY;
}

template <typename T>
inline Vector3<T> BoundBox3<T>::getCenter() const
{
    return Vector3((mMin.x + mMax.x) / 2.0f, (mMin.y + mMax.y) / 2.0f, (mMin.z + mMax.z) / 2.0f);
}

template <typename T>
inline void BoundBox3<T>::getCenter(Vector3* center) const
{
    center->set((mMin.x + mMax.x) / 2.0f, (mMin.y + mMax.y) / 2.0f, (mMin.z + mMax.z) / 2.0f);
}

template <typename T>
inline bool BoundBox3<T>::isUndef() const
{
    return mMin.x > mMax.x || mMin.y > mMax.y || mMin.z > mMax.z;
}

template <typename T>
inline bool BoundBox3<T>::isInside(const Vector3& p) const
{
    return mMin.x <= p.x && p.x <= mMax.x && mMin.y <= p.y && p.y <= mMax.y && mMin.z <= p.z &&
           p.z <= mMax.z;
}

template <typename T>
inline void BoundBox3<T>::setUndef()
{
    const T max = MathCalcCommon<T>::maxNumber();
    mMin.set(max, max, max);
    const T min = MathCalcCommon<T>::minNumber();
    mMax.set(min, min, min);
}

template <typename T>
inline void BoundBox3<T>::set(T x0, T y0, T z0, T x1, T y1, T z1)
{
    if (x0 < x1)
    {
        mMin.x = x0;
        mMax.x = x1;
    }
    else
    {
        mMin.x = x1;
        mMax.x = x0;
    }

    if (y0 < y1)
    {
        mMin.y = y0;
        mMax.y = y1;
    }
    else
    {
        mMin.y = y1;
        mMax.y = y0;
    }

    if (z0 < z1)
    {
        mMin.z = z0;
        mMax.z = z1;
    }
    else
    {
        mMin.z = z1;
        mMax.z = z0;
    }
}

template <typename T>
inline void BoundBox3<T>::set(const Vector3& min, const Vector3& max)
{
    mMin = min;
    mMax = max;
}

template <typename T>
inline void BoundBox3<T>::setMin(const Vector3& min)
{
    mMin = min;
}

template <typename T>
inline void BoundBox3<T>::setMax(const Vector3& max)
{
    mMax = max;
}

template <typename T>
inline void BoundBox3<T>::offset(T dx, T dy, T dz)
{
    mMin.x += dx;
    mMin.y += dy;
    mMin.z += dz;
    mMax.x += dx;
    mMax.y += dy;
    mMax.z += dz;
}

template <typename T>
inline void BoundBox3<T>::offset(const Vector3& dv)
{
    offset(dv.x, dv.y, dv.z);
}

template <typename T>
inline void BoundBox3<T>::scaleX(T sx)
{
    T sizeX = (mMax.x - mMin.x) * (sx / 2.0f);
    T centerX = (mMin.x + mMax.x) / 2.0f;

    mMin.x = centerX - sizeX;
    mMax.x = centerX + sizeX;
}

template <typename T>
inline void BoundBox3<T>::scaleY(T sy)
{
    T sizeY = (mMax.y - mMin.y) * (sy / 2.0f);
    T centerY = (mMin.y + mMax.y) / 2.0f;

    mMin.y = centerY - sizeY;
    mMax.y = centerY + sizeY;
}

template <typename T>
inline void BoundBox3<T>::scaleZ(T sz)
{
    T sizeZ = (mMax.z - mMin.z) * (sz / 2.0f);
    T centerZ = (mMin.z + mMax.z) / 2.0f;

    mMin.z = centerZ - sizeZ;
    mMax.z = centerZ + sizeZ;
}

}  // namespace sead
