#pragma once

#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class SensorSystemGroupHandler : public SystemGroupHandler {
public:
    explicit SensorSystemGroupHandler(int i) : SystemGroupHandler(i, ContactLayerType::Sensor) {}

    u32 makeCollisionFilterInfo(u32 info, ContactLayer layer, GroundHit ground_hit) override;
    u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) override;
    bool m8() override;
};

class SensorGroupFilter : public GroupFilter {
    SEAD_RTTI_OVERRIDE(SensorGroupFilter, GroupFilter)
public:
    static SensorGroupFilter* make(ContactLayer::ValueType last, sead::Heap* heap);

    SensorGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last);
    ~SensorGroupFilter() override;

    hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const override;
    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                              const hkpCdBody& b, const hkpShapeContainer& bContainer,
                              hkpShapeKey bKey) const override;
    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& collectionBodyA,
                              const hkpCdBody& collectionBodyB,
                              const hkpShapeContainer& containerShapeA,
                              const hkpShapeContainer& containerShapeB, hkpShapeKey keyA,
                              hkpShapeKey keyB) const override;
    hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                              const hkpShapeContainer& bContainer, hkpShapeKey bKey) const override;
    hkBool isCollisionEnabled(const hkpWorldRayCastInput& inputA,
                              const hkpCollidable& collidableB) const override;

    u32 makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit) override;
    ContactLayer getCollisionFilterInfoLayer(u32 info) override;
    u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) override;
    GroundHit getQueryCollisionMaskGroundHit(u32 info) override;
    void getCollisionFilterInfoLayerAndGroundHit(u32 info, ContactLayer* layer,
                                                 GroundHit* ground_hit) override;
    const char* getCollisionFilterInfoLayerText(u32 info) override;
    u32 getCollisionFilterInfoGroupHandlerIdx(u32 info) override;

    virtual u32 makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit, u32 unk5,
                                        u32 unk10);
    virtual void setSensorLayerCollisionEnabledMask(ContactLayer layer, u32 mask);

protected:
    /// Checks whether two sensors are colliding.
    hkBool testCollisionForSensors(u32 infoA, u32 infoB) const;
    hkBool testCollisionForRayCasting(u32 infoRayCast, u32 info) const;

    void doInitSystemGroupHandlerLists_(sead::Heap* heap) override;
    int getFreeListIndex(const SystemGroupHandler* handler) override;
    void doInit_(sead::Heap* heap) override;
};

/// Set the contact layer in a sensor collision mask.
/// @param layer A sensor contact layer
/// @param mask An existing sensor collision mask
u32 sensorCollisionMaskSetLayer(ContactLayer layer, u32 mask);

/// Set or clear a contact layer to ignore during collision detection in a sensor collision mask.
/// This function does nothing when using a custom receiver.
/// @param set If true, set the specified layer. Clear it otherwise
/// @param layer A sensor contact layer to be ignored
/// @param mask An existing sensor collision mask
u32 sensorCollisionMaskSetIgnoredLayer(bool set, ContactLayer layer, u32 mask);

inline u32 SensorSystemGroupHandler::makeCollisionFilterInfo(u32 info, ContactLayer layer,
                                                             GroundHit ground_hit) {
    const SensorCollisionMask current_info{info};
    SensorCollisionMask result;

    if (layer == ContactLayer::SensorCustomReceiver) {
        result.is_custom_receiver = true;
        result.group_handler_index.Init(getIndex());
        result.custom_receiver_data.layer.Init(current_info.custom_receiver_data.layer);
    } else {
        result.is_custom_receiver = false;
        result.group_handler_index.Init(getIndex());
        result.data.layer.Init(layer - FirstSensor);
    }
    return result.raw;
}

inline u32 SensorSystemGroupHandler::makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit,
                                                            bool unk) {
    SensorQueryCollisionMask mask;
    mask.layer_mask = layer_mask;
    mask.group_handler_index.Init(getIndex());
    return mask.raw;
}

inline bool SensorSystemGroupHandler::m8() {
    return getIndex() > 0 && getIndex() < 0x400;
}

inline u32 SensorGroupFilter::makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit) {
    return SensorCollisionMask::make(layer).raw;
}

inline ContactLayer SensorGroupFilter::getCollisionFilterInfoLayer(u32 info) {
    return SensorCollisionMask(info).getLayer();
}

inline u32 SensorGroupFilter::makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit,
                                                     bool unk) {
    SensorQueryCollisionMask mask;
    mask.layer_mask = layer_mask;
    return mask.raw;
}

inline GroundHit SensorGroupFilter::getQueryCollisionMaskGroundHit(u32 info) {
    return GroundHit::HitAll;
}

inline void SensorGroupFilter::getCollisionFilterInfoLayerAndGroundHit(u32 info,
                                                                       ContactLayer* layer,
                                                                       GroundHit* ground_hit) {
    SensorCollisionMask mask{info};
    *layer = mask.getLayer();
    *ground_hit = {};
}

inline const char* SensorGroupFilter::getCollisionFilterInfoLayerText(u32 info) {
    return contactLayerToText(getCollisionFilterInfoLayer(info));
}

inline u32 SensorGroupFilter::getCollisionFilterInfoGroupHandlerIdx(u32 info) {
    return SensorCollisionMask(info).group_handler_index;
}

inline u32 SensorGroupFilter::makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit,
                                                      u32 unk5, u32 unk10) {
    return 0;
}

inline void SensorGroupFilter::setSensorLayerCollisionEnabledMask(ContactLayer layer, u32 mask) {
    m_collisionLookupTable[layer - mLayerFirst] = mask;
}

}  // namespace ksys::phys
