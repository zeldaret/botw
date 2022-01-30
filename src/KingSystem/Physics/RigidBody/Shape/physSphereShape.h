#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class SphereParam;

struct SphereShape {
    virtual ~SphereShape();

    RigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct SphereShapeParam {
    SphereShape* createShape(sead::Heap* heap);

    sead::Vector3f translate;
    float radius;
    CommonShapeParam common;
};

class SphereParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(SphereParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    SphereShapeParam shape;
};

}  // namespace ksys::phys
