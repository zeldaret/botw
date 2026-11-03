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
        auto& bodies = getRigidBodies();
        for (int i = 0, n = bodies.size(); i < n; ++i) {
            if (bodies[i]->isAddedToWorld())
                bodies[i]->removeFromWorldImmediately();
            delete bodies[i];
        }
        mRigidBodies.freeBuffer();
    }
};

}  // namespace ksys::phys
