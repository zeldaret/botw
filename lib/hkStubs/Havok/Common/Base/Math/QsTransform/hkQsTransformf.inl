#pragma once

inline hkQsTransformf::hkQsTransformf(IdentityInitializer) {
    setIdentity();
}

inline hkQsTransformf::hkQsTransformf(ZeroInitializer) {
    setZero();
}

inline hkQsTransformf::hkQsTransformf(hkVector4fParameter translation,
                                      hkQuaternionfParameter rotation, hkVector4fParameter scale)
    : m_translation(translation), m_rotation(rotation), m_scale(scale) {}

inline hkQsTransformf::hkQsTransformf(hkVector4fParameter translation,
                                      hkQuaternionfParameter rotation)
    : m_translation(translation), m_rotation(rotation) {
    m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

inline hkQsTransformf::hkQsTransformf(const hkQsTransformf& other) {
    m_translation = other.m_translation;
    m_rotation = other.m_rotation;
    m_scale = other.m_scale;
}

inline const hkVector4f& hkQsTransformf::getTranslation() const {
    return m_translation;
}

inline const hkQuaternionf& hkQsTransformf::getRotation() const {
    return m_rotation;
}

inline const hkVector4f& hkQsTransformf::getScale() const {
    return m_scale;
}

inline void hkQsTransformf::setIdentity() {
    m_translation.setZero();
    m_rotation.setIdentity();
    m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

inline void hkQsTransformf::setZero() {
    m_translation.setZero();
    m_rotation.m_vec.setZero();
    m_scale.setZero();
}

inline void hkQsTransformf::set(hkVector4fParameter translation, hkQuaternionfParameter rotation,
                                hkVector4fParameter scale) {
    m_translation = translation;
    m_rotation = rotation;
    m_scale = scale;
}

inline void hkQsTransformf::set(hkVector4fParameter translation, hkQuaternionfParameter rotation) {
    m_translation = translation;
    m_rotation = rotation;
    m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

inline void hkQsTransformf::setInverse(const hkQsTransformf& t) {
    m_translation.setRotatedInverseDir(t.m_rotation, t.m_translation);
    m_translation.setNeg<4>(m_translation);
    m_rotation.setInverse(t.m_rotation);

    m_scale.setReciprocal(t.m_scale);

    m_scale.zeroComponent<3>();
}

inline void hkQsTransformf::setMul(const hkQsTransformf& t1, const hkQsTransformf& t2) {
    hkVector4f extraTrans;
    extraTrans._setRotatedDir(t1.m_rotation, t2.m_translation);
    m_translation.setAdd(t1.m_translation, extraTrans);
    m_rotation.setMul(t1.m_rotation, t2.m_rotation);

    m_scale.setMul(t1.m_scale, t2.m_scale);
}

inline void hkQsTransformf::setMulInverseMul(const hkQsTransformf& t1, const hkQsTransformf& t2) {
    hkQsTransformf inv;
    inv.setInverse(t1);
    setMul(inv, t2);
}

inline void hkQsTransformf::setMulMulInverse(const hkQsTransformf& t1, const hkQsTransformf& t2) {
    hkQsTransformf inv;
    inv.setInverse(t2);
    setMul(t1, inv);
}

inline void hkQsTransformf::setMulEq(const hkQsTransformf& b) {
    setMul(*this, b);
}

inline void hkQsTransformf::fastRenormalize() {
    m_rotation.normalize();
}
