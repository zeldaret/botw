#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace ksys::phys {

class RigidBodyResource;

/// A rigid body set whose bodies are created from the hkpRigidBodies in a Havok packfile
/// (RigidBodySetParam::Type::FromResource).
class RigidBodySetFromResource : public RigidBodySet {
public:
    RigidBodySetFromResource(const sead::SafeString& name, RigidBodyResource* resource);
    ~RigidBodySetFromResource() override;

    bool init(const RigidBodySetParamAccessor& accessor, sead::Heap* heap);
    void finalize();

private:
    RigidBodyResource* mResource;
    /// A copy of the resource data, loaded in place.
    u8* mBuffer = nullptr;
    u32 mBufferSize = 0;
};

}  // namespace ksys::phys
