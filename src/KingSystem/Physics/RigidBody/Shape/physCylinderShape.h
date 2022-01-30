#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
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

    sead::Vector3f translate_0;
    float radius;
    sead::Vector3f translate_1;
    float convex_radius;
    CommonShapeParam common;
};

class CylinderParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(CylinderParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    CylinderShapeParam shape;
};

}  // namespace ksys::phys
