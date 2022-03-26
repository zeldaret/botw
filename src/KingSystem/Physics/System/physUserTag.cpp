#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

void UserTag::onMaxPositionExceeded(RigidBody* body) {
    body->onMaxPositionExceeded();
}

void UserTag::onImpulse(RigidBody* body_a, RigidBody* body_b, float impulse_a) {
    body_a->onImpulse(body_b, impulse_a);
}

void UserTag::onBodyShapeChanged(RigidBody* body) {}

void UserTag::m5() {}

void UserTag::m7(RigidBody* rigid_body, int a) {}

}  // namespace ksys::phys
