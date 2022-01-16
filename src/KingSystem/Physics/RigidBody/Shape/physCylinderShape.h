#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class CylinderParam;

struct CylinderBody {
    virtual ~CylinderBody();

    RigidBody* init(u32 flag, RigidBodyInstanceParam* params, sead::Heap* heap);
};

struct CylinderShape {
    CylinderBody* init(sead::Heap* heap);
};

class CylinderParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(CylinderParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    CylinderShape shape;
};

}  // namespace ksys::phys
