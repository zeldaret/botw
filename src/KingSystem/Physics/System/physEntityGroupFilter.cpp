#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Agent/hkpCollisionInput.h>
#include <Havok/Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldObject.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/BitField.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

constexpr int NumEntityHandlersInList0 = 0x10;
constexpr int NumEntityHandlers = 0x400;

void receiverMaskEnableLayer(ReceiverMask* mask, ContactLayer layer) {
    mask->raw |= 1 << getContactLayerBaseRelativeValue(layer);
}

bool receiverMaskGetSensorLayerMaskForType(ReceiverMask* mask,
                                           const sead::SafeString& receiver_type) {
    return System::instance()->getContactMgr()->getSensorLayerMask(mask, receiver_type);
}

void receiverMaskSetSensorLayerMask(ReceiverMask* mask, u32 layer_mask) {
    *mask = {};
    mask->layer_mask = layer_mask;
    mask->unk_flag = true;
}

EntityGroupFilter* EntityGroupFilter::make(ContactLayer::ValueType first,
                                           ContactLayer::ValueType last, sead::Heap* heap) {
    auto* filter = util::alloc<EntityGroupFilter>(heap, first, last);
    filter->initFilter(heap);
    return filter;
}

EntityGroupFilter::EntityGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last)
    : GroupFilter(ContactLayerType::Entity, first, last) {}

EntityGroupFilter::~EntityGroupFilter() = default;

void EntityGroupFilter::doInit_(sead::Heap* heap) {
    // Enable all collisions by default.
    mMasks.fill(0xffffffff);
}

hkBool EntityGroupFilter::isCollisionEnabledPhantom(u32 infoPhantom, u32 infoB) const {
    if (mInhibitCollisions)
        return false;

    // TODO: figure out what kind of mask infoPhantom is. Receiver/sensor mask?
    // RigidBodyParam::getParams and ContactInfoTable seem to manipulate similar looking masks.
    const EntityCollisionFilterInfo info{infoB};
    if (info.is_ground_hit_mask)
        return infoPhantom & (1 << info.ground_hit.getLayer());
    return (infoPhantom & (1 << info.data.layer)) & 0x1ffff;
}

hkBool EntityGroupFilter::isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const {
    if (a.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM &&
        b.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        return false;
    }

    if (a.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        if (a.getShape() != nullptr)
            return isCollisionEnabled(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());

        return isCollisionEnabledPhantom(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());
    }

    if (b.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        if (b.getShape() != nullptr)
            return isCollisionEnabled(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());

        return isCollisionEnabledPhantom(b.getCollisionFilterInfo(), a.getCollisionFilterInfo());
    }

    return isCollisionEnabled(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());
}

hkBool EntityGroupFilter::isCollisionEnabled(const hkpCollisionInput& input,
                                             const hkpCdBody& collectionBodyA,
                                             const hkpCdBody& collectionBodyB,
                                             const hkpShapeContainer& containerShapeA,
                                             const hkpShapeContainer& containerShapeB,
                                             hkpShapeKey keyA, hkpShapeKey keyB) const {
    auto infoA = containerShapeA.getCollisionFilterInfo(keyA);
    if (infoA == 0xffffffff)
        infoA = collectionBodyA.getRootCollidable()->getCollisionFilterInfo();

    auto infoB = containerShapeB.getCollisionFilterInfo(keyB);
    if (infoB == 0xffffffff)
        infoB = collectionBodyB.getRootCollidable()->getCollisionFilterInfo();

    return isCollisionEnabled(infoA, infoB);
}

hkBool EntityGroupFilter::isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                             const hkpCdBody& b,
                                             const hkpShapeContainer& bContainer,
                                             hkpShapeKey bKey) const {
    u32 infoB = bContainer.getCollisionFilterInfo(bKey);
    if (infoB == 0xffffffff)
        infoB = b.getRootCollidable()->getCollisionFilterInfo();

    u32 infoA = static_cast<const hkpCollidable&>(a).getCollisionFilterInfo();

    if (a.getParent() != nullptr) {
        if (mInhibitCollisions)
            return false;

        hkpCollisionDispatcher* dispatcher = input.m_dispatcher;

        auto* collidable = &a;
        auto* parent = collidable->getParent();
        while (parent) {
            auto* shape = parent->m_shape;

            if (dispatcher->hasAlternateType(shape->m_type, hkcdShapeType::COLLECTION)) {
                auto* collection = static_cast<const hkpShapeCollection*>(shape);
                infoA = collection->getCollisionFilterInfo(collidable->getShapeKey());
                goto end;
            }

            if (dispatcher->hasAlternateType(shape->m_type, hkcdShapeType::BV_TREE)) {
                auto* container = shape->getContainer();
                infoA = container->getCollisionFilterInfo(collidable->getShapeKey());
                goto end;
            }

            if (dispatcher->hasAlternateType(shape->m_type, hkcdShapeType::MULTI_SPHERE)) {
                infoA = a.getRootCollidable()->getCollisionFilterInfo();
                goto end;
            }

            if (dispatcher->hasAlternateType(shape->m_type, hkcdShapeType::CONVEX_LIST)) {
                return true;
            }

            collidable = parent;
            parent = collidable->getParent();
            infoA = static_cast<const hkpCollidable*>(collidable)->getCollisionFilterInfo();
        }
    }

end:
    return isCollisionEnabled(infoA, infoB);
}

void EntityGroupFilter::doInitSystemGroupHandlerLists_(sead::Heap* heap) {
    for (auto& list : mFreeLists)
        list.initOffset(SystemGroupHandler::getFreeListNodeOffset());

    mUsedList.initOffset(SystemGroupHandler::getUsedListNodeOffset());

    for (int i = 1; i < NumEntityHandlers; ++i) {
        auto& list = mFreeLists[i < NumEntityHandlersInList0];
        list.pushBack(new (heap) EntitySystemGroupHandler(i));
    }
}

int EntityGroupFilter::getFreeListIndex(const SystemGroupHandler* handler) {
    return handler->getIndex() < NumEntityHandlersInList0;
}

u32 orEntityGroundHitMask(u32 mask, GroundHit type) {
    EntityCollisionFilterInfo info{mask};
    info.ground_hit.ground_hit_types |= 1 << type;
    return info.raw;
}

u32 orEntityGroundHitMask(u32 mask, const sead::SafeString& type) {
    return orEntityGroundHitMask(mask, groundHitFromText(type));
}

template <bool WithUnk>
static EntityCollisionFilterInfo makeEntityGroundHitMaskImpl(ContactLayer layer, u32 mask) {
    const EntityCollisionFilterInfo current{mask};
    EntityCollisionFilterInfo info{};
    info.ground_hit.layer.SetUnsafe(layer);
    info.ground_hit.ground_hit_types = current.ground_hit.ground_hit_types;
    info.is_ground_hit_mask = true;
    if constexpr (WithUnk)
        info.ground_hit.unk = current.ground_hit.unk & 1;
    return info;
}

u32 makeEntityGroundHitMask(ContactLayer layer, u32 mask) {
    return makeEntityGroundHitMaskImpl<false>(layer, mask).raw;
}

u32 makeEntityCollisionMask(ContactLayer layer, u32 mask) {
    EntityCollisionFilterInfo current{mask};
    if (current.is_ground_hit_mask) {
        return makeEntityGroundHitMaskImpl<true>(layer, mask).raw;
    } else {
        current.data.layer.SetUnsafe(layer);
        return current.raw;
    }
}

u32 setEntityCollisionMaskGroundHit(GroundHit ground_hit, u32 mask) {
    EntityCollisionFilterInfo current{mask};
    if (current.is_ground_hit_mask) {
        // This shouldn't happen: this function is not supposed to be called on ground hit masks.
    } else {
        current.data.ground_hit.SetUnsafe(ground_hit);
    }
    return current.raw;
}

}  // namespace ksys::phys
