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

    HK_FORCE_INLINE void mul(hkQuaternionfParameter q);
    HK_FORCE_INLINE void setMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1);

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

inline const hkQuaternionf& hkQuaternionf::getIdentity() {
    return reinterpret_cast<const hkQuaternionf&>(g_vectorfConstants[HK_QUADREAL_0001]);
}
