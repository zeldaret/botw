#pragma once

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
};

class SphereParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(SphereParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    SphereShapeParam shape;
};

}  // namespace ksys::phys
