#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class RigidBodyFromShape : public RigidBody {
    SEAD_RTTI_OVERRIDE(RigidBodyFromShape, RigidBody)
public:
    RigidBodyFromShape(hkpRigidBody* hkp_rigid_body, ContactLayerType layer_type,
                       const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~RigidBodyFromShape() override;

protected:
    const hkpShape* getNewHavokShape_() override;
    float updateScale_(float scale, float old_scale) override;

    virtual void m15() = 0;
    virtual void m16() = 0;
};

}  // namespace ksys::phys
