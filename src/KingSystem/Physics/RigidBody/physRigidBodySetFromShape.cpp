#include "KingSystem/Physics/RigidBody/physRigidBodySetFromShape.h"

namespace ksys::phys {

RigidBodySetFromShape::RigidBodySetFromShape(const sead::SafeString& name) : RigidBodySet(name) {}

RigidBodySetFromShape::~RigidBodySetFromShape() {
    destroyRigidBodies();
}

bool RigidBodySetFromShape::init(const RigidBodySetParamAccessor& accessor, sead::Heap* heap) {
    const int num_bodies = accessor.getNumRigidBodies();
    mRigidBodies.allocBuffer(num_bodies, heap);

    for (int i = 0; i < num_bodies; ++i) {
        RigidBody* body = accessor.createRigidBody(i, heap);
        if (!body) {
            destroyRigidBodies();
            return false;
        }
        mRigidBodies.pushBack(body);
    }

    return true;
}

}  // namespace ksys::phys
