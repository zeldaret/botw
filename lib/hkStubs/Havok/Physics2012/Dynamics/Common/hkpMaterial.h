#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <cmath>

class hkpMaterial {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpMaterial)
    HK_DECLARE_REFLECTION()

    enum ResponseType {
        RESPONSE_INVALID,
        RESPONSE_SIMPLE_CONTACT,
        RESPONSE_REPORTING,
        RESPONSE_NONE,
        RESPONSE_MAX_ID
    };

    inline hkpMaterial();
    explicit hkpMaterial(hkFinishLoadedObjectFlag flag) {}

    inline hkReal getFriction() const;
    inline void setFriction(hkReal newFriction);
    static inline hkReal getCombinedFriction(hkReal frictionA, hkReal frictionB);

    inline hkReal getRestitution() const;
    inline void setRestitution(hkReal newRestitution);
    static inline hkReal getCombinedRestitution(hkReal restitutionA, hkReal restitutionB);

    inline hkReal getRollingFrictionMultiplier() const;
    inline void setRollingFrictionMultiplier(hkReal newRollingFrictionMultiplier);
    static inline hkReal getCombinedRollingFrictionMultiplier(hkReal multiplierA,
                                                              hkReal multiplierB);

    inline enum hkpMaterial::ResponseType getResponseType() const;
    inline void setResponseType(enum hkpMaterial::ResponseType t);

private:
    hkEnum<ResponseType, hkInt8> m_responseType;
    hkHalf m_rollingFrictionMultiplier;
    hkReal m_friction;
    hkReal m_restitution;
};

inline hkpMaterial::hkpMaterial() : m_friction(0.5), m_restitution(0.4) {
    m_rollingFrictionMultiplier.setZero();
}

inline hkReal hkpMaterial::getFriction() const {
    return m_friction;
}

inline void hkpMaterial::setFriction(hkReal newFriction) {
    m_friction = newFriction;
}

inline hkReal hkpMaterial::getCombinedFriction(hkReal frictionA, hkReal frictionB) {
    return std::sqrt(frictionA * frictionB);
}

inline hkReal hkpMaterial::getRestitution() const {
    return m_restitution;
}

inline void hkpMaterial::setRestitution(hkReal newRestitution) {
    m_restitution = newRestitution;
}

inline hkReal hkpMaterial::getCombinedRestitution(hkReal restitutionA, hkReal restitutionB) {
    return std::sqrt(restitutionA * restitutionB);
}

inline hkReal hkpMaterial::getRollingFrictionMultiplier() const {
    return m_rollingFrictionMultiplier;
}

inline void hkpMaterial::setRollingFrictionMultiplier(hkReal newRollingFrictionMultiplier) {
    m_rollingFrictionMultiplier = newRollingFrictionMultiplier;
}

inline hkReal hkpMaterial::getCombinedRollingFrictionMultiplier(hkReal multiplierA,
                                                                hkReal multiplierB) {
    return std::sqrt(multiplierA * multiplierB);
}

inline hkpMaterial::ResponseType hkpMaterial::getResponseType() const {
    return m_responseType;
}

inline void hkpMaterial::setResponseType(hkpMaterial::ResponseType t) {
    m_responseType = t;
}
