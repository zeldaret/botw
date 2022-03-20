#pragma once

#include "KingSystem/Physics/System/physRayCast.h"

namespace ksys::phys {

/// A RayCast that keeps track of the first rigid body that collided with the ray (if any).
class RayCastBodyQuery : public RayCast {
    SEAD_RTTI_OVERRIDE(RayCastBodyQuery, RayCast)
public:
    RayCastBodyQuery(SystemGroupHandler* group_handler, GroundHit ground_hit);
    ~RayCastBodyQuery() override;

    bool worldRayCast(ContactLayerType layer_type);
    bool shapeRayCast(RigidBody* rigid_body);
    bool phantomRayCast(Phantom* phantom);

    RigidBody* getHitRigidBody() const { return mHitRigidBody; }

    void onRigidBodyHit(RigidBody* body) override;

private:
    RigidBody* mHitRigidBody{};
};

}  // namespace ksys::phys
