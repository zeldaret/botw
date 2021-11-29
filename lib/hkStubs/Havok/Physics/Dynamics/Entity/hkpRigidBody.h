#pragma once

#include <Havok/Physics/Dynamics/Entity/hkpEntity.h>

class hkpRigidBody : public hkpEntity {
public:
    virtual ~hkpRigidBody();
    void enableDeactivation(bool _enableDeactivation);
};
