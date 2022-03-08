#include "KingSystem/Physics/System/physSensorGroupFilter.h"
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
#include <basis/seadRawPrint.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

constexpr int NumSensorHandlersInList0 = 0x10;
constexpr int NumSensorHandlers = 0x400;

// XXX: find a better name
static bool testHandler(u32 idx) {
    return idx != 0 && idx <= 15;
}

SensorGroupFilter* SensorGroupFilter::make(ContactLayer::ValueType last, sead::Heap* heap) {
    auto* filter = util::alloc<SensorGroupFilter>(heap, FirstSensor, last);
    filter->initFilter(heap);
    return filter;
}

SensorGroupFilter::SensorGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last)
    : GroupFilter(ContactLayerType::Sensor, first, last) {}

SensorGroupFilter::~SensorGroupFilter() = default;

void SensorGroupFilter::doInit_(sead::Heap* heap) {}

hkBool SensorGroupFilter::testCollisionForSensors(u32 infoA, u32 infoB) const {
    if (mInhibitCollisions)
        return false;

    const SensorCollisionMask a{infoA};
    const SensorCollisionMask b{infoB};
    const u32 a_xor_b = infoA ^ infoB;

    constexpr auto GroupHandlerIdxMask = decltype(a.group_handler_index)::GetMask();
    constexpr auto GroupHandlerIdxShift = decltype(a.group_handler_index)::StartBit();

    if (SensorCollisionMask(a_xor_b).is_custom_receiver) {
        if (a.is_custom_receiver) {
            if (!(a.custom_receiver_data.layer_mask & (1 << b.data.layer)))
                return false;

            // TODO: this block of code shows up several times in this function
            //       and in both EntityGroupFilter and SensorGroupFilter. Can this be refactored?
            if ((a_xor_b & GroupHandlerIdxMask) == 0) {
                if (((infoA & GroupHandlerIdxMask) >> GroupHandlerIdxShift) > 15)
                    return false;
            } else if (testHandler(a.group_handler_index) || testHandler(b.group_handler_index)) {
                return false;
            }
            return true;
        } else {
            if (!(b.custom_receiver_data.layer_mask & (1 << a.data.layer)))
                return false;

            if ((a_xor_b & GroupHandlerIdxMask) == 0) {
                if (((infoA & GroupHandlerIdxMask) >> GroupHandlerIdxShift) > 15)
                    return false;
            } else if (testHandler(a.group_handler_index) || testHandler(b.group_handler_index)) {
                return false;
            }
            return true;
        }

    } else {
        if ((a_xor_b & GroupHandlerIdxMask) == 0) {
            if (((infoA & GroupHandlerIdxMask) >> GroupHandlerIdxShift) > 15)
                return false;
        } else if (testHandler(a.group_handler_index) || testHandler(b.group_handler_index)) {
            return false;
        }

        if (a.data.has_ignored_layer && b.data.layer == a.data.ignored_layer)
            return false;
        if (b.data.has_ignored_layer && a.data.layer == b.data.ignored_layer)
            return false;

        return m_collisionLookupTable[a.data.layer] & (1 << b.data.layer);
    }

    return true;
}

hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const {
    return testCollisionForSensors(a.getCollisionFilterInfo(), b.getCollisionFilterInfo());
}

hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollisionInput& input,
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

    return testCollisionForSensors(infoA, infoB);
}

hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
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
    return testCollisionForSensors(infoA, infoB);
}

hkBool SensorGroupFilter::isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                             const hkpShapeContainer& bContainer,
                                             hkpShapeKey bKey) const {
    u32 bInfo = bContainer.getCollisionFilterInfo(bKey);
    if (bInfo == 0)
        return true;

    if (bInfo == 0xffffffff)
        bInfo = aInput.m_collidable->getCollisionFilterInfo();

    return testCollisionForRayCasting(aInput.m_filterInfo, bInfo);
}

hkBool SensorGroupFilter::isCollisionEnabled(const hkpWorldRayCastInput& inputA,
                                             const hkpCollidable& collidableB) const {
    auto* body = getRigidBody(collidableB);
    if (body && body->hasFlag(RigidBody::Flag::_200))
        return false;

    return testCollisionForRayCasting(inputA.m_filterInfo, collidableB.getCollisionFilterInfo());
}

hkBool SensorGroupFilter::testCollisionForRayCasting(u32 infoRayCast, u32 info) const {
    if (mInhibitCollisions)
        return false;

    const SensorCollisionMask mask{info};
    const SensorQueryCollisionMask query{infoRayCast};

    const u32 mask_handler = mask.group_handler_index;
    const u32 query_handler = query.group_handler_index;

    if (mask.is_custom_receiver)
        return false;

    if (query_handler == mask_handler) {
        if (mask_handler > 15)
            return false;
    } else if ((query_handler != 0 && query_handler >> 4 == 0) || testHandler(mask_handler)) {
        return false;
    }
    return query.layer_mask & (1 << mask.data.layer);
}

void SensorGroupFilter::doInitSystemGroupHandlerLists_(sead::Heap* heap) {
    for (auto& list : mFreeLists)
        list.initOffset(SystemGroupHandler::getFreeListNodeOffset());

    mUsedList.initOffset(SystemGroupHandler::getUsedListNodeOffset());

    for (int i = 1; i < NumSensorHandlers; ++i) {
        auto& list = mFreeLists[i < NumSensorHandlersInList0];
        list.pushBack(new (heap) SensorSystemGroupHandler(i));
    }
}

int SensorGroupFilter::getFreeListIndex(const SystemGroupHandler* handler) {
    return handler->getIndex() < NumSensorHandlersInList0;
}

u32 sensorCollisionMaskSetLayer(ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    SensorCollisionMask info{mask};

    if (layer == ContactLayer::SensorCustomReceiver) {
        info.is_custom_receiver = true;
    } else {
        if (info.is_custom_receiver) {
            clearBitFields(&info.raw, info.is_custom_receiver, info.custom_receiver_data.layer);
        } else {
            clearBitFields(&info.raw, info.is_custom_receiver, info.data.layer,
                           info.data.has_ignored_layer, info.data.ignored_layer);
        }

        if (info.is_custom_receiver) {
            info.custom_receiver_data.layer.Init(layer - FirstSensor);
        } else {
            info.data.layer.Init(layer - FirstSensor);
        }
    }

    return info.raw;
}

u32 sensorCollisionMaskSetIgnoredLayer(bool set, ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    SensorCollisionMask info{mask};
    if (info.is_custom_receiver)
        return info.raw;

    info.is_custom_receiver = false;
    info.data.has_ignored_layer = false;
    info.data.ignored_layer = {};

    if (set) {
        info.data.has_ignored_layer = true;
        info.data.ignored_layer.SetUnsafe(layer - FirstSensor);
    }

    return info.raw;
}

}  // namespace ksys::phys
