#pragma once

class hkQsTransformf {
public:
    // Initialisation tags.
    enum class IdentityInitializer {};
    enum class ZeroInitializer {};

    HK_FORCE_INLINE hkQsTransformf() = default;

    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE hkQsTransformf(IdentityInitializer init);

    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE hkQsTransformf(ZeroInitializer init);

    HK_FORCE_INLINE hkQsTransformf(hkVector4fParameter translation, hkQuaternionfParameter rotation,
                                   hkVector4fParameter scale);

    HK_FORCE_INLINE hkQsTransformf(hkVector4fParameter translation,
                                   hkQuaternionfParameter rotation);

    HK_FORCE_INLINE hkQsTransformf(const hkQsTransformf& other);
    hkQsTransformf& operator=(const hkQsTransformf&) = default;

    HK_FORCE_INLINE const hkVector4f& getTranslation() const;
    HK_FORCE_INLINE const hkQuaternionf& getRotation() const;
    HK_FORCE_INLINE const hkVector4f& getScale() const;

    HK_FORCE_INLINE void setIdentity();
    HK_FORCE_INLINE void setZero();

    void setFromTransformNoScale(const hkTransformf& transform);
    void copyToTransformNoScale(hkTransformf& transformOut) const;
    void setFromTransform(const hkTransformf& transform);
    void setFromTransform(const hkQTransformf& qt);
    void copyToTransform(hkTransformf& transformOut) const;

    hkVector4f m_translation;
    hkQuaternionf m_rotation;
    hkVector4f m_scale;
};
