#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class CylinderView;

struct CylinderBody {
    virtual ~CylinderBody();

    RigidBody* init(u32 flag, RigidBodyParamView* view, sead::Heap* heap);
};

struct CylinderShape {
    CylinderBody* init(sead::Heap* heap);
};

class CylinderView : public RigidBodyParamView {
    SEAD_RTTI_OVERRIDE(CylinderView, RigidBodyParamView)
public:
    u8 _90;
    float _94;
    CylinderShape shape;
};

}  // namespace ksys::phys
