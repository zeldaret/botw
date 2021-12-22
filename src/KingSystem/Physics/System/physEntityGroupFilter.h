#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physGroupFilter.h"

namespace ksys::phys {

class EntitySystemGroupHandler : public SystemGroupHandler {
public:
    using SystemGroupHandler::SystemGroupHandler;

    u32 m5() override;
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
    void doInitSystemGroupHandlerLists_(sead::Heap* heap) override;
    int getFreeListIndex(const SystemGroupHandler* handler) override;
    void doInit_(sead::Heap* heap) override;
    virtual void m14();
    virtual void m15();

    sead::SafeArray<u32, ContactLayer::size()> mMasks;
};

}  // namespace ksys::phys
