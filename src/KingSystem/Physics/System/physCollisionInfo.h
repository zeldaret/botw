#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
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
    sead::Mutex mMutex;
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
