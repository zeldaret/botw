#pragma once

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
    void destroyRigidBodies();
};

}  // namespace ksys::phys
