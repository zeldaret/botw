#include "KingSystem/Physics/RigidBody/physRigidBodySetFromShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

RigidBodySetFromShape::RigidBodySetFromShape(const sead::SafeString& name) : RigidBodySet(name) {}

// NON_MATCHING: regalloc (the address of mRigidBodies is kept in a register)
RigidBodySetFromShape::~RigidBodySetFromShape() {
    destroyRigidBodies();
}

// NON_MATCHING: regalloc (the address of mRigidBodies is kept in a register)
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

inline void RigidBodySetFromShape::destroyRigidBodies() {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        if (mRigidBodies[i]->isAddedToWorld())
            mRigidBodies[i]->removeFromWorldImmediately();
        delete mRigidBodies[i];
    }
    mRigidBodies.freeBuffer();
}

}  // namespace ksys::phys
