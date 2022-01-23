#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitUtil.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physGroupFilter.h"

namespace ksys::phys {

class EntitySystemGroupHandler : public SystemGroupHandler {
public:
    explicit EntitySystemGroupHandler(int i) : SystemGroupHandler(i, ContactLayerType::Entity) {}

    u32 makeCollisionFilterInfo(u32 info, ContactLayer layer, GroundHit ground_hit) override;
    u32 m6() override;
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

    bool m2() override { return GroupFilter::m2(); }
    void m3() override {}
    void m4() override {}
    void m5() override {}
    void m6() override {}
    void m7() override {}
    void m8() override {}

    void setLayerCustomMask(ContactLayer layer, u32 mask) override { mMasks[layer] = mask; }

    void m10() override {}

private:
    hkBool isCollisionEnabled(u32 infoA, u32 infoB) const;
    hkBool isCollisionEnabledPhantom(u32 infoPhantom, u32 infoB) const;

    void doInitSystemGroupHandlerLists_(sead::Heap* heap) override;
    int getFreeListIndex(const SystemGroupHandler* handler) override;
    void doInit_(sead::Heap* heap) override;
    virtual void m14();
    virtual void m15();

    sead::SafeArray<u32, ContactLayer::size()> mMasks;
};

void receiverMaskEnableLayer(ReceiverMask* mask, ContactLayer layer);
bool receiverMaskGetSensorLayerMaskForType(ReceiverMask* mask,
                                           const sead::SafeString& receiver_type);
void receiverMaskSetSensorLayerMask(ReceiverMask* mask, u32 layer_mask);

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

}  // namespace ksys::phys
