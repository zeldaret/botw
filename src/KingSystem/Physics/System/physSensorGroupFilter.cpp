#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include <basis/seadRawPrint.h>
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

constexpr int NumSensorHandlersInList0 = 0x10;
constexpr int NumSensorHandlers = 0x400;

SensorGroupFilter* SensorGroupFilter::make(ContactLayer::ValueType last, sead::Heap* heap) {
    auto* filter = util::alloc<SensorGroupFilter>(heap, FirstSensor, last);
    filter->initFilter(heap);
    return filter;
}

SensorGroupFilter::SensorGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last)
    : GroupFilter(ContactLayerType::Sensor, first, last) {}

SensorGroupFilter::~SensorGroupFilter() = default;

void SensorGroupFilter::doInit_(sead::Heap* heap) {}

// TODO
hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const {
    return hkpGroupFilter::isCollisionEnabled(a, b);
}

// TODO
hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollisionInput& input,
                                             const hkpCdBody& collectionBodyA,
                                             const hkpCdBody& collectionBodyB,
                                             const hkpShapeContainer& containerShapeA,
                                             const hkpShapeContainer& containerShapeB,
                                             hkpShapeKey keyA, hkpShapeKey keyB) const {
    return hkpGroupFilter::isCollisionEnabled(input, collectionBodyA, collectionBodyB,
                                              containerShapeA, containerShapeB, keyA, keyB);
}

// TODO
hkBool SensorGroupFilter::isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                             const hkpCdBody& b,
                                             const hkpShapeContainer& bContainer,
                                             hkpShapeKey bKey) const {
    return hkpGroupFilter::isCollisionEnabled(input, a, b, bContainer, bKey);
}

// TODO
hkBool SensorGroupFilter::isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                             const hkpShapeContainer& bContainer,
                                             hkpShapeKey bKey) const {
    return hkpGroupFilter::isCollisionEnabled(aInput, bContainer, bKey);
}

// TODO
hkBool SensorGroupFilter::isCollisionEnabled(const hkpWorldRayCastInput& inputA,
                                             const hkpCollidable& collidableB) const {
    return hkpGroupFilter::isCollisionEnabled(inputA, collidableB);
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

u32 sensorReceiverMaskSetLayer(ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    ReceiverMask info{mask};

    if (layer == ContactLayer::SensorCustomReceiver) {
        info.is_custom_receiver = true;
    } else {
        if (info.is_custom_receiver) {
            clearBitFields(&info.raw, info.is_custom_receiver, info.custom_receiver_data.layer);
        } else {
            clearBitFields(&info.raw, info.is_custom_receiver, info.data.layer,
                           info.data.has_layer2, info.data.layer2);
        }

        if (info.is_custom_receiver) {
            info.custom_receiver_data.layer.Init(layer - FirstSensor);
        } else {
            info.data.layer.Init(layer - FirstSensor);
        }
    }

    return info.raw;
}

u32 sensorReceiverMaskSetLayer2(bool set, ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    ReceiverMask info{mask};
    if (info.is_custom_receiver)
        return info.raw;

    info.is_custom_receiver = false;
    info.data.has_layer2 = false;
    info.data.layer2 = {};

    if (set) {
        info.data.has_layer2 = true;
        info.data.layer2.SetUnsafe(layer - FirstSensor);
    }

    return info.raw;
}

}  // namespace ksys::phys
