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

    HK_FORCE_INLINE void set(hkVector4fParameter translation, hkQuaternionfParameter rotation,
                             hkVector4fParameter scale);

    HK_FORCE_INLINE void set(hkVector4fParameter translation, hkQuaternionfParameter rotation);

    HK_FORCE_INLINE void setInverse(const hkQsTransformf& t);

    HK_FORCE_INLINE void setMul(const hkQsTransformf& t1, const hkQsTransformf& t2);

    HK_FORCE_INLINE void setMulScaled(const hkQsTransformf& t1, const hkQsTransformf& t2);

    /// this = t1^-1 * t2
    HK_FORCE_INLINE void setMulInverseMul(const hkQsTransformf& t1, const hkQsTransformf& t2);

    /// this = t1 * t2^-1
    HK_FORCE_INLINE void setMulMulInverse(const hkQsTransformf& t1, const hkQsTransformf& t2);

    /// this *= b
    HK_FORCE_INLINE void setMulEq(const hkQsTransformf& b);

    bool isOk(hkFloat32 epsilon = hkFloat32(1e-3f)) const;

    void fastRenormalize();

    hkVector4f m_translation;
    hkQuaternionf m_rotation;
    hkVector4f m_scale;
};
