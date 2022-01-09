#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkQuaternionf {
public:
    hkQuaternionf() {}  // NOLINT(modernize-use-equals-default)
    HK_FORCE_INLINE hkQuaternionf(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);
    HK_FORCE_INLINE void set(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);

    hkVector4f m_vec;
};

inline hkQuaternionf::hkQuaternionf(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r) {
    set(ix, iy, iz, r);
}

inline void hkQuaternionf::set(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r) {
    m_vec.set(ix, iy, iz, r);
}
