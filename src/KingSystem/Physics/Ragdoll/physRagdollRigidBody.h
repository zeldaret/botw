#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class RagdollController;

class RagdollRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(RagdollRigidBody, RigidBody)
public:
    RagdollRigidBody(const sead::SafeString& name, RagdollController* ctrl, int bone_index,
                     hkpRigidBody* hkp_rigid_body, sead::Heap* heap);
    ~RagdollRigidBody() override;

    void init(sead::Heap* heap);

    float getVolume() override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                          const sead::Vector3f& contact_point) override;

    void enableContactLayer(ContactLayer layer, bool alt_mask);
    void disableContactLayer(ContactLayer layer, bool alt_mask);
    void setContactAll(bool alt_mask);
    void setContactNone(bool alt_mask);

private:
    void updateContactMask();

    RagdollController* mCtrl{};
    int mBoneIndex{};
    RagdollRigidBody* mParentBody{};
    sead::Buffer<RagdollRigidBody*> mChildBodies{};
    u32 mContactMask1{};
    u32 mContactMask2{};
};

}  // namespace ksys::phys
