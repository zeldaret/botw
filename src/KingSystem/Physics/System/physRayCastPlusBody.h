#pragma once

#include "KingSystem/Physics/System/physRayCast.h"

namespace ksys::phys {

class RayCastPlusBody : public RayCast {
    SEAD_RTTI_OVERRIDE(RayCastPlusBody, RayCast)
public:
    RayCastPlusBody(SystemGroupHandler* group_handler, GroundHit ground_hit);
    ~RayCastPlusBody() override;

    bool worldRayCast(ContactLayerType layer_type);
    bool shapeRayCast(RigidBody* rigid_body);
    bool phantomRayCast(Phantom* phantom);

    RigidBody* getHitRigidBody() const { return mHitRigidBody; }

    void onRigidBodyHit(RigidBody* body) override;

private:
    RigidBody* mHitRigidBody{};
};

}  // namespace ksys::phys
