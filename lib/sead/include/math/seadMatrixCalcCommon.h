#pragma once

#include <math/seadMathPolicies.h>
#include <math/seadVector.h>

namespace sead
{
template <typename T>
class Matrix22CalcCommon
{
public:
    using Base = typename Policies<T>::Mtx22Base;

public:
    static void makeIdentity(Base& o);
    static void makeZero(Base& o);

    static void copy(Base& o, const Base& n);
    static void inverse(Base& o, const Base& n);
    static void inverseTranspose(Base& o, const Base& n);
    static void multiply(Base& o, const Base& a, const Base& b);
    static void transpose(Base& o);
    static void transposeTo(Base& o, const Base& n);
};

template <typename T>
class Matrix33CalcCommon
{
public:
    using Base = typename Policies<T>::Mtx33Base;
    using Mtx34 = typename Policies<T>::Mtx34Base;

    using Quat = typename Policies<T>::QuatBase;
    using Vec3 = typename Policies<T>::Vec3Base;

public:
    static void makeIdentity(Base& o);
    static void makeZero(Base& o);

    static void copy(Base& o, const Base& n);
    static void copy(Base& o, const Mtx34& n);
    static void inverse(Base& o, const Base& n);
    static void inverseTranspose(Base& o, const Base& n);
    static void multiply(Base& o, const Base& a, const Base& b);
    static void multiply(Base& o, const Mtx34& a, const Base& b);
    static void multiply(Base& o, const Base& a, const Mtx34& b);
    static void transpose(Base& o);
    static void transposeTo(Base& o, const Base& n);

    static void makeQ(Base& o, const Quat& q);
    static void makeR(Base& o, const Vec3& r);
    static void makeRIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void makeS(Base& o, const Vec3& s);
    static void makeSR(Base& o, const Vec3& s, const Vec3& r);
    static void makeSRIdx(Base& o, const Vec3& s, const Vector3<u32>& r);
    static void makeSRzxyIdx(Base& o, const Vec3& s, const Vector3<u32>& r);
    static void toQuat(Quat& q, const Base& n);
};

template <typename T>
class Matrix34CalcCommon
{
public:
    using Base = typename Policies<T>::Mtx34Base;
    using Mtx33 = typename Policies<T>::Mtx33Base;
    using Mtx44 = typename Policies<T>::Mtx44Base;

    using Quat = typename Policies<T>::QuatBase;
    using Vec3 = typename Policies<T>::Vec3Base;
    using Vec4 = typename Policies<T>::Vec4Base;

public:
    static void makeIdentity(Base& o);
    static void makeZero(Base& o);

    static void copy(Base& o, const Base& n);
    static void copy(Base& o, const Mtx33& n, const Vec3& t);
    static void copy(Base& o, const Mtx44& n);
    static bool inverse(Base& o, const Base& n);
    static bool inverse33(Base& o, const Base& n);
    static bool inverseTranspose(Base& o, const Base& n);
    static void multiply(Base& o, const Base& a, const Base& b);
    static void multiply(Base& o, const Mtx33& a, const Base& b);
    static void multiply(Base& o, const Base& a, const Mtx33& b);
    static void transpose(Base& o);
    static void transposeTo(Base& o, const Base& n);

    static void makeQ(Base& o, const Quat& q);
    static void makeQT(Base& o, const Quat& q, const Vec3& t);
    static void makeR(Base& o, const Vec3& r);
    static void makeRIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void makeRT(Base& o, const Vec3& r, const Vec3& t);
    static void makeRTIdx(Base& o, const Vector3<u32>& r, const Vec3& t);
    static void makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void makeRzxyTIdx(Base& o, const Vector3<u32>& r, const Vec3& t);
    static void makeS(Base& o, const Vec3& s);
    static void makeSR(Base& o, const Vec3& s, const Vec3& r);
    static void makeSRIdx(Base& o, const Vec3& s, const Vector3<u32>& r);
    static void makeSRT(Base& o, const Vec3& s, const Vec3& r, const Vec3& t);
    static void makeSRTIdx(Base& o, const Vec3& s, const Vector3<u32>& r, const Vec3& t);
    static void makeSRzxyIdx(Base& o, const Vec3& s, const Vector3<u32>& r);
    static void makeSRzxyTIdx(Base& o, const Vec3& s, const Vector3<u32>& r, const Vec3& t);
    static void makeST(Base& o, const Vec3& s, const Vec3& t);
    static void makeT(Base& o, const Vec3& t);
    static void toQuat(Quat& q, const Base& n);

    static void getBase(Vec3& v, const Base& n, s32 axis);
    static void getRow(Vec4& v, const Base& n, s32 row);
    static void getTranslation(Vec3& v, const Base& n);
    static void getRotation(Vec3& v, const Base& n);

    static void scaleAllElements(Base& n, T s);
    static void scaleBases(Base& n, T sx, T sy, T sz);
    static void setBase(Base& n, s32 axis, const Vec3& v);
    static void setRow(Base& n, const Vec4& v, s32 row);
    static void setTranslation(Base& n, const Vec3& v);
};

template <typename T>
class Matrix44CalcCommon
{
public:
    using Base = typename Policies<T>::Mtx44Base;
    using Mtx33 = typename Policies<T>::Mtx33Base;
    using Mtx34 = typename Policies<T>::Mtx34Base;

    using Quat = typename Policies<T>::QuatBase;
    using Vec3 = typename Policies<T>::Vec3Base;
    using Vec4 = typename Policies<T>::Vec4Base;

public:
    static void makeIdentity(Base& o);
    static void makeZero(Base& o);

    static void copy(Base& o, const Base& n);
    static void copy(Base& o, const Mtx33& n, const Vec3& t, const Vec4& v);
    static void copy(Base& o, const Mtx34& n, const Vec4& v);
    static void inverse(Base& o, const Base& n);
    static void inverseTranspose(Base& o, const Base& n);
    static void multiply(Base& o, const Base& a, const Base& b);
    static void multiply(Base& o, const Mtx34& a, const Base& b);
    static void multiply(Base& o, const Base& a, const Mtx34& b);
    static void transpose(Base& o);
    static void transposeTo(Base& o, const Base& n);

    static void makeQ(Base& o, const Quat& q);
    static void makeR(Base& o, const Vec3& r);
    static void makeRIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr);
    static void toQuat(Quat& q, const Base& n);

    static void getCol(Vec4& v, const Base& n, s32 axis);
    static void getRow(Vec4& v, const Base& n, s32 row);

    static void scaleAllElements(Base& n, T s);
    static void scaleBases(Base& n, T sx, T sy, T sz, T sw);
    static void setCol(Base& n, s32 axis, const Vec4& v);
    static void setRow(Base& n, const Vec4& v, s32 row);
};

}  // namespace sead

#define SEAD_MATH_MATRIX_CALC_COMMON_H_
#include <math/seadMatrixCalcCommon.hpp>
#undef SEAD_MATH_MATRIX_CALC_COMMON_H_
