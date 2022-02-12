#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class ListShapeRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(ListShapeRigidBody, RigidBodyFromShape)
public:
    static ListShapeRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);
};

}  // namespace ksys::phys
