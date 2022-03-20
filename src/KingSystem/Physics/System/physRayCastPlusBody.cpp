#include "KingSystem/Physics/System/physRayCastPlusBody.h"

namespace ksys::phys {

RayCastPlusBody::RayCastPlusBody(SystemGroupHandler* group_handler, GroundHit ground_hit)
    : RayCast(group_handler, ground_hit) {}

RayCastPlusBody::~RayCastPlusBody() = default;

bool RayCastPlusBody::worldRayCast(ContactLayerType layer_type) {
    mHitRigidBody = nullptr;
    return RayCast::worldRayCast(layer_type);
}

bool RayCastPlusBody::shapeRayCast(RigidBody* rigid_body) {
    mHitRigidBody = nullptr;
    return RayCast::shapeRayCast(rigid_body);
}

bool RayCastPlusBody::phantomRayCast(Phantom* phantom) {
    mHitRigidBody = nullptr;
    return RayCast::phantomRayCast(phantom);
}

void RayCastPlusBody::onRigidBodyHit(RigidBody* body) {
    mHitRigidBody = body;
}

}  // namespace ksys::phys
