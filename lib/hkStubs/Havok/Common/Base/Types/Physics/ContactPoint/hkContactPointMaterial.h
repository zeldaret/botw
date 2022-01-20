#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkContactPointMaterial {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkContactPointMaterial)
    HK_DECLARE_REFLECTION()

    enum FlagEnum {
        CONTACT_IS_NEW = 1 << 0,
        CONTACT_USES_SOLVER_PATH2 = 1 << 1,
        CONTACT_BREAKOFF_OBJECT_ID_SMALLER = 1 << 2,
        CONTACT_IS_DISABLED = 1 << 3,
    };

    inline hkReal getFriction() const;
    inline void setFriction(hkReal r);

    inline hkReal getRestitution() const;
    inline void setRestitution(hkReal r);

    inline hkUlong getUserData() const;
    inline void setUserData(hkUlong data);

    inline hkBool32 isPotential();

    inline hkReal getMaxImpulsePerStep();
    inline void setMaxImpulsePerStep(hkUFloat8 impulse);

    inline void reset();

    hkUlong m_userData;
    hkUFloat8 m_friction;
    hkUint8 m_restitution;
    hkUFloat8 m_maxImpulse;
    hkUint8 m_flags;
};

inline hkReal hkContactPointMaterial::getFriction() const {
    return m_friction;
}

inline void hkContactPointMaterial::setFriction(hkReal r) {
    m_friction = float(r);
}

inline hkReal hkContactPointMaterial::getRestitution() const {
    return float(m_restitution) * (1.0f / 128.0f);
}

inline void hkContactPointMaterial::setRestitution(hkReal r) {
    m_restitution = hkUchar(hkMath::hkToIntFast(r * 128.0f));
}

inline hkUlong hkContactPointMaterial::getUserData() const {
    return m_userData;
}

inline void hkContactPointMaterial::setUserData(hkUlong data) {
    m_userData = data;
}

inline hkBool32 hkContactPointMaterial::isPotential() {
    return m_flags & CONTACT_IS_NEW;
}

inline hkReal hkContactPointMaterial::getMaxImpulsePerStep() {
    return m_maxImpulse;
}

inline void hkContactPointMaterial::setMaxImpulsePerStep(hkUFloat8 maxImpulse) {
    m_flags &= ~hkContactPointMaterial::CONTACT_USES_SOLVER_PATH2;
    m_maxImpulse = maxImpulse;
}

inline void hkContactPointMaterial::reset() {
    m_friction.m_value = 0;
    m_maxImpulse.m_value = 0;
    m_restitution = 0;
    m_flags = CONTACT_IS_NEW;
}
