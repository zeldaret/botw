#pragma once

#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <thread/seadMutex.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class RigidBody;

struct CollidingBodies {
    RigidBody* bodies[2];
    sead::ListNode list_node;

    static constexpr size_t getListNodeOffset() { return offsetof(CollidingBodies, list_node); }
};

class CollisionInfoBase {
public:
    CollisionInfoBase() = default;
    virtual ~CollisionInfoBase() = default;

    sead::BitFlag32& getLayerMask(ContactLayerType layer_type);
    const sead::BitFlag32& getLayerMask(ContactLayerType layer_type) const;

    void enableLayer(ContactLayer layer);
    void disableLayer(ContactLayer layer);
    bool isLayerEnabled(ContactLayer layer) const;

    void lock();
    void unlock();

private:
    // One layer mask for layer type (entity/sensor).
    sead::SafeArray<sead::BitFlag32, 2> mLayerMasks;
    sead::Mutex mMutex{nullptr,
                       sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
};

class CollisionInfo : public CollisionInfoBase, public sead::INamable {
public:
    static CollisionInfo* make(sead::Heap* heap, const sead::SafeString& name);
    static void free(CollisionInfo* info);

    explicit CollisionInfo(const sead::SafeString& name);
    ~CollisionInfo() override;

    sead::OffsetList<CollidingBodies>& getCollidingBodies() { return mCollidingBodies; }
    const sead::OffsetList<CollidingBodies>& getCollidingBodies() const { return mCollidingBodies; }

    bool isLinked() const { return mListNode.isLinked(); }
    static constexpr size_t getListNodeOffset() { return offsetof(CollisionInfo, mListNode); }

private:
    sead::OffsetList<CollidingBodies> mCollidingBodies;
    sead::ListNode mListNode;
};

inline sead::BitFlag32& CollisionInfoBase::getLayerMask(ContactLayerType layer_type) {
    return mLayerMasks[int(layer_type)];
}

inline const sead::BitFlag32& CollisionInfoBase::getLayerMask(ContactLayerType layer_type) const {
    return mLayerMasks[int(layer_type)];
}

inline void CollisionInfoBase::enableLayer(ContactLayer layer) {
    const u32 mask = makeContactLayerMask(layer);
    getLayerMask(getContactLayerType(layer)).set(mask);
}

inline void CollisionInfoBase::disableLayer(ContactLayer layer) {
    getLayerMask(getContactLayerType(layer)).resetBit(getContactLayerBaseRelativeValue(layer));
}

inline bool CollisionInfoBase::isLayerEnabled(ContactLayer layer) const {
    const auto& mask = getLayerMask(getContactLayerType(layer));
    return mask.isOnBit(getContactLayerBaseRelativeValue(layer));
}

inline void CollisionInfoBase::lock() {
    mMutex.lock();
}

inline void CollisionInfoBase::unlock() {
    mMutex.unlock();
}

}  // namespace ksys::phys
