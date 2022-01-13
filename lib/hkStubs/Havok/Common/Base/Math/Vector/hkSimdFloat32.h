#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <cmath>

using hkSimdFloat32Parameter = class hkSimdFloat32;

class hkSimdFloat32 {
public:
    hkSimdFloat32() = default;
    hkSimdFloat32(float x) : m_real(x) {}     // NOLINT(google-explicit-constructor)
    operator float() const { return val(); }  // NOLINT(google-explicit-constructor)
    hkFloat32 val() const { return m_real; }

    void setAbs(hkSimdFloat32Parameter x);

    hkFloat32 m_real;
};

inline void hkSimdFloat32::setAbs(hkSimdFloat32Parameter x) {
    m_real = std::abs(x.m_real);
}
