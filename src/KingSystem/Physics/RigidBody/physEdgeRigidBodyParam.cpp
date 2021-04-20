#include "KingSystem/Physics/RigidBody/physEdgeRigidBodyParam.h"

namespace ksys::phys {

EdgeRigidBodyParam::EdgeRigidBodyParam()
    : set_name(sead::SafeString::cEmptyString, "set_name", this),
      body_name(sead::SafeString::cEmptyString, "body_name", this),
      edge_type(sead::SafeString::cEmptyString, "edge_type", this) {}

EdgeRigidBodyParam::~EdgeRigidBodyParam() = default;

EdgeRigidBodySetParam::EdgeRigidBodySetParam() = default;

EdgeRigidBodySetParam::~EdgeRigidBodySetParam() {
    edge_rigid_bodies.freeBuffer();
}

void EdgeRigidBodySetParam::parse(int num, sead::Heap* heap) {
    if (num <= 0)
        return;

    edge_rigid_bodies.allocBufferAssert(num, heap);
    for (int i = 0; i < num; ++i) {
        addObj(&edge_rigid_bodies[i], sead::FormatFixedSafeString<32>("EdgeRigidBody_%d", i));
    }
}

}  // namespace ksys::phys
