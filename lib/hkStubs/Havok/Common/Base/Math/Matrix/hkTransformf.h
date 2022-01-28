#pragma once

class hkTransformf {
public:
    HK_FORCE_INLINE hkTransformf() = default;
    HK_FORCE_INLINE hkTransformf(const hkTransformf& other);
    HK_FORCE_INLINE hkTransformf(const hkRotationf& r, hkVector4fParameter t);
    HK_FORCE_INLINE hkTransformf(hkQuaternionfParameter r, hkVector4fParameter t);

    hkTransformf& operator=(const hkTransformf& other) = default;

    hkRotationf& getRotation() { return m_rotation; }
    const hkRotationf& getRotation() const { return m_rotation; }

    hkVector4f& getTranslation() { return m_translation; }
    const hkVector4f& getTranslation() const { return m_translation; }

    HK_FORCE_INLINE void set(const hkRotationf& r, hkVector4fParameter t);
    HK_FORCE_INLINE void set(hkQuaternionfParameter q, hkVector4fParameter t);

    HK_FORCE_INLINE static const hkTransformf& getIdentity();
    HK_FORCE_INLINE void setIdentity();

    hkRotationf m_rotation;
    hkVector4f m_translation;
};

inline hkTransformf::hkTransformf(const hkTransformf& other) {
    const auto col0 = other.m_rotation.m_col0;
    const auto col1 = other.m_rotation.m_col1;
    const auto col2 = other.m_rotation.m_col2;
    const auto col3 = other.m_translation;
    m_rotation.m_col0 = col0;
    m_rotation.m_col1 = col1;
    m_rotation.m_col2 = col2;
    m_translation = col3;
}

inline hkTransformf::hkTransformf(const hkRotationf& r, const hkVector4f& t)
    : m_rotation(r), m_translation(t) {}

inline hkTransformf::hkTransformf(hkQuaternionfParameter r, const hkVector4f& t)
    : m_translation(t) {
    m_rotation.set(r);
}

inline void hkTransformf::set(const hkRotationf& r, const hkVector4f& t) {
    m_rotation = r;
    m_translation = t;
}

inline void hkTransformf::set(const hkQuaternionf& q, const hkVector4f& t) {
    m_rotation.set(q);
    m_translation = t;
}

inline const hkTransformf& hkTransformf::getIdentity() {
    return reinterpret_cast<const hkTransformf&>(g_vectorfConstants[HK_QUADREAL_1000]);
}

inline void hkTransformf::setIdentity() {
    m_rotation.setIdentity();
    m_translation.setZero();
}
