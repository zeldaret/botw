#pragma once

#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <thread/seadMutex.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class CollisionInfoBase {
public:
    CollisionInfoBase() = default;
    virtual ~CollisionInfoBase() = default;

    sead::BitFlag32& getLayerMask(ContactLayerType layer_type);
    const sead::BitFlag32& getLayerMask(ContactLayerType layer_type) const;

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

    bool isLinked() const { return mListNode.isLinked(); }
    static constexpr size_t getListNodeOffset() { return offsetof(CollisionInfo, mListNode); }

private:
    // FIXME: type
    sead::OffsetList<void*> mList;
    sead::ListNode mListNode;
};

inline sead::BitFlag32& CollisionInfoBase::getLayerMask(ContactLayerType layer_type) {
    return mLayerMasks[int(layer_type)];
}

inline const sead::BitFlag32& CollisionInfoBase::getLayerMask(ContactLayerType layer_type) const {
    return mLayerMasks[int(layer_type)];
}

inline void CollisionInfoBase::lock() {
    mMutex.lock();
}

inline void CollisionInfoBase::unlock() {
    mMutex.unlock();
}

}  // namespace ksys::phys
