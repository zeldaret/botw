#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class BoxParam;

struct BoxBody {
    virtual ~BoxBody();

    RigidBody* init(u32 flag, RigidBodyInstanceParam* params, sead::Heap* heap);
};

struct BoxShape {
    BoxBody* init(sead::Heap* heap);
};

class BoxParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(BoxParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    BoxShape shape;
};

}  // namespace ksys::phys
