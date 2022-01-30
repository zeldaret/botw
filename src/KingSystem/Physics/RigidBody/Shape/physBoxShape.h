#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class BoxParam;

struct BoxShape {
    virtual ~BoxShape();

    RigidBody* createBody(u32 flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
};

struct BoxShapeParam {
    BoxShape* createShape(sead::Heap* heap);
};

class BoxParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(BoxParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    BoxShapeParam shape;
};

}  // namespace ksys::phys
