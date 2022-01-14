#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

using hkQuaternionfParameter = const class hkQuaternionf&;

class hkQuaternionf {
public:
    hkQuaternionf() {}  // NOLINT(modernize-use-equals-default)
    HK_FORCE_INLINE hkQuaternionf(const hkQuaternionf&) = default;
    HK_FORCE_INLINE hkQuaternionf(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);
    HK_FORCE_INLINE void set(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);

    HK_FORCE_INLINE hkQuaternionf& operator=(const hkQuaternionf& q);

    HK_FORCE_INLINE const hkFloat32& operator()(int i) const;
    template <int I>
    HK_FORCE_INLINE hkSimdFloat32 getComponent() const;

    hkVector4f m_vec;
};

inline hkQuaternionf::hkQuaternionf(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r) {
    set(ix, iy, iz, r);
}

inline void hkQuaternionf::set(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r) {
    m_vec.set(ix, iy, iz, r);
}

inline hkQuaternionf& hkQuaternionf::operator=(const hkQuaternionf& q) {
    m_vec = q.m_vec;
    return *this;
}

inline const hkFloat32& hkQuaternionf::operator()(int i) const {
    return m_vec(i);
}

template <int I>
inline hkSimdFloat32 hkQuaternionf::getComponent() const {
    return m_vec.getComponent<I>();
}
