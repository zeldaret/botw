#pragma once

#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>

class hkpRigidBodyCinfo;

class hkpRigidBody : public hkpEntity {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpRigidBody)
    HK_DECLARE_REFLECTION()

    hkpRigidBody(const hkpRigidBodyCinfo& info);
    explicit hkpRigidBody(hkFinishLoadedObjectFlag flag);

    ~hkpRigidBody() override;

    virtual hkpRigidBody* clone() const;

    void enableDeactivation(bool _enableDeactivation);

protected:
    hkMotionState* getMotionState() override;
};

inline hkpRigidBody* hkpGetRigidBody(const hkpCollidable* collidable) {
    if (collidable->getType() == hkpWorldObject::BROAD_PHASE_ENTITY) {
        return static_cast<hkpRigidBody*>(hkpGetWorldObject(collidable));
    }
    return nullptr;
}

inline hkpRigidBody* hkpGetRigidBodyUnchecked(const hkpCollidable* collidable) {
    return static_cast<hkpRigidBody*>(hkpGetWorldObject(collidable));
}
