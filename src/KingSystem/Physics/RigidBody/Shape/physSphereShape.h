#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class SphereView;

struct SphereBody {
    virtual ~SphereBody();

    RigidBody* init(u32 flag, RigidBodyParamView* view, sead::Heap* heap);
};

struct SphereShape {
    SphereBody* init(sead::Heap* heap);
};

class SphereView : public RigidBodyParamView {
    SEAD_RTTI_OVERRIDE(SphereView, RigidBodyParamView)
public:
    u8 _90;
    float _94;
    SphereShape shape;
};

}  // namespace ksys::phys
