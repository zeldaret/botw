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
