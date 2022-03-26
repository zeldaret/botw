#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"

namespace ksys::phys {

RagdollRigidBody::RagdollRigidBody(const sead::SafeString& name, RagdollController* ctrl,
                                   int ragdoll_body_index, hkpRigidBody* hkp_rigid_body,
                                   sead::Heap* heap)
    : RigidBody(RigidBody::Type::Ragdoll, ContactLayerType::Entity, hkp_rigid_body, name, heap,
                true),
      mCtrl(ctrl), mRagdollBodyIndex(ragdoll_body_index) {
    updateCollidableQualityType(true);
    mFlags.set(Flag::NoCharStandingOn);
}

RagdollRigidBody::~RagdollRigidBody() {
    _e8.freeBuffer();
}

}  // namespace ksys::phys
