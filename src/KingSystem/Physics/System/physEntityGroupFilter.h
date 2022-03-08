#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitUtil.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class EntitySystemGroupHandler : public SystemGroupHandler {
public:
    explicit EntitySystemGroupHandler(int i) : SystemGroupHandler(i, ContactLayerType::Entity) {}

    u32 makeCollisionFilterInfo(u32 info, ContactLayer layer, GroundHit ground_hit) override;
    u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) override;
    u32 makeRagdollCollisionFilterInfo(GroundHit ground_hit) override;
    bool m8() override;
};

class EntityGroupFilter : public GroupFilter {
    SEAD_RTTI_OVERRIDE(EntityGroupFilter, GroupFilter)
public:
    static EntityGroupFilter* make(ContactLayer::ValueType first, ContactLayer::ValueType last,
                                   sead::Heap* heap);

    EntityGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last);
    ~EntityGroupFilter() override;

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

    bool shouldContactNeverBeIgnored(ContactLayer layerA, ContactLayer layerB) override;
    u32 makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit) override;
    ContactLayer getCollisionFilterInfoLayer(u32 info) override;
    u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) override;
    GroundHit getQueryCollisionMaskGroundHit(u32 info) override;
    void getCollisionFilterInfoLayerAndGroundHit(u32 info, ContactLayer* layer,
                                                 GroundHit* ground_hit) override;
    const char* getCollisionFilterInfoLayerText(u32 info) override;
    void setLayerCustomMask(ContactLayer layer, u32 mask) override;
    u32 getCollisionFilterInfoGroupHandlerIdx(u32 info) override;

    virtual u32 makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit, u32 unk5,
                                        u32 unk10);
    /// @param layer An entity layer
    virtual void setEntityLayerCollisionEnabledMask(ContactLayer layer, u32 mask);

private:
    /// Checks whether two entities are colliding.
    hkBool testCollisionForEntities(u32 infoA, u32 gh_mask) const;
    /// Checks whether a phantom and an entity are colliding with each other.
    hkBool testCollisionForPhantom(u32 infoPhantom, u32 infoB) const;
    /// Checks whether a ray cast and an entity are colliding with each other.
    hkBool testCollisionForRayCasting(u32 infoRayCast, u32 info) const;

    hkBool shouldHandleGroundCollision(u32 infoA, u32 infoB, ContactLayer::ValueType layerA,
                                       ContactLayer::ValueType layerB) const;
    hkBool shouldHandleWaterCollision(u32 infoA, u32 infoB, ContactLayer::ValueType layerA,
                                      ContactLayer::ValueType layerB) const;

    hkBool testLayerCollision(ContactLayer::ValueType a, ContactLayer::ValueType b) const {
        return m_collisionLookupTable[a] & (1 << b);
    }

    void doInitSystemGroupHandlerLists_(sead::Heap* heap) override;
    int getFreeListIndex(const SystemGroupHandler* handler) override;
    void doInit_(sead::Heap* heap) override;

    /// A ContactLayer::size() x ContactLayer::size() matrix such that M[i][j] indicates
    /// whether contact between layers i and layers j can be ignored.
    /// \see EntityContactListener and shouldContactNeverBeIgnored
    sead::SafeArray<u32, ContactLayer::size()> mLayersThatCanBeIgnored;
};

void receiverMaskEnableLayer(SensorCollisionMask* mask, ContactLayer layer);
bool receiverMaskGetSensorLayerMaskForType(SensorCollisionMask* mask,
                                           const sead::SafeString& receiver_type);
void receiverMaskSetSensorLayerMask(SensorCollisionMask* mask, u32 layer_mask);

u32 orEntityGroundHitMask(u32 mask, GroundHit type);
u32 orEntityGroundHitMask(u32 mask, const sead::SafeString& type);

/// Returns a new collision mask in ground hit mask mode.
/// @param mask A collision mask that has been built using orEntityGroundHitMask.
u32 makeEntityGroundHitMask(ContactLayer layer, u32 mask);

/// Returns a new collision mask with the specified layer.
/// Preserves ground hit mask mode.
u32 makeEntityCollisionMask(ContactLayer layer, u32 mask);

/// Updates the collision mask with the specified ground hit type (*not* mask).
u32 setEntityCollisionMaskGroundHit(GroundHit ground_hit, u32 mask);

inline u32 EntitySystemGroupHandler::makeCollisionFilterInfo(u32 info, ContactLayer layer,
                                                             GroundHit ground_hit) {
    const EntityCollisionMask current_info{info};
    EntityCollisionMask result;

    if (layer == ContactLayer::EntityRagdoll) {
        result.data.layer.Init(layer);
        result.data.unk5.Init(current_info.data.unk5);
        result.data.unk10.Init(current_info.data.unk10);
        result.group_handler_index.Init(getIndex());
        result.data.ground_hit.Init(ground_hit);
        result.unk30 = true;
    } else {
        result.data.layer.Init(layer);
        result.ground_col_mode.Init(current_info.ground_col_mode);
        result.group_handler_index.Init(getIndex());
        result.data.ground_hit.Init(ground_hit);
    }
    return result.raw;
}

inline u32 EntitySystemGroupHandler::makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit,
                                                            bool unk) {
    EntityQueryCollisionMask mask;
    mask.layer_mask = layer_mask;
    mask.group_handler_index.Init(getIndex());
    mask.ground_hit_type.Init(static_cast<GroundHit::ValueType>(int(ground_hit)));
    mask.unk.SetBit(unk);
    return mask.raw;
}

inline u32 EntitySystemGroupHandler::makeRagdollCollisionFilterInfo(GroundHit ground_hit) {
    EntityCollisionMask info;
    info.data.layer.Init(ContactLayer::EntityRagdoll);
    info.group_handler_index.Init(getIndex());
    info.data.ground_hit.Init(ground_hit);
    return info.raw;
}

inline bool EntitySystemGroupHandler::m8() {
    return getIndex() > 0 && getIndex() < 0x400;
}

inline bool EntityGroupFilter::shouldContactNeverBeIgnored(ContactLayer layerA,
                                                           ContactLayer layerB) {
    return (mLayersThatCanBeIgnored[layerA.value()] & (1 << layerB.value())) == 0;
}

inline u32 EntityGroupFilter::makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit) {
    return EntityCollisionMask::make(layer, ground_hit).raw;
}

inline ContactLayer EntityGroupFilter::getCollisionFilterInfoLayer(u32 info) {
    return EntityCollisionMask(info).getLayer();
}

inline u32 EntityGroupFilter::makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit,
                                                     bool unk) {
    EntityQueryCollisionMask mask;
    mask.layer_mask = layer_mask;
    mask.ground_hit_type = ground_hit.value();
    mask.unk.SetBit(unk);
    return mask.raw;
}

inline GroundHit EntityGroupFilter::getQueryCollisionMaskGroundHit(u32 info) {
    return EntityQueryCollisionMask(info).ground_hit_type.Value();
}

inline void EntityGroupFilter::getCollisionFilterInfoLayerAndGroundHit(u32 info,
                                                                       ContactLayer* layer,
                                                                       GroundHit* ground_hit) {
    EntityCollisionMask info_{info};
    *layer = info_.getLayer();
    *ground_hit = info_.getGroundHit();
}

inline const char* EntityGroupFilter::getCollisionFilterInfoLayerText(u32 info) {
    EntityCollisionMask info_{info};
    if (info_.is_ground_hit_mask) {
        return "GroundHitMaskMode";
    }
    return contactLayerToText(getCollisionFilterInfoLayer(info));
}

inline void EntityGroupFilter::setLayerCustomMask(ContactLayer layer, u32 mask) {
    mLayersThatCanBeIgnored[layer] = mask;
}

inline u32 EntityGroupFilter::getCollisionFilterInfoGroupHandlerIdx(u32 info) {
    return EntityCollisionMask(info).group_handler_index;
}

inline u32 EntityGroupFilter::makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit,
                                                      u32 unk5, u32 unk10) {
    EntityCollisionMask info;
    info.data.layer.Init(layer);
    info.data.unk5.Init(unk5);
    info.data.unk10.Init(unk10);
    info.data.ground_hit.Init(ground_hit);
    info.unk30 = true;
    return info.raw;
}

inline void EntityGroupFilter::setEntityLayerCollisionEnabledMask(ContactLayer layer, u32 mask) {
    m_collisionLookupTable[layer] = mask;
}

}  // namespace ksys::phys
