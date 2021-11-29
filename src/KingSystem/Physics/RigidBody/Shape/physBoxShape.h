#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class BoxView;

struct BoxBody {
    virtual ~BoxBody();

    RigidBody* init(u32 flag, RigidBodyParamView* view, sead::Heap* heap);
};

struct BoxShape {
    BoxBody* init(sead::Heap* heap);
};

class BoxView : public RigidBodyParamView {
    SEAD_RTTI_OVERRIDE(BoxView, RigidBodyParamView)
public:
    u8 _90;
    float _94;
    BoxShape shape;
};

}  // namespace ksys::phys
