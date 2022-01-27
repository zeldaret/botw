#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_SIMD_FLOAT32_AARCH64_NEON
#else
#include <cmath>
#endif

using hkSimdFloat32Parameter = const class hkSimdFloat32&;

class hkSimdFloat32 {
public:
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    using Storage = __attribute__((vector_size(2 * sizeof(float)))) float;
#else
    using Storage = __attribute__((vector_size(4 * sizeof(float)))) float;
#endif

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,modernize-use-equals-default)
    hkSimdFloat32() {}
    // NOLINTNEXTLINE(google-explicit-constructor)
    hkSimdFloat32(const Storage& x) { m_real = x; }

#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    // NOLINTNEXTLINE(google-explicit-constructor)
    hkSimdFloat32(const float& x) { m_real = vdup_n_f32(x); }
#else
    hkSimdFloat32(float x) : m_real{x, x, x, x} {}  // NOLINT(google-explicit-constructor)
#endif

    hkFloat32 val() const { return m_real[0]; }
    operator float() const { return val(); }  // NOLINT(google-explicit-constructor)

    template <int Constant>
    HK_FORCE_INLINE static hkSimdFloat32 getConstant();

    HK_FORCE_INLINE hkSimdFloat32 operator-() const;
    HK_FORCE_INLINE hkSimdFloat32 operator+(hkSimdFloat32Parameter r) const;
    HK_FORCE_INLINE hkSimdFloat32 operator-(hkSimdFloat32Parameter r) const;
    HK_FORCE_INLINE hkSimdFloat32 operator*(hkSimdFloat32Parameter r) const;
    HK_FORCE_INLINE hkSimdFloat32 operator/(hkSimdFloat32Parameter r) const;

    HK_FORCE_INLINE void add(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void sub(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void mul(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void div(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void addMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void subMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

    HK_FORCE_INLINE void setAdd(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void setSub(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void setMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void setAddMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b,
                                   hkSimdFloat32Parameter c);
    HK_FORCE_INLINE void setSubMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b,
                                   hkSimdFloat32Parameter c);

    void setAbs(hkSimdFloat32Parameter x);

    HK_FORCE_INLINE void setReciprocal(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE hkSimdFloat32 reciprocal() const;
    /// Returns the square root (or zero if the value is negative).
    HK_FORCE_INLINE hkSimdFloat32 sqrt() const;
    /// Returns the square root. Does not check if the value is negative.
    HK_FORCE_INLINE hkSimdFloat32 sqrtUnsafe() const;
    /// Return the inverse square root (or zero if the value is negative or zero).
    HK_FORCE_INLINE hkSimdFloat32 sqrtInverse() const;
    /// Return the inverse square root. Does not check if the value is negative or zero.
    HK_FORCE_INLINE hkSimdFloat32 sqrtInverseUnsafe() const;

    HK_FORCE_INLINE hkBool32 isEqualZero() const;

    HK_FORCE_INLINE m128 toQuad() const;

    Storage m_real;
};

template <int Constant>
inline hkSimdFloat32 hkSimdFloat32::getConstant() {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    return vget_low_f32(g_vectorfConstants[Constant]);
#else
    return g_vectorfConstants[Constant][0];
#endif
}

inline hkSimdFloat32 hkSimdFloat32::operator-() const {
    return -m_real;
}

inline hkSimdFloat32 hkSimdFloat32::operator+(hkSimdFloat32Parameter r) const {
    return m_real + r.m_real;
}

inline hkSimdFloat32 hkSimdFloat32::operator-(hkSimdFloat32Parameter r) const {
    return m_real - r.m_real;
}

inline hkSimdFloat32 hkSimdFloat32::operator*(hkSimdFloat32Parameter r) const {
    return m_real * r.m_real;
}

inline hkSimdFloat32 hkSimdFloat32::operator/(hkSimdFloat32Parameter r) const {
    return m_real / r.m_real;
}

inline void hkSimdFloat32::add(hkSimdFloat32Parameter a) {
    setAdd(*this, a);
}

inline void hkSimdFloat32::sub(hkSimdFloat32Parameter a) {
    setSub(*this, a);
}

inline void hkSimdFloat32::mul(hkSimdFloat32Parameter a) {
    setMul(*this, a);
}

inline void hkSimdFloat32::div(hkSimdFloat32Parameter a) {
    setDiv(*this, a);
}

inline void hkSimdFloat32::addMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    setAddMul(*this, a, b);
}

inline void hkSimdFloat32::subMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    setSubMul(*this, a, b);
}

inline void hkSimdFloat32::setAdd(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    m_real = a.m_real + b.m_real;
}

inline void hkSimdFloat32::setSub(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    m_real = a.m_real - b.m_real;
}

inline void hkSimdFloat32::setMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    m_real = a.m_real * b.m_real;
}

inline void hkSimdFloat32::setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b) {
    m_real = a.m_real / b.m_real;
}

inline void hkSimdFloat32::setAddMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b,
                                     hkSimdFloat32Parameter c) {
    m_real = a.m_real + b.m_real * c.m_real;
}

inline void hkSimdFloat32::setSubMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b,
                                     hkSimdFloat32Parameter c) {
    m_real = a.m_real - b.m_real * c.m_real;
}

inline void hkSimdFloat32::setAbs(hkSimdFloat32Parameter x) {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    m_real = vabs_f32(m_real);
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = std::abs(x.m_real[i]);
#endif
}

inline void hkSimdFloat32::setReciprocal(hkSimdFloat32Parameter a) {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    auto r0 = vrecpe_f32(a.m_real);
    auto r1 = vmul_f32(r0, vrecps_f32(a.m_real, r0));
    auto r2 = vmul_f32(r1, vrecps_f32(a.m_real, r1));
    m_real = r2;
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = 1.0f / a.m_real[i];
#endif
}

inline hkSimdFloat32 hkSimdFloat32::reciprocal() const {
    hkSimdFloat32 r;
    r.setReciprocal(*this);
    return r;
}

inline hkSimdFloat32 hkSimdFloat32::sqrt() const {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    const auto equalsZero = vcle_f32(m_real, vcreate_f32(0));
    const auto inv = sqrtInverseUnsafe().m_real;
    const auto r = m_real * inv;
    return vbic_u32(r, equalsZero);
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = m_real[i] >= 0.0f ? std::sqrt(m_real[i]) : 0.0f;
#endif
}

inline hkSimdFloat32 hkSimdFloat32::sqrtUnsafe() const {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    const auto inv = sqrtInverseUnsafe();
    return m_real * inv.m_real;
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = std::sqrt(m_real[i]);
#endif
}

inline hkSimdFloat32 hkSimdFloat32::sqrtInverse() const {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    const auto equalsZero = vcle_f32(m_real, vcreate_f32(0));
    const auto inv = sqrtInverseUnsafe().m_real;
    return vbic_u32(inv, equalsZero);
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = m_real[i] > 0.0f ? (1.0f / std::sqrt(m_real[i])) : 0.0f;
#endif
}

inline hkSimdFloat32 hkSimdFloat32::sqrtInverseUnsafe() const {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    auto r0 = vrsqrte_f32(m_real);
    r0 = vrsqrts_f32(m_real, r0 * r0) * r0;
    r0 = vrsqrts_f32(m_real, r0 * r0) * r0;
    return r0;
#else
    for (int i = 0; i < 4; ++i)
        m_real[i] = 1.0f / std::sqrt(m_real[i]);
#endif
}

inline hkBool32 hkSimdFloat32::isEqualZero() const {
    auto cmp = m_real == 0.0;
    return cmp[0];
}

inline m128 hkSimdFloat32::toQuad() const {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    return vcombine_f32(m_real, m_real);
#else
    return m_real;
#endif
}
