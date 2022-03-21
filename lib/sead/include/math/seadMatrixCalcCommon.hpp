#pragma once

#ifdef cafe
#include <cafe.h>
#endif  // cafe

#ifdef __aarch64__
// For Matrix34CalcCommon<f32>::copy (access FP/SIMD registers: Q0, ...)
#include <arm_neon.h>
#endif

#include <cmath>

#include <math/seadMathCalcCommon.h>
#ifndef SEAD_MATH_MATRIX_CALC_COMMON_H_
#include <math/seadMatrixCalcCommon.h>
#endif

namespace sead
{
template <typename T>
void Matrix22CalcCommon<T>::makeIdentity(Base& o)
{
    o.m[0][0] = 1;
    o.m[0][1] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 1;
}

template <typename T>
void Matrix22CalcCommon<T>::makeZero(Base& o)
{
    o.m[0][0] = 0;
    o.m[0][1] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 0;
}

template <typename T>
void Matrix22CalcCommon<T>::copy(Base& o, const Base& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
}

template <typename T>
void Matrix22CalcCommon<T>::inverse(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];

    T det = a11 * a22 - a12 * a21;
    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    o.m[0][0] = a22 * det;
    o.m[0][1] = -a12 * det;

    o.m[1][0] = -a21 * det;
    o.m[1][1] = a11 * det;
}

template <typename T>
void Matrix22CalcCommon<T>::inverseTranspose(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];

    T det = a11 * a22 - a12 * a21;
    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    o.m[0][0] = a22 * det;
    o.m[0][1] = -a21 * det;

    o.m[1][0] = -a12 * det;
    o.m[1][1] = a11 * det;
}

template <typename T>
void Matrix22CalcCommon<T>::multiply(Base& o, const Base& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];

    o.m[0][0] = a11 * b11 + a12 * b21;
    o.m[0][1] = a11 * b12 + a12 * b22;

    o.m[1][0] = a21 * b11 + a22 * b21;
    o.m[1][1] = a21 * b12 + a22 * b22;
}

template <typename T>
void Matrix22CalcCommon<T>::transpose(Base& o)
{
    const T a12 = o.m[0][1];
    const T a21 = o.m[1][0];

    o.m[0][1] = a21;
    o.m[1][0] = a12;
}

template <typename T>
void Matrix22CalcCommon<T>::transposeTo(Base& o, const Base& n)
{
    SEAD_ASSERT(&o != &n);

    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[1][0];

    o.m[1][0] = n.m[0][1];
    o.m[1][1] = n.m[1][1];
}

template <typename T>
void Matrix33CalcCommon<T>::makeIdentity(Base& o)
{
    o.m[0][0] = 1;
    o.m[0][1] = 0;
    o.m[0][2] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 1;
    o.m[1][2] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 1;
}

template <typename T>
void Matrix33CalcCommon<T>::makeZero(Base& o)
{
    o.m[0][0] = 0;
    o.m[0][1] = 0;
    o.m[0][2] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 0;
    o.m[1][2] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 0;
}

template <typename T>
void Matrix33CalcCommon<T>::copy(Base& o, const Base& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
}

template <typename T>
void Matrix33CalcCommon<T>::copy(Base& o, const Mtx34& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
}

template <typename T>
void Matrix33CalcCommon<T>::inverse(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    T det = (a11 * a22 * a33 - a31 * a22 * a13) + (a12 * a23 * a31 - a21 * a12 * a33) +
            (a13 * a21 * a32 - a11 * a32 * a23);

    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    o.m[0][0] = (a22 * a33 - a32 * a23) * det;
    o.m[0][1] = (a32 * a13 - a12 * a33) * det;
    o.m[0][2] = (a12 * a23 - a22 * a13) * det;

    o.m[1][0] = (a31 * a23 - a21 * a33) * det;
    o.m[1][1] = (a11 * a33 - a31 * a13) * det;
    o.m[1][2] = (a21 * a13 - a11 * a23) * det;

    o.m[2][0] = (a21 * a32 - a31 * a22) * det;
    o.m[2][1] = (a31 * a12 - a11 * a32) * det;
    o.m[2][2] = (a11 * a22 - a21 * a12) * det;
}

template <typename T>
void Matrix33CalcCommon<T>::inverseTranspose(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    T det = (a11 * a22 * a33 - a31 * a22 * a13) + (a12 * a23 * a31 - a21 * a12 * a33) +
            (a13 * a21 * a32 - a11 * a32 * a23);

    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    o.m[0][0] = (a22 * a33 - a32 * a23) * det;
    o.m[0][1] = (a31 * a23 - a21 * a33) * det;
    o.m[0][2] = (a21 * a32 - a31 * a22) * det;

    o.m[1][0] = (a32 * a13 - a12 * a33) * det;
    o.m[1][1] = (a11 * a33 - a31 * a13) * det;
    o.m[1][2] = (a31 * a12 - a11 * a32) * det;

    o.m[2][0] = (a12 * a23 - a22 * a13) * det;
    o.m[2][1] = (a21 * a13 - a11 * a23) * det;
    o.m[2][2] = (a11 * a22 - a21 * a12) * det;
}

template <typename T>
void Matrix33CalcCommon<T>::multiply(Base& o, const Base& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
}

template <typename T>
void Matrix33CalcCommon<T>::multiply(Base& o, const Mtx34& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
}

template <typename T>
void Matrix33CalcCommon<T>::multiply(Base& o, const Base& a, const Mtx34& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
}

template <typename T>
void Matrix33CalcCommon<T>::transpose(Base& o)
{
    const T a12 = o.m[0][1];
    const T a13 = o.m[0][2];

    const T a21 = o.m[1][0];
    const T a23 = o.m[1][2];

    const T a31 = o.m[2][0];
    const T a32 = o.m[2][1];

    o.m[0][1] = a21;
    o.m[0][2] = a31;

    o.m[1][0] = a12;
    o.m[1][2] = a32;

    o.m[2][0] = a13;
    o.m[2][1] = a23;
}

template <typename T>
void Matrix33CalcCommon<T>::transposeTo(Base& o, const Base& n)
{
    SEAD_ASSERT(&o != &n);

    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[1][0];
    o.m[0][2] = n.m[2][0];

    o.m[1][0] = n.m[0][1];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[2][1];

    o.m[2][0] = n.m[0][2];
    o.m[2][1] = n.m[1][2];
    o.m[2][2] = n.m[2][2];
}

template <typename T>
void Matrix33CalcCommon<T>::makeQ(Base& o, const Quat& q)
{
    // Assuming the quaternion "q" is normalized

    const T yy = 2 * q.y * q.y;
    const T zz = 2 * q.z * q.z;
    const T xx = 2 * q.x * q.x;
    const T xy = 2 * q.x * q.y;
    const T xz = 2 * q.x * q.z;
    const T yz = 2 * q.y * q.z;
    const T wz = 2 * q.w * q.z;
    const T wx = 2 * q.w * q.x;
    const T wy = 2 * q.w * q.y;

    o.m[0][0] = 1 - yy - zz;
    o.m[0][1] = xy - wz;
    o.m[0][2] = xz + wy;

    o.m[1][0] = xy + wz;
    o.m[1][1] = 1 - xx - zz;
    o.m[1][2] = yz - wx;

    o.m[2][0] = xz - wy;
    o.m[2][1] = yz + wx;
    o.m[2][2] = 1 - xx - yy;
}

template <typename T>
void Matrix33CalcCommon<T>::makeR(Base& o, const Vec3& r)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);
}

template <typename T>
void Matrix33CalcCommon<T>::makeRIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);
}

template <typename T>
void Matrix33CalcCommon<T>::makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[2][2] = (cosV[0] * cosV[1]);
    o.m[0][2] = (cosV[0] * sinV[1]);
    o.m[1][2] = -sinV[0];

    o.m[2][0] = (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = (cosV[0] * sinV[2]);

    o.m[2][1] = (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = (cosV[0] * cosV[2]);
}

template <typename T>
void Matrix33CalcCommon<T>::makeS(Base& o, const Vec3& s)
{
    o.m[0][0] = s.x;
    o.m[1][0] = 0;
    o.m[2][0] = 0;

    o.m[0][1] = 0;
    o.m[1][1] = s.y;
    o.m[2][1] = 0;

    o.m[0][2] = 0;
    o.m[1][2] = 0;
    o.m[2][2] = s.z;
}

template <typename T>
void Matrix33CalcCommon<T>::makeSR(Base& o, const Vec3& s, const Vec3& r)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);
}

template <typename T>
void Matrix33CalcCommon<T>::makeSRIdx(Base& o, const Vec3& s, const Vector3<u32>& r)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);
}

template <typename T>
void Matrix33CalcCommon<T>::makeSRzxyIdx(Base& o, const Vec3& s, const Vector3<u32>& r)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[2][2] = s.z * (cosV[0] * cosV[1]);
    o.m[0][2] = s.z * (cosV[0] * sinV[1]);
    o.m[1][2] = s.z * -sinV[0];

    o.m[2][0] = s.x * (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = s.x * (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = s.x * (cosV[0] * sinV[2]);

    o.m[2][1] = s.y * (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = s.y * (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = s.y * (cosV[0] * cosV[2]);
}

template <typename T>
void Matrix33CalcCommon<T>::toQuat(Quat& q, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    const T t = a11 + a22 + a33;
    T w, x, y, z;

    if (t > 0)
    {
        T s = MathCalcCommon<T>::sqrt(t + 1);

        w = s * 0.5f;

        // if (s != 0)
        s = 0.5f / s;

        x = (a32 - a23) * s;
        y = (a13 - a31) * s;
        z = (a21 - a12) * s;
    }
    else if (a22 > a11 && a33 <= a22)
    {
        T s = MathCalcCommon<T>::sqrt(a22 - (a33 + a11) + 1);

        y = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a13 - a31) * s;
        x = (a21 + a12) * s;
        z = (a23 + a32) * s;
    }
    else if (a22 > a11 || a33 > a11)
    {
        T s = MathCalcCommon<T>::sqrt(a33 - (a11 + a22) + 1);

        z = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a21 - a12) * s;
        x = (a31 + a13) * s;
        y = (a32 + a23) * s;
    }
    else
    {
        T s = MathCalcCommon<T>::sqrt(a11 - (a22 + a33) + 1);

        x = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a32 - a23) * s;
        y = (a12 + a21) * s;
        z = (a13 + a31) * s;
    }

    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeIdentity(Base& o)
{
    o.m[0][0] = 1;
    o.m[0][1] = 0;
    o.m[0][2] = 0;
    o.m[0][3] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 1;
    o.m[1][2] = 0;
    o.m[1][3] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 1;
    o.m[2][3] = 0;
}

#ifdef cafe

template <>
inline void Matrix34CalcCommon<f32>::makeIdentity(Base& o)
{
    ASM_MTXIdentity(o.m);
}

#endif  // cafe

template <typename T>
void Matrix34CalcCommon<T>::makeZero(Base& o)
{
    o.m[0][0] = 0;
    o.m[0][1] = 0;
    o.m[0][2] = 0;
    o.m[0][3] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 0;
    o.m[1][2] = 0;
    o.m[1][3] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::copy(Base& o, const Base& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = n.m[0][3];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = n.m[1][3];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = n.m[2][3];
}

#ifdef __aarch64__

template <>
inline void Matrix34CalcCommon<f32>::copy(Base& o, const Base& n)
{
    for (int i = 0; i < 3; ++i)
    {
        vst1q_f32(o.m[i], vld1q_f32(n.m[i]));
    }
}

#endif

#ifdef cafe

template <>
inline void Matrix34CalcCommon<f32>::copy(Base& o, const Base& n)
{
    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);
}

#endif  // cafe

template <typename T>
void Matrix34CalcCommon<T>::copy(Base& o, const Mtx33& n, const Vec3& t)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = t.x;

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = t.y;

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::copy(Base& o, const Mtx44& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = n.m[0][3];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = n.m[1][3];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = n.m[2][3];
}

#ifdef cafe

// Nintendo did not actually use this for the cafe f32 specialization
//
// template <>
// inline void
// Matrix34CalcCommon<f32>::copy(Base& o, const Mtx44& n)
//{
//    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);
//}

#endif  // cafe

template <typename T>
bool Matrix34CalcCommon<T>::inverse(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];
    const T a14 = n.m[0][3];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];
    const T a24 = n.m[1][3];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];
    const T a34 = n.m[2][3];

    T det = (a11 * a22 * a33 - a31 * a22 * a13) + (a12 * a23 * a31 - a21 * a12 * a33) +
            (a13 * a21 * a32 - a11 * a32 * a23);

    if (det == 0)
        return false;

    det = 1 / det;

    o.m[0][0] = (a22 * a33 - a32 * a23) * det;
    o.m[0][1] = (a32 * a13 - a12 * a33) * det;
    o.m[0][2] = (a12 * a23 - a22 * a13) * det;

    o.m[1][0] = (a31 * a23 - a21 * a33) * det;
    o.m[1][1] = (a11 * a33 - a31 * a13) * det;
    o.m[1][2] = (a21 * a13 - a11 * a23) * det;

    o.m[2][0] = (a21 * a32 - a31 * a22) * det;
    o.m[2][1] = (a31 * a12 - a11 * a32) * det;
    o.m[2][2] = (a11 * a22 - a21 * a12) * det;

    o.m[0][3] = o.m[0][0] * -a14 + o.m[0][1] * -a24 + o.m[0][2] * -a34;
    o.m[1][3] = o.m[1][0] * -a14 + o.m[1][1] * -a24 + o.m[1][2] * -a34;
    o.m[2][3] = o.m[2][0] * -a14 + o.m[2][1] * -a24 + o.m[2][2] * -a34;

    return true;
}

template <typename T>
bool Matrix34CalcCommon<T>::inverse33(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    T det = (a11 * a22 * a33 - a31 * a22 * a13) + (a12 * a23 * a31 - a21 * a12 * a33) +
            (a13 * a21 * a32 - a11 * a32 * a23);

    if (det == 0)
        return false;

    det = 1 / det;

    o.m[0][0] = (a22 * a33 - a32 * a23) * det;
    o.m[0][1] = (a32 * a13 - a12 * a33) * det;
    o.m[0][2] = (a12 * a23 - a22 * a13) * det;

    o.m[1][0] = (a31 * a23 - a21 * a33) * det;
    o.m[1][1] = (a11 * a33 - a31 * a13) * det;
    o.m[1][2] = (a21 * a13 - a11 * a23) * det;

    o.m[2][0] = (a21 * a32 - a31 * a22) * det;
    o.m[2][1] = (a31 * a12 - a11 * a32) * det;
    o.m[2][2] = (a11 * a22 - a21 * a12) * det;

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    return true;
}

template <typename T>
bool Matrix34CalcCommon<T>::inverseTranspose(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    T det = (a11 * a22 * a33 - a31 * a22 * a13) + (a12 * a23 * a31 - a21 * a12 * a33) +
            (a13 * a21 * a32 - a11 * a32 * a23);

    if (det == 0)
        return false;

    det = 1 / det;

    o.m[0][0] = (a22 * a33 - a32 * a23) * det;
    o.m[0][1] = (a31 * a23 - a21 * a33) * det;
    o.m[0][2] = (a21 * a32 - a31 * a22) * det;

    o.m[1][0] = (a32 * a13 - a12 * a33) * det;
    o.m[1][1] = (a11 * a33 - a31 * a13) * det;
    o.m[1][2] = (a31 * a12 - a11 * a32) * det;

    o.m[2][0] = (a12 * a23 - a22 * a13) * det;
    o.m[2][1] = (a21 * a13 - a11 * a23) * det;
    o.m[2][2] = (a11 * a22 - a21 * a12) * det;

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    return true;
}

template <typename T>
void Matrix34CalcCommon<T>::multiply(Base& o, const Base& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];
    const T a14 = a.m[0][3];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];
    const T a24 = a.m[1][3];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];
    const T a34 = a.m[2][3];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];
    const T b14 = b.m[0][3];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];
    const T b24 = b.m[1][3];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];
    const T b34 = b.m[2][3];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
    o.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
    o.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
    o.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34;
}

#ifdef cafe

template <>
inline void Matrix34CalcCommon<f32>::multiply(Base& o, const Base& a, const Base& b)
{
    ASM_MTXConcat(const_cast<f32(*)[4]>(a.m), const_cast<f32(*)[4]>(b.m), o.m);
}

#endif  // cafe

template <typename T>
void Matrix34CalcCommon<T>::multiply(Base& o, const Mtx33& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];
    const T b14 = b.m[0][3];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];
    const T b24 = b.m[1][3];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];
    const T b34 = b.m[2][3];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
    o.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
    o.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
    o.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34;
}

template <typename T>
void Matrix34CalcCommon<T>::multiply(Base& o, const Base& a, const Mtx33& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];
    const T a14 = a.m[0][3];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];
    const T a24 = a.m[1][3];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];
    const T a34 = a.m[2][3];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
    o.m[0][3] = a14;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
    o.m[1][3] = a24;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
    o.m[2][3] = a34;
}

template <typename T>
void Matrix34CalcCommon<T>::transpose(Base& o)
{
    const T a12 = o.m[0][1];
    const T a13 = o.m[0][2];

    const T a21 = o.m[1][0];
    const T a23 = o.m[1][2];

    const T a31 = o.m[2][0];
    const T a32 = o.m[2][1];

    o.m[0][1] = a21;
    o.m[0][2] = a31;
    o.m[0][3] = 0;

    o.m[1][0] = a12;
    o.m[1][2] = a32;
    o.m[1][3] = 0;

    o.m[2][0] = a13;
    o.m[2][1] = a23;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::transposeTo(Base& o, const Base& n)
{
    SEAD_ASSERT(&o != &n);

    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[1][0];
    o.m[0][2] = n.m[2][0];
    o.m[0][3] = 0;

    o.m[1][0] = n.m[0][1];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[2][1];
    o.m[1][3] = 0;

    o.m[2][0] = n.m[0][2];
    o.m[2][1] = n.m[1][2];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = 0;
}

#ifdef cafe

// Nintendo did not actually use this for the cafe f32 specialization
//
// template <>
// inline void
// Matrix34CalcCommon<f32>::transposeTo(Base& o, const Base& n)
//{
//    ASM_MTXTranspose(const_cast<f32(*)[4]>(n.m), o.m);
//}

#endif  // cafe

template <typename T>
void Matrix34CalcCommon<T>::makeQ(Base& o, const Quat& q)
{
    // Assuming the quaternion "q" is normalized

    const T yy = 2 * q.y * q.y;
    const T zz = 2 * q.z * q.z;
    const T xx = 2 * q.x * q.x;
    const T xy = 2 * q.x * q.y;
    const T xz = 2 * q.x * q.z;
    const T yz = 2 * q.y * q.z;
    const T wz = 2 * q.w * q.z;
    const T wx = 2 * q.w * q.x;
    const T wy = 2 * q.w * q.y;

    o.m[0][0] = 1 - yy - zz;
    o.m[0][1] = xy - wz;
    o.m[0][2] = xz + wy;

    o.m[1][0] = xy + wz;
    o.m[1][1] = 1 - xx - zz;
    o.m[1][2] = yz - wx;

    o.m[2][0] = xz - wy;
    o.m[2][1] = yz + wx;
    o.m[2][2] = 1 - xx - yy;

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeQT(Base& o, const Quat& q, const Vec3& t)
{
    // Assuming the quaternion "q" is normalized

    const T yy = 2 * q.y * q.y;
    const T zz = 2 * q.z * q.z;
    const T xx = 2 * q.x * q.x;
    const T xy = 2 * q.x * q.y;
    const T xz = 2 * q.x * q.z;
    const T yz = 2 * q.y * q.z;
    const T wz = 2 * q.w * q.z;
    const T wx = 2 * q.w * q.x;
    const T wy = 2 * q.w * q.y;

    o.m[0][0] = 1 - yy - zz;
    o.m[0][1] = xy - wz;
    o.m[0][2] = xz + wy;

    o.m[1][0] = xy + wz;
    o.m[1][1] = 1 - xx - zz;
    o.m[1][2] = yz - wx;

    o.m[2][0] = xz - wy;
    o.m[2][1] = yz + wx;
    o.m[2][2] = 1 - xx - yy;

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeR(Base& o, const Vec3& r)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeRIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
inline void Matrix34CalcCommon<T>::makeRT(Base& o, const Vec3& r, const Vec3& t)
{
    const T sinV[3] = {std::sin(r.x), std::sin(r.y), std::sin(r.z)};

    const T cosV[3] = {std::cos(r.x), std::cos(r.y), std::cos(r.z)};

    T s0_s1 = sinV[0] * sinV[1];
    T c0_s2 = cosV[0] * sinV[2];
    T c0_c2 = cosV[0] * cosV[2];

    o.m[0][0] = cosV[1] * cosV[2];
    o.m[1][0] = cosV[1] * sinV[2];
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (s0_s1 * cosV[2]) - c0_s2;
    o.m[1][1] = (s0_s1 * sinV[2]) + c0_c2;
    o.m[2][1] = sinV[0] * cosV[1];

    o.m[0][2] = (c0_c2 * sinV[1]) + (sinV[0] * sinV[2]);
    o.m[1][2] = (c0_s2 * sinV[1]) - (sinV[0] * cosV[2]);
    o.m[2][2] = cosV[0] * cosV[1];

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeRTIdx(Base& o, const Vector3<u32>& r, const Vec3& t)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[2][2] = (cosV[0] * cosV[1]);
    o.m[0][2] = (cosV[0] * sinV[1]);
    o.m[1][2] = -sinV[0];

    o.m[2][0] = (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = (cosV[0] * sinV[2]);

    o.m[2][1] = (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = (cosV[0] * cosV[2]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeRzxyTIdx(Base& o, const Vector3<u32>& r, const Vec3& t)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[2][2] = (cosV[0] * cosV[1]);
    o.m[0][2] = (cosV[0] * sinV[1]);
    o.m[1][2] = -sinV[0];

    o.m[2][0] = (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = (cosV[0] * sinV[2]);

    o.m[2][1] = (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = (cosV[0] * cosV[2]);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeS(Base& o, const Vec3& s)
{
    o.m[0][0] = s.x;
    o.m[1][0] = 0;
    o.m[2][0] = 0;

    o.m[0][1] = 0;
    o.m[1][1] = s.y;
    o.m[2][1] = 0;

    o.m[0][2] = 0;
    o.m[1][2] = 0;
    o.m[2][2] = s.z;

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

#ifdef cafe

template <>
inline void Matrix34CalcCommon<f32>::makeS(Base& o, const Vec3& s)
{
    ASM_MTXScale(o.m, s.x, s.y, s.z);
}

#endif  // cafe

template <typename T>
void Matrix34CalcCommon<T>::makeSR(Base& o, const Vec3& s, const Vec3& r)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeSRIdx(Base& o, const Vec3& s, const Vector3<u32>& r)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeSRT(Base& o, const Vec3& s, const Vec3& r, const Vec3& t)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeSRTIdx(Base& o, const Vec3& s, const Vector3<u32>& r, const Vec3& t)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[0][0] = s.x * (cosV[1] * cosV[2]);
    o.m[1][0] = s.x * (cosV[1] * sinV[2]);
    o.m[2][0] = s.x * -sinV[1];

    o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = s.y * (sinV[0] * cosV[1]);

    o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = s.z * (cosV[0] * cosV[1]);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeSRzxyIdx(Base& o, const Vec3& s, const Vector3<u32>& r)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[2][2] = s.z * (cosV[0] * cosV[1]);
    o.m[0][2] = s.z * (cosV[0] * sinV[1]);
    o.m[1][2] = s.z * -sinV[0];

    o.m[2][0] = s.x * (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = s.x * (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = s.x * (cosV[0] * sinV[2]);

    o.m[2][1] = s.y * (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = s.y * (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = s.y * (cosV[0] * cosV[2]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;
}

template <typename T>
void Matrix34CalcCommon<T>::makeSRzxyTIdx(Base& o, const Vec3& s, const Vector3<u32>& r,
                                          const Vec3& t)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

    o.m[2][2] = s.z * (cosV[0] * cosV[1]);
    o.m[0][2] = s.z * (cosV[0] * sinV[1]);
    o.m[1][2] = s.z * -sinV[0];

    o.m[2][0] = s.x * (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = s.x * (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = s.x * (cosV[0] * sinV[2]);

    o.m[2][1] = s.y * (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = s.y * (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = s.y * (cosV[0] * cosV[2]);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeST(Base& o, const Vec3& s, const Vec3& t)
{
    o.m[0][0] = s.x;
    o.m[1][0] = 0;
    o.m[2][0] = 0;

    o.m[0][1] = 0;
    o.m[1][1] = s.y;
    o.m[2][1] = 0;

    o.m[0][2] = 0;
    o.m[1][2] = 0;
    o.m[2][2] = s.z;

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::makeT(Base& o, const Vec3& t)
{
    o.m[0][0] = 1;
    o.m[1][0] = 0;
    o.m[2][0] = 0;

    o.m[0][1] = 0;
    o.m[1][1] = 1;
    o.m[2][1] = 0;

    o.m[0][2] = 0;
    o.m[1][2] = 0;
    o.m[2][2] = 1;

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

template <typename T>
void Matrix34CalcCommon<T>::toQuat(Quat& q, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    const T t = a11 + a22 + a33;
    T w, x, y, z;

    if (t > 0)
    {
        T s = MathCalcCommon<T>::sqrt(t + 1);

        w = s * 0.5f;

        // if (s != 0)
        s = 0.5f / s;

        x = (a32 - a23) * s;
        y = (a13 - a31) * s;
        z = (a21 - a12) * s;
    }
    else if (a22 > a11 && a33 <= a22)
    {
        T s = MathCalcCommon<T>::sqrt(a22 - (a33 + a11) + 1);

        y = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a13 - a31) * s;
        x = (a21 + a12) * s;
        z = (a23 + a32) * s;
    }
    else if (a22 > a11 || a33 > a11)
    {
        T s = MathCalcCommon<T>::sqrt(a33 - (a11 + a22) + 1);

        z = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a21 - a12) * s;
        x = (a31 + a13) * s;
        y = (a32 + a23) * s;
    }
    else
    {
        T s = MathCalcCommon<T>::sqrt(a11 - (a22 + a33) + 1);

        x = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a32 - a23) * s;
        y = (a12 + a21) * s;
        z = (a13 + a31) * s;
    }

    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
}

template <typename T>
void Matrix34CalcCommon<T>::getBase(Vec3& v, const Base& n, s32 axis)
{
    v.x = n.m[0][axis];
    v.y = n.m[1][axis];
    v.z = n.m[2][axis];
}

template <typename T>
void Matrix34CalcCommon<T>::getRow(Vec4& v, const Base& n, s32 row)
{
    v.x = n.m[row][0];
    v.y = n.m[row][1];
    v.z = n.m[row][2];
    v.w = n.m[row][3];
}

template <typename T>
void Matrix34CalcCommon<T>::getTranslation(Vec3& v, const Base& n)
{
    getBase(v, n, 3);
}

template <typename T>
void Matrix34CalcCommon<T>::getRotation(Vec3& v, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    T abs = MathCalcCommon<T>::abs(a31);
    // making sure pitch stays within bounds, setting roll to 0 otherwise
    if ((1.0f - abs) < MathCalcCommon<T>::epsilon() * 10)
    {
        v.x = 0.0f;
        v.y = (a31 / abs) * (-numbers::pi_v<T> / 2);
        v.z = std::atan2(-a12, -(a31 * a13));
    }
    else
    {
        v.x = std::atan2(a32, a33);
        v.y = std::asin(-a31);
        v.z = std::atan2(a21, a11);
    }
}

template <typename T>
void Matrix34CalcCommon<T>::scaleAllElements(Base& n, T s)
{
    n.m[0][0] *= s;
    n.m[0][1] *= s;
    n.m[0][2] *= s;
    n.m[0][3] *= s;

    n.m[1][0] *= s;
    n.m[1][1] *= s;
    n.m[1][2] *= s;
    n.m[1][3] *= s;

    n.m[2][0] *= s;
    n.m[2][1] *= s;
    n.m[2][2] *= s;
    n.m[2][3] *= s;
}

template <typename T>
void Matrix34CalcCommon<T>::scaleBases(Base& n, T sx, T sy, T sz)
{
    n.m[0][0] *= sx;
    n.m[1][0] *= sx;
    n.m[2][0] *= sx;

    n.m[0][1] *= sy;
    n.m[1][1] *= sy;
    n.m[2][1] *= sy;

    n.m[0][2] *= sz;
    n.m[1][2] *= sz;
    n.m[2][2] *= sz;
}

template <typename T>
void Matrix34CalcCommon<T>::setBase(Base& n, s32 axis, const Vec3& v)
{
    n.m[0][axis] = v.x;
    n.m[1][axis] = v.y;
    n.m[2][axis] = v.z;
}

template <typename T>
void Matrix34CalcCommon<T>::setRow(Base& n, const Vec4& v, s32 row)
{
    n.m[row][0] = v.x;
    n.m[row][1] = v.y;
    n.m[row][2] = v.z;
    n.m[row][3] = v.w;
}

template <typename T>
void Matrix34CalcCommon<T>::setTranslation(Base& n, const Vec3& v)
{
    setBase(n, 3, v);
}

template <typename T>
void Matrix44CalcCommon<T>::makeIdentity(Base& o)
{
    o.m[0][0] = 1;
    o.m[0][1] = 0;
    o.m[0][2] = 0;
    o.m[0][3] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 1;
    o.m[1][2] = 0;
    o.m[1][3] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 1;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 1;
}

#ifdef cafe

template <>
inline void Matrix44CalcCommon<f32>::makeIdentity(Base& o)
{
    ASM_MTX44Identity(o.m);
}

#endif  // cafe

template <typename T>
void Matrix44CalcCommon<T>::makeZero(Base& o)
{
    o.m[0][0] = 0;
    o.m[0][1] = 0;
    o.m[0][2] = 0;
    o.m[0][3] = 0;

    o.m[1][0] = 0;
    o.m[1][1] = 0;
    o.m[1][2] = 0;
    o.m[1][3] = 0;

    o.m[2][0] = 0;
    o.m[2][1] = 0;
    o.m[2][2] = 0;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 0;
}

template <typename T>
void Matrix44CalcCommon<T>::copy(Base& o, const Base& n)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = n.m[0][3];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = n.m[1][3];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = n.m[2][3];

    o.m[3][0] = n.m[3][0];
    o.m[3][1] = n.m[3][1];
    o.m[3][2] = n.m[3][2];
    o.m[3][3] = n.m[3][3];
}

#ifdef cafe

template <>
inline void Matrix44CalcCommon<f32>::copy(Base& o, const Base& n)
{
    ASM_MTX44Copy(const_cast<f32(*)[4]>(n.m), o.m);
}

#endif  // cafe

template <typename T>
void Matrix44CalcCommon<T>::copy(Base& o, const Mtx33& n, const Vec3& t, const Vec4& v)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = t.x;

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = t.y;

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = t.z;

    o.m[3][0] = v.x;
    o.m[3][1] = v.y;
    o.m[3][2] = v.z;
    o.m[3][3] = v.w;
}

template <typename T>
void Matrix44CalcCommon<T>::copy(Base& o, const Mtx34& n, const Vec4& v)
{
    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[0][1];
    o.m[0][2] = n.m[0][2];
    o.m[0][3] = n.m[0][3];

    o.m[1][0] = n.m[1][0];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[1][2];
    o.m[1][3] = n.m[1][3];

    o.m[2][0] = n.m[2][0];
    o.m[2][1] = n.m[2][1];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = n.m[2][3];

    o.m[3][0] = v.x;
    o.m[3][1] = v.y;
    o.m[3][2] = v.z;
    o.m[3][3] = v.w;
}

#ifdef cafe

// Nintendo did not actually use this for the cafe f32 specialization
//
// template <>
// inline void
// Matrix44CalcCommon<f32>::copy(Base& o, const Mtx34& n, const Vec4& v)
//{
//    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);
//
//    o.m[3][0] = v.x;
//    o.m[3][1] = v.y;
//    o.m[3][2] = v.z;
//    o.m[3][3] = v.w;
//}

#endif  // cafe

template <typename T>
void Matrix44CalcCommon<T>::inverse(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];
    const T a14 = n.m[0][3];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];
    const T a24 = n.m[1][3];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];
    const T a34 = n.m[2][3];

    const T a41 = n.m[3][0];
    const T a42 = n.m[3][1];
    const T a43 = n.m[3][2];
    const T a44 = n.m[3][3];

    T det = a11 * (a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43) +
            a12 * (a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41) +
            a13 * (a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42) +
            a14 * (a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41) -
            a11 * (a22 * a34 * a43 + a23 * a32 * a44 + a24 * a33 * a42) -
            a12 * (a21 * a33 * a44 + a23 * a34 * a41 + a24 * a31 * a43) -
            a13 * (a21 * a34 * a42 + a22 * a31 * a44 + a24 * a32 * a41) -
            a14 * (a21 * a32 * a43 + a22 * a33 * a41 + a23 * a31 * a42);

    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    const T a33xa44_a34xa43 = a33 * a44 - a34 * a43;
    const T a32xa44_a34xa42 = a32 * a44 - a34 * a42;
    const T a33xa42_a32xa43 = a33 * a42 - a32 * a43;
    const T a33xa41_a31xa43 = a33 * a41 - a31 * a43;
    const T a31xa44_a34xa41 = a31 * a44 - a34 * a41;
    const T a32xa41_a31xa42 = a32 * a41 - a31 * a42;
    const T a23xa44_a24xa43 = a23 * a44 - a24 * a43;
    const T a24xa33_a23xa34 = a24 * a33 - a23 * a34;
    const T a24xa42_a22xa44 = a24 * a42 - a22 * a44;
    const T a22xa43_a23xa42 = a22 * a43 - a23 * a42;
    const T a22xa34_a24xa32 = a22 * a34 - a24 * a32;
    const T a23xa32_a22xa33 = a23 * a32 - a22 * a33;
    const T a21xa44_a24xa41 = a21 * a44 - a24 * a41;
    const T a23xa41_a21xa43 = a23 * a41 - a21 * a43;
    const T a24xa31_a21xa34 = a24 * a31 - a21 * a34;
    const T a21xa33_a23xa31 = a21 * a33 - a23 * a31;
    const T a21xa42_a22xa41 = a21 * a42 - a22 * a41;
    const T a22xa31_a21xa32 = a22 * a31 - a21 * a32;

    o.m[0][0] = (a22 * a33xa44_a34xa43 - a23 * a32xa44_a34xa42 - a24 * a33xa42_a32xa43) * det;
    o.m[0][1] = (a13 * a32xa44_a34xa42 + a14 * a33xa42_a32xa43 - a12 * a33xa44_a34xa43) * det;
    o.m[0][2] = (a12 * a23xa44_a24xa43 + a13 * a24xa42_a22xa44 + a14 * a22xa43_a23xa42) * det;
    o.m[0][3] = (a12 * a24xa33_a23xa34 + a13 * a22xa34_a24xa32 + a14 * a23xa32_a22xa33) * det;

    o.m[1][0] = (a23 * a31xa44_a34xa41 + a24 * a33xa41_a31xa43 - a21 * a33xa44_a34xa43) * det;
    o.m[1][1] = (a11 * a33xa44_a34xa43 - a13 * a31xa44_a34xa41 - a14 * a33xa41_a31xa43) * det;
    o.m[1][2] = (a13 * a21xa44_a24xa41 + a14 * a23xa41_a21xa43 - a11 * a23xa44_a24xa43) * det;
    o.m[1][3] = (a13 * a24xa31_a21xa34 + a14 * a21xa33_a23xa31 - a11 * a24xa33_a23xa34) * det;

    o.m[2][0] = (a21 * a32xa44_a34xa42 - a22 * a31xa44_a34xa41 - a24 * a32xa41_a31xa42) * det;
    o.m[2][1] = (a12 * a31xa44_a34xa41 + a14 * a32xa41_a31xa42 - a11 * a32xa44_a34xa42) * det;
    o.m[2][2] = (a14 * a21xa42_a22xa41 - a11 * a24xa42_a22xa44 - a12 * a21xa44_a24xa41) * det;
    o.m[2][3] = (a14 * a22xa31_a21xa32 - a11 * a22xa34_a24xa32 - a12 * a24xa31_a21xa34) * det;

    o.m[3][0] = (a21 * a33xa42_a32xa43 - a22 * a33xa41_a31xa43 + a23 * a32xa41_a31xa42) * det;
    o.m[3][1] = (a12 * a33xa41_a31xa43 - a13 * a32xa41_a31xa42 - a11 * a33xa42_a32xa43) * det;
    o.m[3][2] = (-a13 * a21xa42_a22xa41 - a11 * a22xa43_a23xa42 - a12 * a23xa41_a21xa43) * det;
    o.m[3][3] = (-a13 * a22xa31_a21xa32 - a11 * a23xa32_a22xa33 - a12 * a21xa33_a23xa31) * det;
}

template <typename T>
void Matrix44CalcCommon<T>::inverseTranspose(Base& o, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];
    const T a14 = n.m[0][3];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];
    const T a24 = n.m[1][3];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];
    const T a34 = n.m[2][3];

    const T a41 = n.m[3][0];
    const T a42 = n.m[3][1];
    const T a43 = n.m[3][2];
    const T a44 = n.m[3][3];

    T det = a11 * (a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43) +
            a12 * (a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41) +
            a13 * (a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42) +
            a14 * (a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41) -
            a11 * (a22 * a34 * a43 + a23 * a32 * a44 + a24 * a33 * a42) -
            a12 * (a21 * a33 * a44 + a23 * a34 * a41 + a24 * a31 * a43) -
            a13 * (a21 * a34 * a42 + a22 * a31 * a44 + a24 * a32 * a41) -
            a14 * (a21 * a32 * a43 + a22 * a33 * a41 + a23 * a31 * a42);

    if (det == 0)
        return makeIdentity(o);

    det = 1 / det;

    const T a33xa44_a34xa43 = a33 * a44 - a34 * a43;
    const T a32xa44_a34xa42 = a32 * a44 - a34 * a42;
    const T a33xa42_a32xa43 = a33 * a42 - a32 * a43;
    const T a33xa41_a31xa43 = a33 * a41 - a31 * a43;
    const T a31xa44_a34xa41 = a31 * a44 - a34 * a41;
    const T a32xa41_a31xa42 = a32 * a41 - a31 * a42;
    const T a23xa44_a24xa43 = a23 * a44 - a24 * a43;
    const T a24xa33_a23xa34 = a24 * a33 - a23 * a34;
    const T a24xa42_a22xa44 = a24 * a42 - a22 * a44;
    const T a22xa43_a23xa42 = a22 * a43 - a23 * a42;
    const T a22xa34_a24xa32 = a22 * a34 - a24 * a32;
    const T a23xa32_a22xa33 = a23 * a32 - a22 * a33;
    const T a21xa44_a24xa41 = a21 * a44 - a24 * a41;
    const T a23xa41_a21xa43 = a23 * a41 - a21 * a43;
    const T a24xa31_a21xa34 = a24 * a31 - a21 * a34;
    const T a21xa33_a23xa31 = a21 * a33 - a23 * a31;
    const T a21xa42_a22xa41 = a21 * a42 - a22 * a41;
    const T a22xa31_a21xa32 = a22 * a31 - a21 * a32;

    o.m[0][0] = (a22 * a33xa44_a34xa43 - a23 * a32xa44_a34xa42 - a24 * a33xa42_a32xa43) * det;
    o.m[0][1] = (a23 * a31xa44_a34xa41 + a24 * a33xa41_a31xa43 - a21 * a33xa44_a34xa43) * det;
    o.m[0][2] = (a21 * a32xa44_a34xa42 - a22 * a31xa44_a34xa41 - a24 * a32xa41_a31xa42) * det;
    o.m[0][3] = (a21 * a33xa42_a32xa43 - a22 * a33xa41_a31xa43 + a23 * a32xa41_a31xa42) * det;

    o.m[1][0] = (a13 * a32xa44_a34xa42 + a14 * a33xa42_a32xa43 - a12 * a33xa44_a34xa43) * det;
    o.m[1][1] = (a11 * a33xa44_a34xa43 - a13 * a31xa44_a34xa41 - a14 * a33xa41_a31xa43) * det;
    o.m[1][2] = (a12 * a31xa44_a34xa41 + a14 * a32xa41_a31xa42 - a11 * a32xa44_a34xa42) * det;
    o.m[1][3] = (a12 * a33xa41_a31xa43 - a13 * a32xa41_a31xa42 - a11 * a33xa42_a32xa43) * det;

    o.m[2][0] = (a12 * a23xa44_a24xa43 + a13 * a24xa42_a22xa44 + a14 * a22xa43_a23xa42) * det;
    o.m[2][1] = (a13 * a21xa44_a24xa41 + a14 * a23xa41_a21xa43 - a11 * a23xa44_a24xa43) * det;
    o.m[2][2] = (a14 * a21xa42_a22xa41 - a11 * a24xa42_a22xa44 - a12 * a21xa44_a24xa41) * det;
    o.m[2][3] = (-a13 * a21xa42_a22xa41 - a11 * a22xa43_a23xa42 - a12 * a23xa41_a21xa43) * det;

    o.m[3][0] = (a12 * a24xa33_a23xa34 + a13 * a22xa34_a24xa32 + a14 * a23xa32_a22xa33) * det;
    o.m[3][1] = (a13 * a24xa31_a21xa34 + a14 * a21xa33_a23xa31 - a11 * a24xa33_a23xa34) * det;
    o.m[3][2] = (a14 * a22xa31_a21xa32 - a11 * a22xa34_a24xa32 - a12 * a24xa31_a21xa34) * det;
    o.m[3][3] = (-a13 * a22xa31_a21xa32 - a11 * a23xa32_a22xa33 - a12 * a21xa33_a23xa31) * det;
}

template <typename T>
void Matrix44CalcCommon<T>::multiply(Base& o, const Base& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];
    const T a14 = a.m[0][3];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];
    const T a24 = a.m[1][3];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];
    const T a34 = a.m[2][3];

    const T a41 = a.m[3][0];
    const T a42 = a.m[3][1];
    const T a43 = a.m[3][2];
    const T a44 = a.m[3][3];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];
    const T b14 = b.m[0][3];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];
    const T b24 = b.m[1][3];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];
    const T b34 = b.m[2][3];

    const T b41 = b.m[3][0];
    const T b42 = b.m[3][1];
    const T b43 = b.m[3][2];
    const T b44 = b.m[3][3];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
    o.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
    o.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
    o.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

    o.m[3][0] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
    o.m[3][1] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
    o.m[3][2] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
    o.m[3][3] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
}

#ifdef cafe

template <>
inline void Matrix44CalcCommon<f32>::multiply(Base& o, const Base& a, const Base& b)
{
    ASM_MTX44Concat(const_cast<f32(*)[4]>(a.m), const_cast<f32(*)[4]>(b.m), o.m);
}

#endif  // cafe

template <typename T>
void Matrix44CalcCommon<T>::multiply(Base& o, const Mtx34& a, const Base& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];
    const T a14 = a.m[0][3];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];
    const T a24 = a.m[1][3];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];
    const T a34 = a.m[2][3];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];
    const T b14 = b.m[0][3];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];
    const T b24 = b.m[1][3];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];
    const T b34 = b.m[2][3];

    const T b41 = b.m[3][0];
    const T b42 = b.m[3][1];
    const T b43 = b.m[3][2];
    const T b44 = b.m[3][3];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
    o.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
    o.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
    o.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

    o.m[3][0] = b41;
    o.m[3][1] = b42;
    o.m[3][2] = b43;
    o.m[3][3] = b44;
}

template <typename T>
void Matrix44CalcCommon<T>::multiply(Base& o, const Base& a, const Mtx34& b)
{
    const T a11 = a.m[0][0];
    const T a12 = a.m[0][1];
    const T a13 = a.m[0][2];
    const T a14 = a.m[0][3];

    const T a21 = a.m[1][0];
    const T a22 = a.m[1][1];
    const T a23 = a.m[1][2];
    const T a24 = a.m[1][3];

    const T a31 = a.m[2][0];
    const T a32 = a.m[2][1];
    const T a33 = a.m[2][2];
    const T a34 = a.m[2][3];

    const T a41 = a.m[3][0];
    const T a42 = a.m[3][1];
    const T a43 = a.m[3][2];
    const T a44 = a.m[3][3];

    const T b11 = b.m[0][0];
    const T b12 = b.m[0][1];
    const T b13 = b.m[0][2];
    const T b14 = b.m[0][3];

    const T b21 = b.m[1][0];
    const T b22 = b.m[1][1];
    const T b23 = b.m[1][2];
    const T b24 = b.m[1][3];

    const T b31 = b.m[2][0];
    const T b32 = b.m[2][1];
    const T b33 = b.m[2][2];
    const T b34 = b.m[2][3];

    o.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
    o.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
    o.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
    o.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14;

    o.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
    o.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
    o.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
    o.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24;

    o.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
    o.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
    o.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
    o.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

    o.m[3][0] = a41 * b11 + a42 * b21 + a43 * b31;
    o.m[3][1] = a41 * b12 + a42 * b22 + a43 * b32;
    o.m[3][2] = a41 * b13 + a42 * b23 + a43 * b33;
    o.m[3][3] = a41 * b14 + a42 * b24 + a43 * b34 + a44;
}

template <typename T>
void Matrix44CalcCommon<T>::transpose(Base& o)
{
    const T a12 = o.m[0][1];
    const T a13 = o.m[0][2];
    const T a14 = o.m[0][3];

    const T a21 = o.m[1][0];
    const T a23 = o.m[1][2];
    const T a24 = o.m[1][3];

    const T a31 = o.m[2][0];
    const T a32 = o.m[2][1];
    const T a34 = o.m[2][3];

    const T a41 = o.m[3][0];
    const T a42 = o.m[3][1];
    const T a43 = o.m[3][2];

    o.m[0][1] = a21;
    o.m[0][2] = a31;
    o.m[0][3] = a41;

    o.m[1][0] = a12;
    o.m[1][2] = a32;
    o.m[1][3] = a42;

    o.m[2][0] = a13;
    o.m[2][1] = a23;
    o.m[2][3] = a43;

    o.m[3][0] = a14;
    o.m[3][1] = a24;
    o.m[3][2] = a34;
}

template <typename T>
void Matrix44CalcCommon<T>::transposeTo(Base& o, const Base& n)
{
    SEAD_ASSERT(&o != &n);

    o.m[0][0] = n.m[0][0];
    o.m[0][1] = n.m[1][0];
    o.m[0][2] = n.m[2][0];
    o.m[0][3] = n.m[3][0];

    o.m[1][0] = n.m[0][1];
    o.m[1][1] = n.m[1][1];
    o.m[1][2] = n.m[2][1];
    o.m[1][3] = n.m[3][1];

    o.m[2][0] = n.m[0][2];
    o.m[2][1] = n.m[1][2];
    o.m[2][2] = n.m[2][2];
    o.m[2][3] = n.m[3][2];

    o.m[3][0] = n.m[0][3];
    o.m[3][1] = n.m[1][3];
    o.m[3][2] = n.m[2][3];
    o.m[3][3] = n.m[3][3];
}

template <typename T>
void Matrix44CalcCommon<T>::makeQ(Base& o, const Quat& q)
{
    // Assuming the quaternion "q" is normalized

    const T yy = 2 * q.y * q.y;
    const T zz = 2 * q.z * q.z;
    const T xx = 2 * q.x * q.x;
    const T xy = 2 * q.x * q.y;
    const T xz = 2 * q.x * q.z;
    const T yz = 2 * q.y * q.z;
    const T wz = 2 * q.w * q.z;
    const T wx = 2 * q.w * q.x;
    const T wy = 2 * q.w * q.y;

    o.m[0][0] = 1 - yy - zz;
    o.m[0][1] = xy - wz;
    o.m[0][2] = xz + wy;

    o.m[1][0] = xy + wz;
    o.m[1][1] = 1 - xx - zz;
    o.m[1][2] = yz - wx;

    o.m[2][0] = xz - wy;
    o.m[2][1] = yz + wx;
    o.m[2][2] = 1 - xx - yy;

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 1;
}

template <typename T>
void Matrix44CalcCommon<T>::makeR(Base& o, const Vec3& r)
{
    const T sinV[3] = {MathCalcCommon<T>::sin(r.x), MathCalcCommon<T>::sin(r.y),
                       MathCalcCommon<T>::sin(r.z)};

    const T cosV[3] = {MathCalcCommon<T>::cos(r.x), MathCalcCommon<T>::cos(r.y),
                       MathCalcCommon<T>::cos(r.z)};

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 1;
}

template <typename T>
void Matrix44CalcCommon<T>::makeRIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[0][0] = (cosV[1] * cosV[2]);
    o.m[1][0] = (cosV[1] * sinV[2]);
    o.m[2][0] = -sinV[1];

    o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
    o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
    o.m[2][1] = (sinV[0] * cosV[1]);

    o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
    o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
    o.m[2][2] = (cosV[0] * cosV[1]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 1;
}

template <typename T>
void Matrix44CalcCommon<T>::makeRzxyIdx(Base& o, u32 xr, u32 yr, u32 zr)
{
    const T sinV[3];
    const T cosV[3];

    MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], xr);
    MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], yr);
    MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], zr);

    o.m[2][2] = (cosV[0] * cosV[1]);
    o.m[0][2] = (cosV[0] * sinV[1]);
    o.m[1][2] = -sinV[0];

    o.m[2][0] = (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
    o.m[0][0] = (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
    o.m[1][0] = (cosV[0] * sinV[2]);

    o.m[2][1] = (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
    o.m[0][1] = (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
    o.m[1][1] = (cosV[0] * cosV[2]);

    o.m[0][3] = 0;
    o.m[1][3] = 0;
    o.m[2][3] = 0;

    o.m[3][0] = 0;
    o.m[3][1] = 0;
    o.m[3][2] = 0;
    o.m[3][3] = 1;
}

template <typename T>
void Matrix44CalcCommon<T>::toQuat(Quat& q, const Base& n)
{
    const T a11 = n.m[0][0];
    const T a12 = n.m[0][1];
    const T a13 = n.m[0][2];

    const T a21 = n.m[1][0];
    const T a22 = n.m[1][1];
    const T a23 = n.m[1][2];

    const T a31 = n.m[2][0];
    const T a32 = n.m[2][1];
    const T a33 = n.m[2][2];

    const T t = a11 + a22 + a33;
    T w, x, y, z;

    if (t > 0)
    {
        T s = MathCalcCommon<T>::sqrt(t + 1);

        w = s * 0.5f;

        // if (s != 0)
        s = 0.5f / s;

        x = (a32 - a23) * s;
        y = (a13 - a31) * s;
        z = (a21 - a12) * s;
    }
    else if (a22 > a11 && a33 <= a22)
    {
        T s = MathCalcCommon<T>::sqrt(a22 - (a33 + a11) + 1);

        y = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a13 - a31) * s;
        x = (a21 + a12) * s;
        z = (a23 + a32) * s;
    }
    else if (a22 > a11 || a33 > a11)
    {
        T s = MathCalcCommon<T>::sqrt(a33 - (a11 + a22) + 1);

        z = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a21 - a12) * s;
        x = (a31 + a13) * s;
        y = (a32 + a23) * s;
    }
    else
    {
        T s = MathCalcCommon<T>::sqrt(a11 - (a22 + a33) + 1);

        x = s * 0.5f;

        if (s != 0)
            s = 0.5f / s;

        w = (a32 - a23) * s;
        y = (a12 + a21) * s;
        z = (a13 + a31) * s;
    }

    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
}

template <typename T>
void Matrix44CalcCommon<T>::getCol(Vec4& v, const Base& n, s32 axis)
{
    v.x = n.m[0][axis];
    v.y = n.m[1][axis];
    v.z = n.m[2][axis];
    v.w = n.m[3][axis];
}

template <typename T>
void Matrix44CalcCommon<T>::getRow(Vec4& v, const Base& n, s32 row)
{
    v.x = n.m[row][0];
    v.y = n.m[row][1];
    v.z = n.m[row][2];
    v.w = n.m[row][3];
}

template <typename T>
void Matrix44CalcCommon<T>::scaleAllElements(Base& n, T s)
{
    n.m[0][0] *= s;
    n.m[0][1] *= s;
    n.m[0][2] *= s;
    n.m[0][3] *= s;

    n.m[1][0] *= s;
    n.m[1][1] *= s;
    n.m[1][2] *= s;
    n.m[1][3] *= s;

    n.m[2][0] *= s;
    n.m[2][1] *= s;
    n.m[2][2] *= s;
    n.m[2][3] *= s;

    n.m[3][0] *= s;
    n.m[3][1] *= s;
    n.m[3][2] *= s;
    n.m[3][3] *= s;
}

template <typename T>
void Matrix44CalcCommon<T>::scaleBases(Base& n, T sx, T sy, T sz, T sw)
{
    n.m[0][0] *= sx;
    n.m[1][0] *= sx;
    n.m[2][0] *= sx;
    n.m[3][0] *= sx;

    n.m[0][1] *= sy;
    n.m[1][1] *= sy;
    n.m[2][1] *= sy;
    n.m[3][1] *= sy;

    n.m[0][2] *= sz;
    n.m[1][2] *= sz;
    n.m[2][2] *= sz;
    n.m[3][2] *= sz;

    n.m[0][3] *= sw;
    n.m[1][3] *= sw;
    n.m[2][3] *= sw;
    n.m[3][3] *= sw;
}

template <typename T>
void Matrix44CalcCommon<T>::setCol(Base& n, s32 axis, const Vec4& v)
{
    n.m[0][axis] = v.x;
    n.m[1][axis] = v.y;
    n.m[2][axis] = v.z;
    n.m[3][axis] = v.w;
}

template <typename T>
void Matrix44CalcCommon<T>::setRow(Base& n, const Vec4& v, s32 row)
{
    n.m[row][0] = v.x;
    n.m[row][1] = v.y;
    n.m[row][2] = v.z;
    n.m[row][3] = v.w;
}

}  // namespace sead
