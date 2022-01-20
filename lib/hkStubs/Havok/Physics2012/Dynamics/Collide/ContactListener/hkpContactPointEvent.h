#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h>

class hkpContactPointProperties;
class hkpVelocityAccumulator;

class hkpContactPointEvent : public hkpCollisionEvent {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpContactPointEvent)

    enum Type {
        TYPE_TOI,
        TYPE_EXPAND_MANIFOLD,
        TYPE_MANIFOLD,
        TYPE_MANIFOLD_AT_END_OF_STEP,
        TYPE_MANIFOLD_FROM_SAVED_CONTACT_POINT,
    };

    inline hkpContactPointEvent(CallbackSource source, hkpRigidBody* a, hkpRigidBody* b,
                                hkpSimpleConstraintContactMgr* mgr, Type type, hkContactPoint* cp,
                                hkpContactPointProperties* cpp, hkReal* sepVel, hkReal* rotNorm,
                                hkBool fullManifold, hkBool firstCallback, hkBool lastCallback,
                                hkpShapeKey* keyStorage, hkpVelocityAccumulator* accA,
                                hkpVelocityAccumulator* accB);

    inline hkBool isToi() const;

    inline hkpShapeKey* getShapeKeys(int bodyIdx) const;

    hkContactPointId getContactPointId() const;

    inline void setNormal(const hkVector4& normal);

    inline hkReal getSeparatingVelocity() const;
    inline void setSeparatingVelocity(hkReal sepVel) const;

    inline hkReal getRotateNormal() const;
    inline void setRotateNormal(hkReal rotNorm) const;

    inline void accessVelocities(int bodyIdx) const;
    inline void updateVelocities(int bodyIdx) const;

    Type m_type;
    hkContactPoint* m_contactPoint;
    hkpContactPointProperties* m_contactPointProperties;
    hkBool m_firingCallbacksForFullManifold;
    hkBool m_firstCallbackForFullManifold;
    hkBool m_lastCallbackForFullManifold;

protected:
    hkReal* m_separatingVelocity;
    hkReal* m_rotateNormal;
    hkpShapeKey* m_shapeKeyStorage;
    hkpVelocityAccumulator* m_accumulators[2];
};

inline hkpContactPointEvent::hkpContactPointEvent(
    CallbackSource source, hkpRigidBody* a, hkpRigidBody* b, hkpSimpleConstraintContactMgr* mgr,
    Type type, hkContactPoint* cp, hkpContactPointProperties* cpp, hkReal* sepVel, hkReal* rotNorm,
    hkBool fullManifold, hkBool firstCallback, hkBool lastCallback, hkpShapeKey* keyStorage,
    hkpVelocityAccumulator* accA, hkpVelocityAccumulator* accB)
    : hkpCollisionEvent(source, a, b, mgr), m_type(type), m_contactPoint(cp),
      m_contactPointProperties(cpp), m_firingCallbacksForFullManifold(fullManifold),
      m_firstCallbackForFullManifold(firstCallback), m_lastCallbackForFullManifold(lastCallback),
      m_separatingVelocity(sepVel), m_rotateNormal(rotNorm), m_shapeKeyStorage(keyStorage) {
    m_accumulators[0] = accA;
    m_accumulators[1] = accB;
}

inline hkBool hkpContactPointEvent::isToi() const {
    return m_type <= TYPE_TOI;
}

inline hkpShapeKey* hkpContactPointEvent::getShapeKeys(int bodyIdx) const {
    hkpShapeKey* shapeKeys = nullptr;
    if (getBody(bodyIdx)->m_numShapeKeysInContactPointProperties > 0) {
        shapeKeys =
            m_shapeKeyStorage + bodyIdx * m_bodies[0]->m_numShapeKeysInContactPointProperties;
    }
    return shapeKeys;
}

inline hkReal hkpContactPointEvent::getRotateNormal() const {
    return *m_rotateNormal;
}

inline void hkpContactPointEvent::setRotateNormal(hkReal rotNorm) const {
    *m_rotateNormal = rotNorm;
}
