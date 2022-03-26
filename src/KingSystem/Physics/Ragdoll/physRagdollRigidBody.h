#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class RagdollController;

// TODO
class RagdollRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(RagdollRigidBody, RigidBody)
public:
    RagdollRigidBody(const sead::SafeString& name, RagdollController* ctrl, int ragdoll_body_index,
                     hkpRigidBody* hkp_rigid_body, sead::Heap* heap);
    ~RagdollRigidBody() override;

    float getVolume() override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                          const sead::Vector3f& contact_point) override;

private:
    RagdollController* mCtrl{};
    int mRagdollBodyIndex{};
    void* _e0{};
    sead::Buffer<void*> _e8{};
    void* _f8{};
};

}  // namespace ksys::phys
