#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h"
#include "Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

RagdollRigidBody::RagdollRigidBody(const sead::SafeString& name, RagdollInstance* instance,
                                   int bone_index, hkpRigidBody* hkp_rigid_body, sead::Heap* heap)
    : RigidBody(RigidBody::Type::Ragdoll, ContactLayerType::Entity, hkp_rigid_body, name, heap,
                true),
      mInstance(instance), mBoneIndex(bone_index) {
    updateCollidableQualityType(true);
    mFlags.set(Flag::NoCharStandingOn);
}

RagdollRigidBody::~RagdollRigidBody() {
    mChildBodies.freeBuffer();
}

void RagdollRigidBody::init(sead::Heap* heap) {
    const int parent_index = mInstance->getParentOfBone(mBoneIndex);
    if (parent_index >= 0)
        mParentBody = mInstance->getRigidBodies_()[parent_index];

    int num_children = 0;
    for (int i = 0, n = mInstance->getRigidBodies_().size(); i < n; ++i) {
        if (mInstance->getParentOfBone(i) == mBoneIndex)
            ++num_children;
    }

    if (num_children > 0) {
        mChildBodies.allocBufferAssert(num_children, heap);
        int child_index = 0;
        for (int i = 0, n = mInstance->getRigidBodies_().size(); i < n; ++i) {
            if (mInstance->getParentOfBone(i) == mBoneIndex) {
                mChildBodies[child_index] = mInstance->getRigidBodies_()[i];
                ++child_index;
            }
        }
    }
}

u32 RagdollRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                                        const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask;
    masks->collision_filter_info = getCollisionFilterInfo();
    MaterialMaskData data;
    data.material = Material::Ragdoll;
    masks->material_mask = MaterialMask(data.raw).getRawData();
    return 0;
}

void RagdollRigidBody::enableContactLayer(ContactLayer layer, bool alt_mask) {
    (!alt_mask ? mContactMask1 : mContactMask2) |= 1 << getLayerBit(layer);
    updateContactMask();
}

void RagdollRigidBody::disableContactLayer(ContactLayer layer, bool alt_mask) {
    (!alt_mask ? mContactMask1 : mContactMask2) &= ~(1 << getLayerBit(layer));
    updateContactMask();
}

void RagdollRigidBody::setContactAll(bool alt_mask) {
    (!alt_mask ? mContactMask1 : mContactMask2) = ~0;
    updateContactMask();
}

void RagdollRigidBody::setContactNone(bool alt_mask) {
    (!alt_mask ? mContactMask1 : mContactMask2) = 0;
    updateContactMask();
}

void RagdollRigidBody::updateContactMask() {
    setContactMask(mContactMask2 | mContactMask1);
}

float RagdollRigidBody::getVolume() {
    auto lock = makeScopedLock();

    const hkpShape* shape = mHkBody->getCollidable()->getShape();
    if (shape->getType() != hkcdShapeType::CAPSULE)
        return 0.0f;

    auto* capsule = static_cast<const hkpCapsuleShape*>(shape);

    hkVector4f diff;
    diff.setSub(capsule->getVertex<0>(), capsule->getVertex<1>());
    const float radius = capsule->getRadius();
    const float side = diff.length<3>();
    return sead::Mathf::pi() * radius * radius * 4.0f * radius / 3.0f +
           sead::Mathf::pi() * radius * radius * side;
}

}  // namespace ksys::phys
