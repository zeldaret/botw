#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class CylinderParam;

struct CylinderShape {
    virtual ~CylinderShape();

    RigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct CylinderShapeParam {
    CylinderShape* createShape(sead::Heap* heap);
};

class CylinderParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(CylinderParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    CylinderShapeParam shape;
};

}  // namespace ksys::phys
