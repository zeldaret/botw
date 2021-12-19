#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkVector4f {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkVector4f)

    HK_FORCE_INLINE hkVector4f() {}
    HK_FORCE_INLINE hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);

    // This prevents hkVector4f from being passed in registers.
    // NOLINTNEXTLINE(modernize-use-equals-default)
    HK_FORCE_INLINE hkVector4f(const hkVector4f& other) : v(other.v) {}

    HK_FORCE_INLINE void set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);
    HK_FORCE_INLINE void setAll(hkFloat32 x);

    void sub_7100FABE80(const hkVector4f&, const hkVector4f&);

    m128 v;
};

inline hkVector4f::hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

inline void hkVector4f::set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

inline void hkVector4f::setAll(hkReal x) {
    v = {x, x, x, x};
}
