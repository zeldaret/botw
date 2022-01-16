#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class SphereParam;

struct SphereBody {
    virtual ~SphereBody();

    RigidBody* init(u32 flag, RigidBodyInstanceParam* params, sead::Heap* heap);
};

struct SphereShape {
    SphereBody* init(sead::Heap* heap);
};

class SphereParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(SphereParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    SphereShape shape;
};

}  // namespace ksys::phys
