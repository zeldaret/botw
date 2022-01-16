#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_SIMD_FLOAT32_AARCH64_NEON
#else
#include <cmath>
#endif

using hkSimdFloat32Parameter = class hkSimdFloat32;

class hkSimdFloat32 {
public:
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    using Storage = __attribute__((vector_size(2 * sizeof(float)))) float;
#else
    using Storage = float;
#endif

    hkSimdFloat32() = default;

#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    // NOLINTNEXTLINE(google-explicit-constructor)
    hkSimdFloat32(const float& x) { m_real = vdup_n_f32(x); }
    // NOLINTNEXTLINE(google-explicit-constructor)
    hkSimdFloat32(const Storage& x) { m_real = x; }
    hkFloat32 val() const { return m_real[0]; }
#else
    hkSimdFloat32(float x) : m_real{x} {}  // NOLINT(google-explicit-constructor)
    hkFloat32 val() const { return m_real; }
#endif

    operator float() const { return val(); }  // NOLINT(google-explicit-constructor)

    template <int Constant>
    HK_FORCE_INLINE static hkSimdFloat32 getConstant();

    void setAbs(hkSimdFloat32Parameter x);

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

inline void hkSimdFloat32::setAbs(hkSimdFloat32Parameter x) {
#ifdef HK_SIMD_FLOAT32_AARCH64_NEON
    m_real = vabs_f32(m_real);
#else
    m_real = std::abs(x.m_real);
#endif
}
