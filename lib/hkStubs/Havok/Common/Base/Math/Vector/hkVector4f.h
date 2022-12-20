#pragma once

#include <Havok/Common/Base/Math/Vector/hkSimdFloat32.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifndef HK_MATH_H
#error "Include <Havok/Common/Base/Math/hkMath.h> or hkBase.h"
#endif

class hkVector4f {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkVector4f)

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,modernize-use-equals-default)
    HK_FORCE_INLINE hkVector4f() {}
    HK_FORCE_INLINE hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);
    HK_FORCE_INLINE hkVector4f(const hkVector4f& other);
    HK_FORCE_INLINE hkVector4f& operator=(hkVector4fParameter other);

    // ========== Vector initialization

    HK_FORCE_INLINE void set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = 0);
    HK_FORCE_INLINE void setXYZ(hkVector4fParameter xyz);
    HK_FORCE_INLINE void setXYZ_W(hkVector4fParameter xyz, hkSimdFloat32Parameter w);
    HK_FORCE_INLINE void setAll(hkFloat32 x);
    HK_FORCE_INLINE void setAll(hkSimdFloat32Parameter x);
    HK_FORCE_INLINE void setZero();
    template <int I>
    HK_FORCE_INLINE void zeroComponent();
    HK_FORCE_INLINE void zeroComponent(int i);

    // ========== Vector operations

    HK_FORCE_INLINE void add(hkVector4fParameter a);
    HK_FORCE_INLINE void sub(hkVector4fParameter a);
    HK_FORCE_INLINE void mul(hkVector4fParameter a);
    HK_FORCE_INLINE void div(hkVector4fParameter a);

    HK_FORCE_INLINE void setAdd(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setSub(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setMul(hkVector4fParameter a, hkVector4fParameter b);
    HK_FORCE_INLINE void setDiv(hkVector4fParameter a, hkVector4fParameter b);

    HK_FORCE_INLINE void add(hkSimdFloat32Parameter a);
    HK_FORCE_INLINE void sub(hkSimdFloat32Parameter a);
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

    /// Whether the first N components of this vector are within `epsilon`
    /// of the corresponding components in `v`.
    template <int N>
    HK_FORCE_INLINE hkBool32 allEqual(hkVector4fParameter rhs,
                                      hkSimdFloat32Parameter epsilon) const;

    // ========== Sign, comparisons, clamping

    HK_FORCE_INLINE void setAbs(hkVector4fParameter a);
    template <int N>
    HK_FORCE_INLINE void setNeg(hkVector4fParameter a);

    /// v[i] = mask[i] ? -a[i] : a[i]
    HK_FORCE_INLINE void setFlipSign(hkVector4fParameter a, hkVector4fComparisonParameter mask);
    /// v[i] = signs[i] < 0 ? -a[i] : a[i]
    HK_FORCE_INLINE void setFlipSign(hkVector4fParameter a, hkVector4fParameter signs);
    /// v[i] = sign < 0 ? -a[i] : a[i]
    HK_FORCE_INLINE void setFlipSign(hkVector4fParameter a, hkSimdFloat32Parameter sign);

    /// Whether the sign bit is set. (True for -0.0.)
    HK_FORCE_INLINE hkVector4fComparison signBitSet() const;
    /// Whether the sign bit is cleared.
    HK_FORCE_INLINE hkVector4fComparison signBitClear() const;

    // ========== Matrix operations (out-of-line)

    void setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);
    void setRotatedInverseDir(const hkMatrix3f& a, hkVector4fParameter b);
    void setTransformedPos(const hkTransformf& a, const hkVector4f& pos);
    void setTransformedInversePos(const hkTransformf& a, hkVector4fParameter b);

    void setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter direction);
    void setRotatedInverseDir(hkQuaternionfParameter quat, hkVector4fParameter direction);
    void setTransformedPos(const hkQsTransformf& a, hkVector4fParameter b);
    void setTransformedInversePos(const hkQsTransformf& a, hkVector4fParameter b);

    void setTransformedPos(const hkQTransformf& a, hkVector4fParameter b);
    void setTransformedInversePos(const hkQTransformf& a, hkVector4fParameter b);

    // ========== Matrix operations (inline)

    HK_FORCE_INLINE void _setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);
    HK_FORCE_INLINE void _setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter vec);
    HK_FORCE_INLINE void _setRotatedInverseDir(hkQuaternionfParameter quat,
                                               hkVector4fParameter vec);
    HK_FORCE_INLINE void _setTransformedPos(const hkTransformf& a, hkVector4fParameter b);

    // ========== Length and normalization

    template <int N>
    HK_FORCE_INLINE hkSimdFloat32 dot(hkVector4fParameter a) const;

    template <int N>
    HK_FORCE_INLINE void setDot(hkVector4fParameter a, hkVector4fParameter b);

    /// Get the length of this vector as if it had N components.
    template <int N>
    HK_FORCE_INLINE hkSimdFloat32 length() const;

    /// Get the squared length (|v|^2) of this vector as if it had N components.
    template <int N>
    HK_FORCE_INLINE hkSimdFloat32 lengthSquared() const;

    /// Get the inverse length (1/|v|) of this vector as if it had N components.
    template <int N>
    HK_FORCE_INLINE hkSimdFloat32 lengthInverse() const;

    /// Get the inverse length (1/|v|) of this vector as if it had N components.
    /// Does not check for negative sqrt values or divide-by-zero.
    template <int N>
    HK_FORCE_INLINE hkSimdFloat32 lengthInverseUnsafe() const;

    /// Normalize this vector as if it had N components.
    template <int N>
    HK_FORCE_INLINE void normalize();

    /// Normalize this vector as if it had N components.
    /// Does not check for negative sqrt values or divide-by-zero.
    template <int N>
    HK_FORCE_INLINE void normalizeUnsafe();

    // ========== Misc

    /// Dot product of this vector and (a.x, a.y, a.z, 1).
    hkSimdFloat32 dot4xyz1(hkVector4fParameter a) const;

    // ========== Component access

    hkFloat32& operator()(int i) { return reinterpret_cast<float*>(&v)[i]; }
    hkFloat32& operator[](int i) { return reinterpret_cast<float*>(&v)[i]; }
    const hkFloat32& operator()(int i) const { return reinterpret_cast<const float*>(&v)[i]; }
    const hkFloat32& operator[](int i) const { return reinterpret_cast<const float*>(&v)[i]; }

    template <int I>
    HK_FORCE_INLINE hkSimdFloat32 getComponent() const {
        return v[I];
    }
    hkSimdFloat32 getComponent(int i) const { return v[i]; }
    hkSimdFloat32 getX() const { return getComponent<0>(); }
    hkSimdFloat32 getY() const { return getComponent<1>(); }
    hkSimdFloat32 getZ() const { return getComponent<2>(); }
    hkSimdFloat32 getW() const { return getComponent<3>(); }
    template <int I>
    HK_FORCE_INLINE void setComponent(hkSimdFloat32Parameter val) {
        v[I] = val;
    }
    void setComponent(int i, hkSimdFloat32Parameter val) { v[i] = val; }
    void setX(hkSimdFloat32Parameter val) { setComponent(0, val); }
    void setY(hkSimdFloat32Parameter val) { setComponent(1, val); }
    void setZ(hkSimdFloat32Parameter val) { setComponent(2, val); }
    void setW(hkSimdFloat32Parameter val) { setComponent(3, val); }

    HK_FORCE_INLINE void setInt24W(int value);
    HK_FORCE_INLINE int getInt24W() const;

    // ========== Load/store

    template <int Constant>
    HK_FORCE_INLINE static const hkVector4f& getConstant();

    HK_FORCE_INLINE static hkVector4f zero() {
        hkVector4f u;
        u.setZero();
        return u;
    }

    /// Load N floats from in.
    template <int N>
    void load(const hkFloat32* in);

    /// Store N floats to out.
    template <int N>
    void store(hkFloat32* out) const;

    m128 v;
};
