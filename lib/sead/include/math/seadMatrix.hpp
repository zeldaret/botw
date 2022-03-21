#pragma once

#include <math/seadMatrixCalcCommon.h>
#ifndef SEAD_MATH_MATRIX_H_
#include <math/seadMatrix.h>
#endif

namespace sead
{
template <typename T>
inline Matrix22<T>::Matrix22(T a00, T a01, T a10, T a11)
{
    this->m[0][0] = a00;
    this->m[0][1] = a01;

    this->m[1][0] = a10;
    this->m[1][1] = a11;
}

template <typename T>
inline T Matrix22<T>::operator()(s32 i, s32 j) const
{
    return this->m[i][j];
}

template <typename T>
inline T& Matrix22<T>::operator()(s32 i, s32 j)
{
    return this->m[i][j];
}

template <typename T>
inline Matrix22<T>& Matrix22<T>::operator=(const Self& n)
{
    Matrix22CalcCommon<T>::copy(*this, n);
    return *this;
}

template <typename T>
inline void Matrix22<T>::makeIdentity()
{
    Matrix22CalcCommon<T>::makeIdentity(*this);
}

template <typename T>
inline void Matrix22<T>::makeZero()
{
    Matrix22CalcCommon<T>::makeZero(*this);
}

template <typename T>
inline void Matrix22<T>::setInverse(const Self& n)
{
    Matrix22CalcCommon<T>::inverse(*this, n);
}

template <typename T>
inline void Matrix22<T>::setInverseTranspose(const Self& n)
{
    Matrix22CalcCommon<T>::inverseTranspose(*this, n);
}

template <typename T>
inline void Matrix22<T>::setMul(const Self& a, const Self& b)
{
    Matrix22CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix22<T>::setTranspose(const Self& n)
{
    Matrix22CalcCommon<T>::transposeTo(*this, n);
}

template <typename T>
inline void Matrix22<T>::transpose()
{
    Matrix22CalcCommon<T>::transpose(*this);
}

template <typename T>
inline Matrix33<T>::Matrix33(T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22)
{
    this->m[0][0] = a00;
    this->m[0][1] = a01;
    this->m[0][2] = a02;

    this->m[1][0] = a10;
    this->m[1][1] = a11;
    this->m[1][2] = a12;

    this->m[2][0] = a20;
    this->m[2][1] = a21;
    this->m[2][2] = a22;
}

template <typename T>
inline Matrix33<T>::Matrix33(const Mtx34& mtx34)
{
    Matrix33CalcCommon<T>::copy(*this, mtx34);
}

template <typename T>
inline T Matrix33<T>::operator()(s32 i, s32 j) const
{
    return this->m[i][j];
}

template <typename T>
inline T& Matrix33<T>::operator()(s32 i, s32 j)
{
    return this->m[i][j];
}

template <typename T>
inline Matrix33<T>& Matrix33<T>::operator=(const Self& n)
{
    Matrix33CalcCommon<T>::copy(*this, n);
    return *this;
}

template <typename T>
inline void Matrix33<T>::makeIdentity()
{
    Matrix33CalcCommon<T>::makeIdentity(*this);
}

template <typename T>
inline void Matrix33<T>::makeZero()
{
    Matrix33CalcCommon<T>::makeZero(*this);
}

template <typename T>
inline void Matrix33<T>::setInverse(const Self& n)
{
    Matrix33CalcCommon<T>::inverse(*this, n);
}

template <typename T>
inline void Matrix33<T>::setInverseTranspose(const Self& n)
{
    Matrix33CalcCommon<T>::inverseTranspose(*this, n);
}

template <typename T>
inline void Matrix33<T>::setMul(const Self& a, const Self& b)
{
    Matrix33CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix33<T>::setMul(const Mtx34& a, const Self& b)
{
    Matrix33CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix33<T>::setMul(const Self& a, const Mtx34& b)
{
    Matrix33CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix33<T>::setTranspose(const Self& n)
{
    Matrix33CalcCommon<T>::transposeTo(*this, n);
}

template <typename T>
inline void Matrix33<T>::transpose()
{
    Matrix33CalcCommon<T>::transpose(*this);
}

template <typename T>
inline void Matrix33<T>::fromQuat(const Quat<T>& q)
{
    Matrix33CalcCommon<T>::makeQ(*this, q);
}

template <typename T>
inline void Matrix33<T>::makeR(const Vec3& r)
{
    Matrix33CalcCommon<T>::makeR(*this, r);
}

template <typename T>
inline void Matrix33<T>::makeRIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix33CalcCommon<T>::makeRIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix33<T>::makeRzxyIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix33CalcCommon<T>::makeRzxyIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix33<T>::makeS(const Vec3& s)
{
    Matrix33CalcCommon<T>::makeS(*this, s);
}

template <typename T>
inline void Matrix33<T>::makeS(T x, T y, T z)
{
    Vec3 s(x, y, z);
    Matrix33CalcCommon<T>::makeS(*this, s);
}

template <typename T>
inline void Matrix33<T>::makeSR(const Vec3& s, const Vec3& r)
{
    Matrix33CalcCommon<T>::makeSR(*this, s, r);
}

template <typename T>
inline void Matrix33<T>::makeSRIdx(const Vec3& s, const Vector3<u32>& r)
{
    Matrix33CalcCommon<T>::makeSRIdx(*this, s, r);
}

template <typename T>
inline void Matrix33<T>::makeSRzxyIdx(const Vec3& s, const Vector3<u32>& r)
{
    Matrix33CalcCommon<T>::makeSRzxyIdx(*this, s, r);
}

template <typename T>
inline void Matrix33<T>::toQuat(Quat<T>& q) const
{
    Matrix33CalcCommon<T>::toQuat(q, *this);
}

template <typename T>
inline Matrix34<T>::Matrix34(T a00, T a01, T a02, T a03, T a10, T a11, T a12, T a13, T a20, T a21,
                             T a22, T a23)
{
    this->m[0][0] = a00;
    this->m[0][1] = a01;
    this->m[0][2] = a02;
    this->m[0][3] = a03;

    this->m[1][0] = a10;
    this->m[1][1] = a11;
    this->m[1][2] = a12;
    this->m[1][3] = a13;

    this->m[2][0] = a20;
    this->m[2][1] = a21;
    this->m[2][2] = a22;
    this->m[2][3] = a23;
}

template <typename T>
inline Matrix34<T>::Matrix34(const Mtx33& mtx33, const Vec3& t)
{
    Matrix34CalcCommon<T>::copy(*this, mtx33, t);
}

template <typename T>
inline Matrix34<T>::Matrix34(const Mtx44& mtx44)
{
    Matrix34CalcCommon<T>::copy(*this, mtx44);
}

template <typename T>
inline T Matrix34<T>::operator()(s32 i, s32 j) const
{
    return this->m[i][j];
}

template <typename T>
inline T& Matrix34<T>::operator()(s32 i, s32 j)
{
    return this->m[i][j];
}

template <typename T>
inline Matrix34<T>& Matrix34<T>::operator=(const Self& n)
{
    Matrix34CalcCommon<T>::copy(*this, n);
    return *this;
}

template <typename T>
inline void Matrix34<T>::makeIdentity()
{
    Matrix34CalcCommon<T>::makeIdentity(*this);
}

template <typename T>
inline void Matrix34<T>::makeZero()
{
    Matrix34CalcCommon<T>::makeZero(*this);
}

template <typename T>
inline bool Matrix34<T>::invert()
{
    return setInverse(*this);
}

template <typename T>
inline bool Matrix34<T>::invert33()
{
    return setInverse33(*this);
}

template <typename T>
inline bool Matrix34<T>::invertTranspose()
{
    return setInverseTranspose(*this);
}

template <typename T>
inline bool Matrix34<T>::setInverse(const Self& n)
{
    return Matrix34CalcCommon<T>::inverse(*this, n);
}

template <typename T>
inline bool Matrix34<T>::setInverse33(const Self& n)
{
    return Matrix34CalcCommon<T>::inverse33(*this, n);
}

template <typename T>
inline bool Matrix34<T>::setInverseTranspose(const Self& n)
{
    return Matrix34CalcCommon<T>::inverseTranspose(*this, n);
}

template <typename T>
inline void Matrix34<T>::setMul(const Self& a, const Self& b)
{
    Matrix34CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix34<T>::setMul(const Mtx33& a, const Self& b)
{
    Matrix34CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix34<T>::setTranspose(const Self& n)
{
    Matrix34CalcCommon<T>::transposeTo(*this, n);
}

template <typename T>
inline void Matrix34<T>::transpose()
{
    Matrix34CalcCommon<T>::transpose(*this);
}

template <typename T>
inline void Matrix34<T>::fromQuat(const Quat<T>& q)
{
    Matrix34CalcCommon<T>::makeQ(*this, q);
}

template <typename T>
inline void Matrix34<T>::makeQT(const Quat<T>& q, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeQT(*this, q, t);
}

template <typename T>
inline void Matrix34<T>::makeR(const Vec3& r)
{
    Matrix34CalcCommon<T>::makeR(*this, r);
}

template <typename T>
inline void Matrix34<T>::makeRIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix34CalcCommon<T>::makeRIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix34<T>::makeRT(const Vec3& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeRT(*this, r, t);
}

template <typename T>
inline void Matrix34<T>::makeRTIdx(const Vector3<u32>& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeRTIdx(*this, r, t);
}

template <typename T>
inline void Matrix34<T>::makeRzxyIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix34CalcCommon<T>::makeRzxyIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix34<T>::makeRzxyTIdx(const Vector3<u32>& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeRzxyTIdx(*this, r, t);
}

template <typename T>
inline void Matrix34<T>::makeS(const Vec3& s)
{
    Matrix34CalcCommon<T>::makeS(*this, s);
}

template <typename T>
inline void Matrix34<T>::makeS(T x, T y, T z)
{
    Vec3 s(x, y, z);
    Matrix34CalcCommon<T>::makeS(*this, s);
}

template <typename T>
inline void Matrix34<T>::makeSR(const Vec3& s, const Vec3& r)
{
    Matrix34CalcCommon<T>::makeSR(*this, s, r);
}

template <typename T>
inline void Matrix34<T>::makeSRIdx(const Vec3& s, const Vector3<u32>& r)
{
    Matrix34CalcCommon<T>::makeSRIdx(*this, s, r);
}

template <typename T>
inline void Matrix34<T>::makeSRT(const Vec3& s, const Vec3& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeSRT(*this, s, r, t);
}

template <typename T>
inline void Matrix34<T>::makeSRTIdx(const Vec3& s, const Vector3<u32>& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeSRTIdx(*this, s, r, t);
}

template <typename T>
inline void Matrix34<T>::makeSRzxyIdx(const Vec3& s, const Vector3<u32>& r)
{
    Matrix34CalcCommon<T>::makeSRzxyIdx(*this, s, r);
}

template <typename T>
inline void Matrix34<T>::makeSRzxyTIdx(const Vec3& s, const Vector3<u32>& r, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeSRzxyTIdx(*this, s, r, t);
}

template <typename T>
inline void Matrix34<T>::makeST(const Vec3& s, const Vec3& t)
{
    Matrix34CalcCommon<T>::makeST(*this, s, t);
}

template <typename T>
inline void Matrix34<T>::makeT(const Vec3& t)
{
    Matrix34CalcCommon<T>::makeT(*this, t);
}

template <typename T>
inline void Matrix34<T>::makeT(T x, T y, T z)
{
    Vec3 t(x, y, z);
    Matrix34CalcCommon<T>::makeT(*this, t);
}

template <typename T>
inline void Matrix34<T>::toQuat(Quat<T>& q) const
{
    Matrix34CalcCommon<T>::toQuat(q, *this);
}

template <typename T>
inline void Matrix34<T>::getBase(Vec3& o, s32 axis) const
{
    Matrix34CalcCommon<T>::getBase(o, *this, axis);
}

template <typename T>
inline void Matrix34<T>::getRow(Vec4& o, s32 row) const
{
    Matrix34CalcCommon<T>::getRow(o, *this, row);
}

template <typename T>
inline void Matrix34<T>::getTranslation(Vec3& o) const
{
    Matrix34CalcCommon<T>::getTranslation(o, *this);
}

template <typename T>
inline void Matrix34<T>::getRotation(Vec3& o) const
{
    Matrix34CalcCommon<T>::getRotation(o, *this);
}

template <typename T>
inline void Matrix34<T>::scaleAllElements(T s)
{
    Matrix34CalcCommon<T>::scaleAllElements(*this, s);
}

template <typename T>
inline void Matrix34<T>::scaleBases(T sx, T sy, T sz)
{
    Matrix34CalcCommon<T>::scaleBases(*this, sx, sy, sz);
}

template <typename T>
inline void Matrix34<T>::setBase(s32 axis, const Vec3& v)
{
    Matrix34CalcCommon<T>::setBase(*this, axis, v);
}

template <typename T>
inline void Matrix34<T>::setRow(s32 row, const Vec4& v)
{
    Matrix34CalcCommon<T>::setRow(*this, v, row);
}

template <typename T>
inline void Matrix34<T>::setTranslation(const Vec3& t)
{
    Matrix34CalcCommon<T>::setTranslation(*this, t);
}

template <typename T>
inline void Matrix34<T>::setTranslation(T x, T y, T z)
{
    Vec3 t(x, y, z);
    Matrix34CalcCommon<T>::setTranslation(*this, t);
}

template <typename T>
inline Matrix44<T>::Matrix44(T a00, T a01, T a02, T a03, T a10, T a11, T a12, T a13, T a20, T a21,
                             T a22, T a23, T a30, T a31, T a32, T a33)
{
    this->m[0][0] = a00;
    this->m[0][1] = a01;
    this->m[0][2] = a02;
    this->m[0][3] = a03;

    this->m[1][0] = a10;
    this->m[1][1] = a11;
    this->m[1][2] = a12;
    this->m[1][3] = a13;

    this->m[2][0] = a20;
    this->m[2][1] = a21;
    this->m[2][2] = a22;
    this->m[2][3] = a23;

    this->m[3][0] = a30;
    this->m[3][1] = a31;
    this->m[3][2] = a32;
    this->m[3][3] = a33;
}

template <typename T>
inline Matrix44<T>::Matrix44(const Mtx33& mtx33, const Vec3& t, const Vec4& vw)
{
    Matrix44CalcCommon<T>::copy(*this, mtx33, t, vw);
}

template <typename T>
inline Matrix44<T>::Matrix44(const Mtx34& mtx34, const Vec4& vw)
{
    Matrix44CalcCommon<T>::copy(*this, mtx34, vw);
}

template <typename T>
inline T Matrix44<T>::operator()(s32 i, s32 j) const
{
    return this->m[i][j];
}

template <typename T>
inline T& Matrix44<T>::operator()(s32 i, s32 j)
{
    return this->m[i][j];
}

template <typename T>
inline Matrix44<T>& Matrix44<T>::operator=(const Self& n)
{
    Matrix44CalcCommon<T>::copy(*this, n);
    return *this;
}

template <typename T>
inline void Matrix44<T>::makeIdentity()
{
    Matrix44CalcCommon<T>::makeIdentity();
}

template <typename T>
inline void Matrix44<T>::makeZero()
{
    Matrix44CalcCommon<T>::makeZero();
}

template <typename T>
inline void Matrix44<T>::setInverse(const Self& n)
{
    Matrix44CalcCommon<T>::inverse(*this, n);
}

template <typename T>
inline void Matrix44<T>::setMul(const Self& a, const Self& b)
{
    Matrix44CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix44<T>::setMul(const Mtx34& a, const Self& b)
{
    Matrix44CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix44<T>::setMul(const Self& a, const Mtx34& b)
{
    Matrix44CalcCommon<T>::multiply(*this, a, b);
}

template <typename T>
inline void Matrix44<T>::setTranspose(const Self& n)
{
    Matrix44CalcCommon<T>::transposeTo(*this, n);
}

template <typename T>
inline void Matrix44<T>::transpose()
{
    Matrix44CalcCommon<T>::transpose(*this);
}

template <typename T>
inline void Matrix44<T>::fromQuat(const Quat<T>& q)
{
    Matrix44CalcCommon<T>::makeQ(*this, q);
}

template <typename T>
inline void Matrix44<T>::makeR(const Vec3& r)
{
    Matrix44CalcCommon<T>::makeR(*this, r);
}

template <typename T>
inline void Matrix44<T>::makeRIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix44CalcCommon<T>::makeRIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix44<T>::makeRzxyIdx(u32 xr, u32 yr, u32 zr)
{
    Matrix44CalcCommon<T>::makeRzxyIdx(*this, xr, yr, zr);
}

template <typename T>
inline void Matrix44<T>::toQuat(Quat<T>& q) const
{
    Matrix44CalcCommon<T>::toQuat(q, *this);
}

template <typename T>
inline void Matrix44<T>::getCol(Vec4& o, s32 axis) const
{
    Matrix44CalcCommon<T>::getCol(o, *this, axis);
}

template <typename T>
inline void Matrix44<T>::getRow(Vec4& o, s32 row) const
{
    Matrix44CalcCommon<T>::getRow(o, *this, row);
}

template <typename T>
inline void Matrix44<T>::scaleAllElements(T s)
{
    Matrix44CalcCommon<T>::scaleAllElements(*this, s);
}

template <typename T>
inline void Matrix44<T>::scaleBases(T sx, T sy, T sz, T sw)
{
    Matrix44CalcCommon<T>::scaleBases(*this, sx, sy, sz, sw);
}

template <typename T>
inline void Matrix44<T>::setCol(s32 axis, const Vec4& v)
{
    Matrix44CalcCommon<T>::setCol(*this, axis, v);
}

template <typename T>
inline void Matrix44<T>::setRow(s32 row, const Vec4& v)
{
    Matrix44CalcCommon<T>::setRow(*this, row, v);
}

}  // namespace sead
