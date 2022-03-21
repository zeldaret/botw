#include "KingSystem/Physics/System/physPhantom.h"
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

Phantom* Phantom::make(sead::Heap* heap, const sead::BoundBox3f& aabb, ContactLayerType layer_type,
                       const LayerMaskBuilder* layer_mask_builder, hkpAabbPhantom* havok_phantom) {
    auto* phantom = util::allocWithAlign<Phantom>(heap, 0x10, aabb, layer_type);

    phantom->initHavokPhantom(havok_phantom);

    if (layer_mask_builder != nullptr)
        phantom->setLayerMask(*layer_mask_builder);

    return phantom;
}

void Phantom::free(Phantom* phantom) {
    phantom->removePhantomFromWorld();
    phantom->mHavokPhantom->removeReference();
    delete phantom;
}

Phantom::Phantom(const sead::BoundBox3f& aabb, ContactLayerType layer_type)
    : mAabb(aabb), mLayerType(layer_type) {}

void Phantom::initHavokPhantom(hkpAabbPhantom* havok_phantom) {
    hkAabb aabb;
    loadFromVec3(&aabb.m_min, mAabb.getMin());
    loadFromVec3(&aabb.m_max, mAabb.getMax());

    if (havok_phantom) {
        mHavokPhantom = havok_phantom;
        havok_phantom->setAabb(aabb);
    } else {
        mHavokPhantom = new hkpAabbPhantom(aabb);
    }
}

void Phantom::setLayerMask(const LayerMaskBuilder& builder) {
    mLayerMask = builder.getMasks()[int(mLayerType)].layers;
    mDirtyLayerMask = true;
    mHavokPhantom->getCollidableRw()->setCollisionFilterInfo(mLayerMask);
}

bool Phantom::isAddedToWorld() const {
    return mHavokPhantom->isAddedToWorld();
}

void Phantom::addPhantomToWorld() {
    if (isAddedToWorld())
        return;

    System::instance()->lockWorld(mLayerType);
    System::instance()->getHavokWorld(mLayerType)->addPhantom(mHavokPhantom);
    System::instance()->unlockWorld(mLayerType);
}

void Phantom::removePhantomFromWorld() {
    if (!isAddedToWorld())
        return;

    System::instance()->lockWorld(mLayerType);
    System::instance()->getHavokWorld(mLayerType)->removePhantom(mHavokPhantom);
    System::instance()->unlockWorld(mLayerType);
}

void Phantom::updateHavokFilterInfoAndAabb() {
    bool added = isAddedToWorld();
    if (added)
        System::instance()->lockWorld(mLayerType);

    if (mDirtyLayerMask) {
        mHavokPhantom->getCollidableRw()->setCollisionFilterInfo(mLayerMask);
        mDirtyLayerMask = false;
    }

    hkAabb aabb;
    loadFromVec3(&aabb.m_min, mAabb.getMin());
    loadFromVec3(&aabb.m_max, mAabb.getMax());
    mHavokPhantom->setAabb(aabb);

    if (added)
        System::instance()->unlockWorld(mLayerType);
}

WorldBorderPhantom::WorldBorderPhantom()
    : hkpAabbPhantom(hkAabb{hkVector4f::zero(), hkVector4f(1, 1, 1, 0)}) {}

WorldBorderPhantom::~WorldBorderPhantom() = default;

void WorldBorderPhantom::addOverlappingCollidable(hkpCollidable* collidable) {
    auto* body = getRigidBody(*collidable);
    if (!body)
        return;

    auto position = sead::Vector3f::zero;
    auto user_name = sead::SafeString::cEmptyString;
    auto body_name = sead::SafeString::cEmptyString;

    body->getPosition(&position);
    body_name = body->getHkBodyName();
    if (auto* tag = body->getUserTag()) {
        user_name = tag->getName(body);
    }

    util::PrintDebugFmt("rigid body overlapped with WorldBorderPhantom: %f %f %f %s %s", position.x,
                        position.y, position.z, user_name, body_name);

    System::instance()->getRigidBodyRequestMgr()->onMaxPositionExceeded(body->getLayerType(), body);
}

}  // namespace ksys::phys
