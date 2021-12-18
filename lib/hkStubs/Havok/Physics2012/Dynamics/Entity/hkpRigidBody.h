#pragma once

#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>

class hkpRigidBody : public hkpEntity {
public:
    virtual ~hkpRigidBody();
    void enableDeactivation(bool _enableDeactivation);
};
