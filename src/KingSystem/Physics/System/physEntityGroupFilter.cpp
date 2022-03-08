#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Agent/hkpCollisionInput.h>
#include <Havok/Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldObject.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/BitField.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

constexpr int NumEntityHandlersInList0 = 0x10;
constexpr int NumEntityHandlers = 0x400;

void receiverMaskEnableLayer(SensorCollisionMask* mask, ContactLayer layer) {
    mask->raw |= 1 << getContactLayerBaseRelativeValue(layer);
}

bool receiverMaskGetSensorLayerMaskForType(SensorCollisionMask* mask,
                                           const sead::SafeString& receiver_type) {
    return System::instance()->getContactMgr()->getSensorLayerMask(mask, receiver_type);
}

void receiverMaskSetSensorLayerMask(SensorCollisionMask* mask, u32 layer_mask) {
    *mask = {};
    mask->custom_receiver_data.layer_mask = layer_mask;
    mask->is_custom_receiver = true;
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
    // Allow any layer pairs to be ignored by a rigid body by default.
    mLayersThatCanBeIgnored.fill(0xffffffff);
}

hkBool EntityGroupFilter::shouldHandleGroundCollision(u32 infoA, u32 infoB,
                                                      ContactLayer::ValueType layerA,
                                                      ContactLayer::ValueType layerB) const {
    const EntityCollisionMask a{infoA};
    const EntityCollisionMask b{infoB};

    if (EntityCollisionMask(infoA | infoB).ground_col_mode != GroundCollisionMode::Normal) {
        if (a.ground_col_mode != GroundCollisionMode::Normal) {
            bool ground = isEntityGroundLayer(layerB);
            if (a.ground_col_mode == GroundCollisionMode::IgnoreNonGround && !ground)
                return false;
            if (a.ground_col_mode == GroundCollisionMode::IgnoreGround && ground)
                return false;
        }

        if (b.ground_col_mode != GroundCollisionMode::Normal) {
            bool ground = isEntityGroundLayer(layerA);
            if (b.ground_col_mode == GroundCollisionMode::IgnoreNonGround && !ground)
                return false;
            if (b.ground_col_mode == GroundCollisionMode::IgnoreGround && ground)
                return false;
        }
    }
    return true;
}

hkBool EntityGroupFilter::shouldHandleWaterCollision(u32 infoA, u32 infoB,
                                                     ContactLayer::ValueType layerA,
                                                     ContactLayer::ValueType layerB) const {
    const EntityCollisionMask a{infoA};
    const EntityCollisionMask b{infoB};

    if (EntityCollisionMask(infoA | infoB).water_col_mode != WaterCollisionMode::Normal) {
        if (a.water_col_mode == WaterCollisionMode::IgnoreWater &&
            layerB == ContactLayer::EntityWater) {
            return false;
        }
        if (b.water_col_mode == WaterCollisionMode::IgnoreWater &&
            layerA == ContactLayer::EntityWater) {
            return false;
        }
    }
    return true;
}

// XXX: find a better name
static bool testHandler(u32 idx) {
    return idx != 0 && idx <= 15;
}

// NON_MATCHING: deduplicated branch: `return a.data.query_custom_receiver_layer_mask & (1 << ...)`
hkBool EntityGroupFilter::testCollisionForEntities(u32 infoA, u32 infoB) const {
    if (mInhibitCollisions)
        return false;

    const EntityCollisionMask a{infoA};
    const EntityCollisionMask b{infoB};

    constexpr auto GroupHandlerIdxMask = decltype(a.group_handler_index)::GetMask();
    constexpr auto GroupHandlerIdxShift = decltype(a.group_handler_index)::StartBit();

    if (!EntityCollisionMask(infoA | infoB).is_ground_hit_mask) {
        if (a.unk30 && b.unk30) {
            if (((infoA ^ infoB) & GroupHandlerIdxMask) != 0) {
                if (testHandler(a.group_handler_index) || testHandler(b.group_handler_index))
                    return false;
            } else if ((infoA & GroupHandlerIdxMask) >> GroupHandlerIdxShift != 0) {
                if (a.data.unk5 == b.data.unk10 || b.data.unk5 == a.data.unk10)
                    return false;
            }
            return true;
        }

        const auto layerA = static_cast<ContactLayer::ValueType>(a.data.layer.Value());
        const auto layerB = static_cast<ContactLayer::ValueType>(b.data.layer.Value());

        if (layerA != ContactLayer::EntityQueryCustomReceiver &&
            layerB != ContactLayer::EntityQueryCustomReceiver) {
            if (!a.unk30 && !b.unk30) {
                if (!shouldHandleGroundCollision(infoA, infoB, layerA, layerB))
                    return false;
                if (!shouldHandleWaterCollision(infoA, infoB, layerA, layerB))
                    return false;
            }

            if (((infoA ^ infoB) & GroupHandlerIdxMask) != 0) {
                if (testHandler(a.group_handler_index) || testHandler(b.group_handler_index))
                    return false;
            } else if (((infoA & GroupHandlerIdxMask) >> GroupHandlerIdxShift) > 15) {
                return false;
            }
            return testLayerCollision(layerA, layerB);
        }

        if (layerA == ContactLayer::EntityQueryCustomReceiver &&
            layerB == ContactLayer::EntityQueryCustomReceiver) {
            return false;
        }

        if (layerA == ContactLayer::EntityQueryCustomReceiver)
            return a.data.query_custom_receiver_layer_mask & (1 << layerB);
        else
            return b.data.query_custom_receiver_layer_mask & (1 << layerA);
    }

    if (a.is_ground_hit_mask && b.is_ground_hit_mask) {
        const auto layerA = static_cast<ContactLayer::ValueType>(a.ground_hit.layer.Value());
        const auto layerB = static_cast<ContactLayer::ValueType>(b.ground_hit.layer.Value());

        if (!shouldHandleGroundCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!shouldHandleWaterCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!testLayerCollision(layerA, layerB))
            return false;
        return !a.ground_hit.unk23 && !b.ground_hit.unk23;
    }

    EntityCollisionMask entity_mask, ground_hit_mask;

    if (a.is_ground_hit_mask && !b.is_ground_hit_mask) {
        const auto layerA = static_cast<ContactLayer::ValueType>(a.ground_hit.layer.Value());
        const auto layerB = static_cast<ContactLayer::ValueType>(b.data.layer.Value());
        entity_mask = b;
        ground_hit_mask = a;

        if (layerB == ContactLayer::EntityQueryCustomReceiver)
            return b.data.query_custom_receiver_layer_mask & (1 << layerA);

        if (!b.unk30 && !shouldHandleGroundCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!b.unk30 && !shouldHandleWaterCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!testLayerCollision(layerA, layerB))
            return false;

    } else /* A entity, B ground hit */ {
        const auto layerA = static_cast<ContactLayer::ValueType>(a.data.layer.Value());
        const auto layerB = static_cast<ContactLayer::ValueType>(b.ground_hit.layer.Value());
        entity_mask = a;
        ground_hit_mask = b;

        if (layerA == ContactLayer::EntityQueryCustomReceiver)
            return a.data.query_custom_receiver_layer_mask & (1 << layerB);

        if (!a.unk30 && !shouldHandleGroundCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!a.unk30 && !shouldHandleWaterCollision(infoA, infoB, layerA, layerB))
            return false;
        if (!testLayerCollision(layerB, layerA))
            return false;
    }
    return !(ground_hit_mask.ground_hit.ground_hit_types & (1 << entity_mask.data.ground_hit));
}

hkBool EntityGroupFilter::testCollisionForPhantom(u32 infoPhantom, u32 infoB) const {
    if (mInhibitCollisions)
        return false;

    EntityQueryCollisionMask infoPhantomData{infoPhantom};
    const EntityCollisionMask info{infoB};
    if (info.is_ground_hit_mask)
        return infoPhantomData.raw & (1 << info.ground_hit.getLayer());
    return infoPhantomData.layer_mask & (1 << info.data.layer);
}

hkBool EntityGroupFilter::isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const {
    if (a.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM &&
        b.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        return false;
    }

    if (a.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        if (a.getShape() != nullptr)
            return testCollisionForEntities(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());

        return testCollisionForPhantom(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());
    }

    if (b.getType() == hkpWorldObject::BROAD_PHASE_PHANTOM) {
        if (b.getShape() != nullptr)
            return testCollisionForEntities(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());

        return testCollisionForPhantom(b.getCollisionFilterInfo(), a.getCollisionFilterInfo());
    }

    return testCollisionForEntities(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());
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

    return testCollisionForEntities(infoA, infoB);
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
    return testCollisionForEntities(infoA, infoB);
}

static hkBool checkCollisionWithGroundHitMask(EntityCollisionMask::GroundHitMask ground_hit_mask,
                                              EntityQueryCollisionMask ray_cast) {
    if (!(ray_cast.layer_mask & (1 << ground_hit_mask.getLayer())))
        return false;

    if (ground_hit_mask.unk & ray_cast.unk)
        return false;

    if (ground_hit_mask.ground_hit_types & (1 << ray_cast.ground_hit_type))
        return false;

    return true;
}

hkBool EntityGroupFilter::testCollisionForRayCasting(u32 infoRayCast, u32 info) const {
    if (mInhibitCollisions)
        return false;

    EntityQueryCollisionMask a{infoRayCast};
    EntityCollisionMask b{info};

    if (b.is_ground_hit_mask)
        return checkCollisionWithGroundHitMask(b.ground_hit, a);

    const u32 bHandlerIdx = b.group_handler_index;
    const u32 aHandlerIdx = a.group_handler_index;

    if (aHandlerIdx == bHandlerIdx) {
        if (bHandlerIdx > 15)
            return false;
        return a.layer_mask & (1 << b.data.layer);
    }

    if (testHandler(aHandlerIdx) || testHandler(bHandlerIdx))
        return false;

    return a.layer_mask & (1 << b.data.layer);
}

KSYS_ALWAYS_INLINE hkBool EntityGroupFilter::isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                                                const hkpShapeContainer& bContainer,
                                                                hkpShapeKey bKey) const {
    u32 bInfo = bContainer.getCollisionFilterInfo(bKey);
    if (bInfo == 0)
        return true;

    if (bInfo == 0xffffffff)
        bInfo = aInput.m_collidable->getCollisionFilterInfo();

    return testCollisionForRayCasting(aInput.m_filterInfo, bInfo);
}

hkBool EntityGroupFilter::isCollisionEnabled(const hkpWorldRayCastInput& inputA,
                                             const hkpCollidable& collidableB) const {
    auto* body = getRigidBody(collidableB);
    if (body && body->hasFlag(RigidBody::Flag::_200))
        return false;

    return testCollisionForRayCasting(inputA.m_filterInfo, collidableB.getCollisionFilterInfo());
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
    EntityCollisionMask info{mask};
    info.ground_hit.ground_hit_types |= 1 << type;
    return info.raw;
}

u32 orEntityGroundHitMask(u32 mask, const sead::SafeString& type) {
    return orEntityGroundHitMask(mask, groundHitFromText(type));
}

template <bool WithUnk>
static EntityCollisionMask makeEntityGroundHitMaskImpl(ContactLayer layer, u32 mask) {
    const EntityCollisionMask current{mask};
    EntityCollisionMask info{};
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
    EntityCollisionMask current{mask};
    if (current.is_ground_hit_mask) {
        return makeEntityGroundHitMaskImpl<true>(layer, mask).raw;
    } else {
        current.data.layer.SetUnsafe(layer);
        return current.raw;
    }
}

u32 setEntityCollisionMaskGroundHit(GroundHit ground_hit, u32 mask) {
    EntityCollisionMask current{mask};
    if (current.is_ground_hit_mask) {
        // This shouldn't happen: this function is not supposed to be called on ground hit masks.
    } else {
        current.data.ground_hit.SetUnsafe(ground_hit);
    }
    return current.raw;
}

}  // namespace ksys::phys
