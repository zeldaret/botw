#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class WaterCylinderParam;

struct WaterCylinderBody {
    virtual ~WaterCylinderBody();

    RigidBody* init(u32 flag, RigidBodyInstanceParam* params, sead::Heap* heap);
};

struct WaterCylinderShape {
    WaterCylinderBody* init(sead::Heap* heap);
};

class WaterCylinderParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(WaterCylinderParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    WaterCylinderShape shape;
};

}  // namespace ksys::phys
