#pragma once

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_VECTOR4F_AARCH64_NEON
#else
#include <cmath>
#endif

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
inline hkVector4f::hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
    set(x, y, z, w);
}

inline hkVector4f::hkVector4f(const hkVector4f& other) = default;

inline void hkVector4f::set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

inline void hkVector4f::setAll(hkReal x) {
    v = {x, x, x, x};
}

inline void hkVector4f::add(hkVector4fParameter a) {
    setAdd(*this, a);
}

inline void hkVector4f::sub(hkVector4fParameter a) {
    setSub(*this, a);
}

inline void hkVector4f::mul(hkVector4fParameter a) {
    setMul(*this, a);
}

inline void hkVector4f::div(hkVector4fParameter a) {
    setDiv(*this, a);
}

inline void hkVector4f::setAdd(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v + b.v;
}

inline void hkVector4f::setSub(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v - b.v;
}

inline void hkVector4f::setMul(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v * b.v;
}

inline void hkVector4f::setDiv(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v / b.v;
}

inline void hkVector4f::mul(hkSimdFloat32Parameter a) {
    setMul(*this, a);
}

inline void hkVector4f::setMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vmulq_n_f32(v, r);
#else
    v *= r.val();
#endif
}

inline void hkVector4f::setMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    setMul(a, r);
}

inline void hkVector4f::setAdd(hkVector4fParameter a, hkSimdFloat32Parameter b) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vaddq_f32(v, vdupq_n_f32(b));
#else
    v += b.val();
#endif
}

inline void hkVector4f::setSub(hkVector4fParameter a, hkSimdFloat32Parameter b) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vsubq_f32(v, vdupq_n_f32(b));
#else
    v -= b.val();
#endif
}

inline void hkVector4f::setReciprocal(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vrecpeq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = 1.0f / a[i];
#endif
}

inline void hkVector4f::setSqrt(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vsqrtq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = std::sqrt(a[i]);
#endif
}

inline void hkVector4f::setSqrtInverse(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vrsqrteq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = 1.0f / std::sqrt(a[i]);
#endif
}

inline void hkVector4f::addMul(hkVector4fParameter a, hkVector4fParameter b) {
    setAddMul(*this, a, b);
}

inline void hkVector4f::subMul(hkVector4fParameter a, hkVector4fParameter b) {
    setSubMul(*this, a, b);
}

inline void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkVector4fParameter c) {
    v = a.v + b.v * c.v;
}

inline void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkVector4fParameter c) {
    v = a.v - b.v * c.v;
}

inline void hkVector4f::addMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
    setAddMul(*this, a, r);
}

inline void hkVector4f::addMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    addMul(a, r);
}

inline void hkVector4f::subMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
    setSubMul(*this, a, r);
}

inline void hkVector4f::subMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    subMul(a, r);
}

inline void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkSimdFloat32Parameter r) {
    m128 rr{r, r, r, r};
    v = a.v + rr * b.v;
}

inline void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkSimdFloat32Parameter r) {
    m128 rr{r, r, r, r};
    v = a.v - rr * b.v;
}

inline void hkVector4f::setCross(hkVector4fParameter a, hkVector4fParameter b) {
    // 	z = a[0] * b[1] - b[0] * a[1]
    //	x = a[1] * b[2] - b[1] * a[2]
    //	y = a[2] * b[0] - b[2] * a[0]
    //      ----   ----   ----   ----
    //        a     bb     b      aa

    auto cross0 = a.v * __builtin_shufflevector(b.v, b.v, 1, 2, 0, 3);
    auto cross1 = b.v * __builtin_shufflevector(a.v, a.v, 1, 2, 0, 3);
    auto diff = cross0 - cross1;
    v = __builtin_shufflevector(diff, diff, 1, 2, 0, 3);
}

inline void hkVector4f::setInterpolate(hkVector4fParameter v0, hkVector4fParameter v1,
                                       hkSimdFloat32Parameter t) {
    // v = v0 + t * (v1 - v0)
    hkVector4f diff;
    diff.setSub(v1, v0);
    setAddMul(v0, diff, t);
}

inline void hkVector4f::_setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    auto col0 = vmulq_laneq_f32(a.m_col0.v, v, 0);
    auto col1 = vmulq_laneq_f32(a.m_col1.v, v, 1);
    auto col2 = vmulq_laneq_f32(a.m_col2.v, v, 2);
    v = col0 + col1 + col2;
#else
    setMul(a.m_col0, b[0]);
    addMul(a.m_col1, b[1]);
    addMul(a.m_col2, b[2]);
#endif
}

inline void hkVector4f::_setTransformedPos(const hkTransformf& a, hkVector4fParameter b) {
    hkVector4f t;
    t._setRotatedDir(a.getRotation(), b);
    setAdd(t, a.getTranslation());
}

template <int N>
inline void hkVector4f::store(hkFloat32* out) const {
    static_assert(1 <= N && N <= 4, "invalid N");
#ifdef HK_VECTOR4F_AARCH64_NEON
    switch (N) {
    case 1:
        vst1q_lane_f32(out, v, 0);
        break;
    case 2:
        vst1_f32(out, vget_low_f32(v));
        break;
    case 3:
        vst1_f32(out, vget_low_f32(v));
        vst1q_lane_f32(out + 2, v, 2);
        break;
    case 4:
        vst1q_f32(out, v);
        break;
    default:
        break;
    }
#else
    for (int i = 0; i < N; ++i)
        out[i] = v[i];
#endif
}
