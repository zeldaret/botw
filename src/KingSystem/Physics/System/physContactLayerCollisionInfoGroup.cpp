#include "KingSystem/Physics/System/physContactLayerCollisionInfoGroup.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

ContactLayerCollisionInfoGroup::ContactLayerCollisionInfoGroup(ContactLayer layer,
                                                               const sead::SafeString& name)
    : sead::INamable(name), mLayer(layer) {}

ContactLayerCollisionInfoGroup::~ContactLayerCollisionInfoGroup() = default;

ContactLayerCollisionInfoGroup* ContactLayerCollisionInfoGroup::make(sead::Heap* heap,
                                                                     ContactLayer layer,
                                                                     int capacity,
                                                                     const sead::SafeString& name) {
    return System::instance()->makeContactLayerCollisionInfoGroup(heap, layer, capacity, name);
}

void ContactLayerCollisionInfoGroup::free(ContactLayerCollisionInfoGroup* group) {
    System::instance()->freeContactLayerCollisionInfoGroup(group);
}

void ContactLayerCollisionInfoGroup::init(sead::Heap* heap, int capacity) {
    mCollisionInfoInstances.allocBuffer(capacity, heap);
    mLayers.allocBufferAssert(capacity, heap);
}

void ContactLayerCollisionInfoGroup::finalize() {
    mCollisionInfoInstances.freeBuffer();
    mLayers.freeBuffer();
}

// NON_MATCHING: trivial reordering
void ContactLayerCollisionInfoGroup::addLayer(ContactLayer layer) {
    auto& info = mLayers[mCollisionInfoInstances.size()];
    info.layer = layer;
    info.layer_gt = mLayer > layer;
    info.layer_le = !info.layer_gt;

    auto* collision_info = System::instance()->trackLayerPair(mLayer, layer);
    mCollisionInfoInstances.pushBack(collision_info);
}

void ContactLayerCollisionInfoGroup::ensureLayersAreTracked() {
    for (int i = 0; i < mCollisionInfoInstances.size(); ++i) {
        System::instance()->trackLayerPair(mLayer, mLayers[i].layer);
    }
}

ContactLayerCollisionInfoGroup::CollidingBodiesIterator::CollidingBodiesIterator(
    const ContactLayerCollisionInfoGroup* group, int index, IsStart start)
    : mGroup(group), mInfoIndex(index) {
    if (!bool(start))
        return;

    initIterator(group);

    // If there is no colliding body, turn this iterator into an end iterator.
    if (!mCollidingBodiesEntry) {
        mInfo = nullptr;
        mInfoIndex = group->mCollisionInfoInstances.size();
    }
}

ContactLayerCollisionInfoGroup::CollidingBodiesIterator::~CollidingBodiesIterator() {
    if (mInfo)
        mInfo->unlock();
}

void ContactLayerCollisionInfoGroup::CollidingBodiesIterator::initIterator(
    const ContactLayerCollisionInfoGroup* group) {
    for (mInfoIndex = 0; mInfoIndex < group->mCollisionInfoInstances.size(); ++mInfoIndex) {
        mInfo = group->mCollisionInfoInstances[mInfoIndex];
        if (!mInfo)
            continue;

        mInfo->lock();
        mCollidingBodiesEntry = mInfo->getCollidingBodies().front();
        if (mCollidingBodiesEntry) {
            // Keep the ContactLayerCollisionInfo locked.
            break;
        }
        // Otherwise, unlock the current ContactLayerCollisionInfo and try the next one.
        mInfo->unlock();
    }
}

ContactLayerCollisionInfoGroup::CollidingBodiesIterator&
ContactLayerCollisionInfoGroup::CollidingBodiesIterator::operator++() {
    auto* group = mGroup;

    mCollidingBodiesEntry = mInfo->getCollidingBodies().next(mCollidingBodiesEntry);
    if (mCollidingBodiesEntry)
        return *this;

    // If we reached the last entry in the current ContactLayerCollisionInfo,
    // move on to the next one.

    ++mInfoIndex;
    for (; mInfoIndex < group->mCollisionInfoInstances.size(); ++mInfoIndex) {
        auto* next_info = group->mCollisionInfoInstances[mInfoIndex];
        if (!next_info)
            continue;

        mInfo->unlock();
        mInfo = next_info;
        mInfo->lock();
        mCollidingBodiesEntry = mInfo->getCollidingBodies().front();
        if (mCollidingBodiesEntry)
            break;
    }

    return *this;
}

}  // namespace ksys::phys
