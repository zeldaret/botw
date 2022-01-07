#pragma once

#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>

class hkpRigidBody : public hkpEntity {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpRigidBody)
    HK_DECLARE_REFLECTION()

    virtual ~hkpRigidBody();
    void enableDeactivation(bool _enableDeactivation);
};
