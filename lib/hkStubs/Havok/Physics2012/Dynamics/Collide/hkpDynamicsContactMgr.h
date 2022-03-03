#pragma once

#include <Havok/Physics2012/Collide/Agent/ContactMgr/hkpContactMgr.h>

class hkContactPoint;
class hkpContactPointProperties;
class hkpWorld;

class hkpDynamicsContactMgr : public hkpContactMgr {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpDynamicsContactMgr)

    explicit hkpDynamicsContactMgr(Type type) : hkpContactMgr(type) {}

    virtual hkpContactPointProperties* getContactPointProperties(hkContactPointId id) {
        return nullptr;
    }

    virtual hkContactPoint* getContactPoint(hkContactPointId id) { return nullptr; }

    virtual void getAllContactPointIds(hkArray<hkContactPointId>& contactPointIds) const {}

    virtual Type getType() const = 0;

    virtual void toiCollisionResponseBeginCallback(const hkContactPoint& cp,
                                                   struct hkpSimpleConstraintInfoInitInput& inA,
                                                   struct hkpBodyVelocity& velA,
                                                   hkpSimpleConstraintInfoInitInput& inB,
                                                   hkpBodyVelocity& velB) {}

    virtual void toiCollisionResponseEndCallback(const hkContactPoint& cp, hkReal impulseApplied,
                                                 struct hkpSimpleConstraintInfoInitInput& inA,
                                                 struct hkpBodyVelocity& velA,
                                                 hkpSimpleConstraintInfoInitInput& inB,
                                                 hkpBodyVelocity& velB) {}

    virtual class hkpConstraintInstance* getConstraintInstance() { return nullptr; }

    virtual hkBool fireCallbacksForEarliestToi(struct hkpToiEvent& event, hkReal& rotateNormal) {
        return false;
    }

    virtual void confirmToi(struct hkpToiEvent& event, hkReal rotateNormal,
                            class hkArray<class hkpEntity*>& outToBeActivated) {}

protected:
    hkpWorld* m_world;
};
