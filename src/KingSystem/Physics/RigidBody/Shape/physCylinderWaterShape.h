#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class CylinderWaterParam;

struct CylinderWaterShape {
    virtual ~CylinderWaterShape();

    RigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct WaterCylinderShapeParam {
    CylinderWaterShape* createShape(sead::Heap* heap);
};

class CylinderWaterParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(CylinderWaterParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    WaterCylinderShapeParam shape;
};

}  // namespace ksys::phys
