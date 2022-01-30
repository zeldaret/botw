#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class BoxParam;

struct BoxShape {
    virtual ~BoxShape();

    RigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct BoxShapeParam {
    BoxShape* createShape(sead::Heap* heap);

    sead::Vector3f translate_1;
    sead::Vector3f translate_0;
    sead::Vector3f rotate;
    float convex_radius;
    CommonShapeParam common;
};

class BoxParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(BoxParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    BoxShapeParam shape;
};

}  // namespace ksys::phys
