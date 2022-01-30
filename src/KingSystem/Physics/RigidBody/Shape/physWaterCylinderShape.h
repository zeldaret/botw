#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class WaterCylinderParam;

struct WaterCylinderShape {
    virtual ~WaterCylinderShape();

    RigidBody* createBody(u32 flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct WaterCylinderShapeParam {
    WaterCylinderShape* createShape(sead::Heap* heap);
};

class WaterCylinderParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(WaterCylinderParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    WaterCylinderShapeParam shape;
};

}  // namespace ksys::phys
