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
    HK_FORCE_INLINE hkFloat32 getReal() const;
    HK_FORCE_INLINE hkSimdFloat32 getRealPart() const;
    HK_FORCE_INLINE const hkVector4f& getImag() const;

    HK_FORCE_INLINE hkBool32 hasValidAxis() const;
    /// @warning This should only be called if hasValidAxis() is true.
    HK_FORCE_INLINE void getAxis(hkVector4f& axis) const;
    HK_FORCE_INLINE hkFloat32 getAngle() const;
    hkSimdFloat32 getAngleSr() const;

    HK_FORCE_INLINE void mul(hkQuaternionfParameter q);
    HK_FORCE_INLINE void setMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1);

    HK_FORCE_INLINE void setInverse(hkQuaternionfParameter q);

    HK_FORCE_INLINE void normalize();

    HK_FORCE_INLINE static const hkQuaternionf& getIdentity();

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

inline hkFloat32 hkQuaternionf::getReal() const {
    return m_vec(3);
}

inline hkSimdFloat32 hkQuaternionf::getRealPart() const {
    return m_vec.getW();
}

inline const hkVector4f& hkQuaternionf::getImag() const {
    return m_vec;
}

inline hkBool32 hkQuaternionf::hasValidAxis() const {
    return m_vec.lengthSquared<3>().isGreater(hkSimdFloat32::getConstant<HK_QUADREAL_EPS_SQRD>());
}

void hkQuaternionf::getAxis(hkVector4f& axis) const {
    hkVector4f result = getImag();
    result.normalize<3>();
    axis.setFlipSign(result, getRealPart().lessZero());
}

inline hkFloat32 hkQuaternionf::getAngle() const {
    return getAngleSr().val();
}

inline void hkQuaternionf::mul(hkQuaternionfParameter q) {
    setMul(*this, q);
}

inline void hkQuaternionf::setMul(hkQuaternionfParameter r, hkQuaternionfParameter q) {
    const auto rImag = r.getImag();
    const auto qImag = q.getImag();
    const auto rReal = r.getRealPart();
    const auto qReal = q.getRealPart();

    hkVector4f vec;
    vec.setCross(rImag, qImag);
    vec.addMul(rReal, qImag);
    vec.addMul(qReal, rImag);
    m_vec.setXYZ_W(vec, (rReal * qReal) - rImag.dot<3>(qImag));
}

inline void hkQuaternionf::setInverse(const hkQuaternionf& q) {
    m_vec.setNeg<3>(q.getImag());
}

inline void hkQuaternionf::normalize() {
    m_vec.normalizeUnsafe<4>();
}

inline const hkQuaternionf& hkQuaternionf::getIdentity() {
    return reinterpret_cast<const hkQuaternionf&>(g_vectorfConstants[HK_QUADREAL_0001]);
}
