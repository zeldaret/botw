#pragma once

#include <Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class SystemGroupHandler {
    SEAD_RTTI_BASE(SystemGroupHandler)
public:
    explicit SystemGroupHandler(int index, ContactLayerType layer_type)
        : mIndex(index), mLayerType(layer_type) {}

    virtual ~SystemGroupHandler() = default;
    virtual u32 makeCollisionFilterInfo(u32 info, ContactLayer layer, GroundHit ground_hit) = 0;
    virtual u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) = 0;
    virtual u32 makeRagdollCollisionFilterInfo(GroundHit ground_hit);
    virtual bool m8() = 0;

    int getIndex() const { return mIndex; }
    ContactLayerType getLayerType() const { return mLayerType; }

    const char* getActorName() const { return mActorName; }
    void setActorName(const char* name) { mActorName = name; }

    const char* getActorProfile() const { return mActorProfile; }
    void setActorProfile(const char* name) { mActorProfile = name; }

    /// Remove this handler from the filter it's attached to.
    void removeThis();

    static constexpr auto getFreeListNodeOffset() {
        return offsetof(SystemGroupHandler, mFreeListNode);
    }

    static constexpr auto getUsedListNodeOffset() {
        return offsetof(SystemGroupHandler, mUsedListNode);
    }

protected:
    const char* mActorName = nullptr;
    const char* mActorProfile = nullptr;
    int mIndex = 0;
    ContactLayerType mLayerType{};
    sead::ListNode mFreeListNode;
    sead::ListNode mUsedListNode;
};

class GroupFilter : public hkpGroupFilter {
    SEAD_RTTI_BASE(GroupFilter)
public:
    GroupFilter(ContactLayerType type, ContactLayer::ValueType layer_first,
                ContactLayer::ValueType layer_last);
    ~GroupFilter() override;

    ContactLayer::ValueType getLayerFirst() const { return mLayerFirst; }
    ContactLayer::ValueType getLayerLast() const { return mLayerLast; }
    int getNumLayers() const { return getLayerLast() - getLayerFirst() + 1; }
    ContactLayerType getLayerType() const { return mLayerType; }

    void initFilter(sead::Heap* heap);
    /// Frees all memory associated with this instance and then self-destructs.
    /// @warning Do not use this filter after a call to destroy!
    void destroy();

    SystemGroupHandler* addSystemGroupHandler(int free_list_idx);
    void removeSystemGroupHandler(SystemGroupHandler* handler);

    void setLayerCollisionEnabledMask(ContactLayer layer, u32 mask) {
        m_collisionLookupTable[layer - getLayerFirst()] = mask;
    }

    /// Indicates whether contact between layerA and layerB should never be ignored,
    /// even if the corresponding rigid bodies are configured to ignore each other's layer.
    virtual bool shouldContactNeverBeIgnored(ContactLayer layerA, ContactLayer layerB) {
        return true;
    }

    /// Make a collision filter mask with the specified layer and ground hit type.
    virtual u32 makeCollisionFilterInfo(ContactLayer layer, GroundHit ground_hit) = 0;

    /// Get the layer from a collision filter mask.
    virtual ContactLayer getCollisionFilterInfoLayer(u32 info) = 0;

    /// Make a query collision mask with the specified layer mask, ground hit type and flag.
    virtual u32 makeQueryCollisionMask(u32 layer_mask, GroundHit ground_hit, bool unk) = 0;

    /// Get the ground hit type from a query collision mask.
    virtual GroundHit getQueryCollisionMaskGroundHit(u32 info) = 0;

    /// Get the layer and ground hit type from a collision filter mask.
    virtual void getCollisionFilterInfoLayerAndGroundHit(u32 info, ContactLayer* layer,
                                                         GroundHit* ground_hit) = 0;

    /// Get the layer from a collision filter mask.
    virtual const char* getCollisionFilterInfoLayerText(u32 info) = 0;

    virtual void setLayerCustomMask(ContactLayer layer, u32 mask) {}

    /// Get the group handler index from a collision filter mask.
    virtual u32 getCollisionFilterInfoGroupHandlerIdx(u32 info) = 0;

protected:
    virtual void doInitSystemGroupHandlerLists_(sead::Heap* heap) = 0;
    virtual int getFreeListIndex(const SystemGroupHandler* handler) = 0;

    /// Initialises internal state.
    virtual void doInit_(sead::Heap* heap) {}

    ContactLayer::ValueType mLayerFirst{};
    ContactLayer::ValueType mLayerLast{};
    ContactLayerType mLayerType{};
    bool mInhibitCollisions{};
    sead::SafeArray<sead::OffsetList<SystemGroupHandler>, 2> mFreeLists;
    sead::CriticalSection mCS;
    sead::OffsetList<SystemGroupHandler> mUsedList;
};

}  // namespace ksys::phys
