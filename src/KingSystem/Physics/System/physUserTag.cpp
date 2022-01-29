#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

void UserTag::onMaxPositionExceeded(RigidBody* body) {
    body->onMaxPositionExceeded();
}

void UserTag::m3(void* a, void* b, float c) {
    // FIXME
}

void UserTag::onBodyShapeChanged(RigidBody* body) {}

void UserTag::m5() {}

void UserTag::m7(RigidBody* rigid_body, int a) {}

}  // namespace ksys::phys
