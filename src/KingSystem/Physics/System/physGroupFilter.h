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
    virtual u32 m6() = 0;
    virtual u32 m7();
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

    virtual bool m2() { return true; }
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void setLayerCustomMask(ContactLayer layer, u32 mask) {}
    virtual void m10() = 0;

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
