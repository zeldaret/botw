#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_VECTOR4F_AARCH64_NEON
#endif

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

    /// Store N floats to out.
    template <int N>
    void store(hkFloat32* out) const;

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
        p[i] = v[i];
#endif
}
