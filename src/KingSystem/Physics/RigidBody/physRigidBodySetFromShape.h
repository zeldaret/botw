#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace ksys::phys {

/// A rigid body set whose bodies are created from the shape parameters in the actor's
/// physics parameters (RigidBodySetParam::Type::FromShapeType).
class RigidBodySetFromShape : public RigidBodySet {
public:
    explicit RigidBodySetFromShape(const sead::SafeString& name);
    ~RigidBodySetFromShape() override;

    bool init(const RigidBodySetParamAccessor& accessor, sead::Heap* heap);

private:
    void destroyRigidBodies() {
        for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
            if (mRigidBodies[i]->isAddedToWorld())
                mRigidBodies[i]->removeFromWorldImmediately();
            delete mRigidBodies[i];
        }
        mRigidBodies.freeBuffer();
    }
};

}  // namespace ksys::phys
