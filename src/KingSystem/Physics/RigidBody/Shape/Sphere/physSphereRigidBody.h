#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class SphereRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(SphereRigidBody, RigidBodyFromShape)
public:
    static SphereRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);
};

}  // namespace ksys::phys
