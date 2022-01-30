#pragma once

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
    HK_FORCE_INLINE hkFloat32 getReal() const;
    HK_FORCE_INLINE hkSimdFloat32 getRealPart() const;
    HK_FORCE_INLINE const hkVector4f& getImag() const;

    HK_FORCE_INLINE hkBool32 hasValidAxis() const;
    /// @warning This should only be called if hasValidAxis() is true.
    HK_FORCE_INLINE void getAxis(hkVector4f& axis) const;
    HK_FORCE_INLINE hkFloat32 getAngle() const;
    hkSimdFloat32 getAngleSr() const;

    /// self = self * q
    HK_FORCE_INLINE void mul(hkQuaternionfParameter q);
    /// self = r * q
    HK_FORCE_INLINE void setMul(hkQuaternionfParameter r, hkQuaternionfParameter q);
    /// self = r * q^-1
    HK_FORCE_INLINE void setMulInverse(hkQuaternionfParameter r, hkQuaternionfParameter q);
    /// self = r^-1 * q
    HK_FORCE_INLINE void setInverseMul(hkQuaternionfParameter r, hkQuaternionfParameter q);

    HK_FORCE_INLINE void setInverse(hkQuaternionfParameter q);

    HK_FORCE_INLINE void normalize();

    HK_FORCE_INLINE static const hkQuaternionf& getIdentity();
    HK_FORCE_INLINE void setIdentity();

    hkVector4f m_vec;
};
