#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class WaterCylinderView;

struct WaterCylinderBody {
    virtual ~WaterCylinderBody();

    RigidBody* init(u32 flag, RigidBodyParamView* view, sead::Heap* heap);
};

struct WaterCylinderShape {
    WaterCylinderBody* init(sead::Heap* heap);
};

class WaterCylinderView : public RigidBodyParamView {
    SEAD_RTTI_OVERRIDE(WaterCylinderView, RigidBodyParamView)
public:
    u8 _90;
    float _94;
    WaterCylinderShape shape;
};

}  // namespace ksys::phys
