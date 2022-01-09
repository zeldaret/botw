#pragma once

#include <Havok/Common/Base/Math/Vector/hkSimdFloat32.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifndef HK_MATH_H
#error "Include <Havok/Common/Base/Math/hkMath.h> or hkBase.h"
#endif

using hkVector4fParameter = const class hkVector4f&;
using hkVector4fComparisonParameter = const class hkVector4fComparison&;

class hkMatrix3f;
class hkTransformf;

class hkVector4f {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkVector4f)

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,modernize-use-equals-default)
    HK_FORCE_INLINE hkVector4f() {}
    HK_FORCE_INLINE hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);
    HK_FORCE_INLINE hkVector4f(const hkVector4f& other);
    HK_FORCE_INLINE hkVector4f& operator=(hkVector4fParameter) = default;

    // ========== Vector initialization

    HK_FORCE_INLINE void set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);
    HK_FORCE_INLINE void setAll(hkFloat32 x);

    // ========== Vector operations

    HK_FORCE_INLINE void add(hkVector4fParameter a);
    HK_FORCE_INLINE void sub(hkVector4fParameter a);
    HK_FORCE_INLINE void mul(hkVector4fParameter a);
    HK_FORCE_INLINE void div(hkVector4fParameter a);

    HK_FORCE_INLINE void setAdd(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setSub(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setMul(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setDiv(hkVector4fParameter a, hkVector4fParameter b);

    HK_FORCE_INLINE void mul(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void setMul(hkVector4fParameter a, hkSimdFloat32Parameter r);
    HK_FORCE_INLINE void setMul(hkSimdFloat32Parameter r, hkVector4fParameter a);
    HK_FORCE_INLINE void setAdd(hkVector4fParameter a, hkSimdFloat32Parameter b);
    HK_FORCE_INLINE void setSub(hkVector4fParameter a, hkSimdFloat32Parameter b);

    HK_FORCE_INLINE void setReciprocal(hkVector4fParameter a);
    HK_FORCE_INLINE void setSqrt(hkVector4fParameter a);
    HK_FORCE_INLINE void setSqrtInverse(hkVector4fParameter a);

    HK_FORCE_INLINE void addMul(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void subMul(hkVector4fParameter a, hkVector4fParameter b);

    HK_FORCE_INLINE void setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                   hkVector4fParameter c);
    HK_FORCE_INLINE void setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                   hkVector4fParameter c);

    HK_FORCE_INLINE void addMul(hkVector4fParameter a, hkSimdFloat32Parameter r);
    HK_FORCE_INLINE void addMul(hkSimdFloat32Parameter r, hkVector4fParameter a);
    HK_FORCE_INLINE void subMul(hkVector4fParameter a, hkSimdFloat32Parameter r);
    HK_FORCE_INLINE void subMul(hkSimdFloat32Parameter r, hkVector4fParameter a);

    HK_FORCE_INLINE void setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                   hkSimdFloat32Parameter r);
    HK_FORCE_INLINE void setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                   hkSimdFloat32Parameter r);

    HK_FORCE_INLINE void setCross(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setInterpolate(hkVector4fParameter v0, hkVector4fParameter v1,
                                        hkSimdFloat32Parameter t);

    // ========== Comparisons

    HK_FORCE_INLINE hkVector4fComparison less(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison lessEqual(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison greater(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison greaterEqual(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison equal(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison notEqual(hkVector4fParameter a) const;
    HK_FORCE_INLINE hkVector4fComparison lessZero() const;
    HK_FORCE_INLINE hkVector4fComparison lessEqualZero() const;
    HK_FORCE_INLINE hkVector4fComparison greaterZero() const;
    HK_FORCE_INLINE hkVector4fComparison greaterEqualZero() const;
    HK_FORCE_INLINE hkVector4fComparison equalZero() const;
    HK_FORCE_INLINE hkVector4fComparison notEqualZero() const;

    // ========== Sign, comparisons, clamping

    void setAbs(hkVector4fParameter a);

    // ========== Matrix operations (out-of-line)

    void setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);
    void setTransformedPos(const hkTransformf& a, const hkVector4f& pos);

    // ========== Matrix operations (inline)

    HK_FORCE_INLINE void _setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);
    HK_FORCE_INLINE void _setTransformedPos(const hkTransformf& a, hkVector4fParameter b);

    // ========== Length and normalization

    // ========== Misc

    // ========== Component access

    hkFloat32& operator()(int i) { return reinterpret_cast<float*>(&v)[i]; }
    hkFloat32& operator[](int i) { return reinterpret_cast<float*>(&v)[i]; }
    const hkFloat32& operator()(int i) const { return reinterpret_cast<const float*>(&v)[i]; }
    const hkFloat32& operator[](int i) const { return reinterpret_cast<const float*>(&v)[i]; }

    hkSimdFloat32 getComponent(int i) const { return v[i]; }
    hkSimdFloat32 getX() const { return getComponent(0); }
    hkSimdFloat32 getY() const { return getComponent(1); }
    hkSimdFloat32 getZ() const { return getComponent(2); }
    hkSimdFloat32 getW() const { return getComponent(3); }
    void setComponent(int i, hkSimdFloat32Parameter val) { v[i] = val; }
    void setX(hkSimdFloat32Parameter val) { setComponent(0, val); }
    void setY(hkSimdFloat32Parameter val) { setComponent(1, val); }
    void setZ(hkSimdFloat32Parameter val) { setComponent(2, val); }
    void setW(hkSimdFloat32Parameter val) { setComponent(3, val); }

    // ========== Load/store

    /// Store N floats to out.
    template <int N>
    void store(hkFloat32* out) const;

    m128 v;
};
