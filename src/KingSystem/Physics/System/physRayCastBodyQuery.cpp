#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace ksys::phys {

RayCastBodyQuery::RayCastBodyQuery(SystemGroupHandler* group_handler, GroundHit ground_hit)
    : RayCast(group_handler, ground_hit) {}

RayCastBodyQuery::~RayCastBodyQuery() = default;

bool RayCastBodyQuery::worldRayCast(ContactLayerType layer_type) {
    mHitRigidBody = nullptr;
    return RayCast::worldRayCast(layer_type);
}

bool RayCastBodyQuery::shapeRayCast(RigidBody* rigid_body) {
    mHitRigidBody = nullptr;
    return RayCast::shapeRayCast(rigid_body);
}

bool RayCastBodyQuery::phantomRayCast(Phantom* phantom) {
    mHitRigidBody = nullptr;
    return RayCast::phantomRayCast(phantom);
}

void RayCastBodyQuery::onRigidBodyHit(RigidBody* body) {
    mHitRigidBody = body;
}

}  // namespace ksys::phys
