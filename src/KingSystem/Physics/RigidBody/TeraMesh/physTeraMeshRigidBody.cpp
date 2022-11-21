#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"

namespace ksys::phys {

TeraMeshRigidBody::TeraMeshRigidBody(hkpRigidBody* hk_body, sead::Heap* heap)
    : RigidBody(RigidBody::Type::TeraMesh, ContactLayerType::Entity, hk_body, "TeraMesh", heap,
                true) {
    RigidBodyInstanceParam param;
    param.motion_type = MotionType::Fixed;
    initMotionAccessor(param, heap, false);
}

TeraMeshRigidBody::~TeraMeshRigidBody() {
    if (isAddedToWorld()) {
        removeFromWorldImmediately();
    }
}

u32 TeraMeshRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                         const sead::Vector3f& contact_point) {
    const auto* collidable = getHkBody()->getCollidable();
    masks->ignored_layers = ~mContactMask;
    if (unk != nullptr) {
        getCollisionFilterInfoFromCollidable(masks, &masks->collision_filter_info, *collidable,
                                             unk);
        return 0;
    }
    masks->material_mask = collidable->getShape()->getUserData();
    masks->collision_filter_info = collidable->getCollisionFilterInfo();
    return 0;
}

}  // namespace ksys::phys
