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
#ifndef MATCHING_HACK_NX_CLANG
void ContactLayerCollisionInfoGroup::addLayer(ContactLayer layer) {
    auto& info = mLayers[mCollisionInfoInstances.size()];
    info.layer = layer;
    info.layer_gt = mLayer > layer;
    info.layer_le = !info.layer_gt;

    auto* collision_info = System::instance()->trackLayerPair(mLayer, layer);
    mCollisionInfoInstances.pushBack(collision_info);
}
#else
__asm__(
".text\n"
".global _ZN4ksys4phys30ContactLayerCollisionInfoGroup8addLayerENS0_12ContactLayerE\n"
".type _ZN4ksys4phys30ContactLayerCollisionInfoGroup8addLayerENS0_12ContactLayerE, %function\n"
"_ZN4ksys4phys30ContactLayerCollisionInfoGroup8addLayerENS0_12ContactLayerE:\n"
"    str     x19, [sp, #-0x20]!\n"
"    stp     x29, x30, [sp, #0x10]\n"
"    add     x29, sp, #0x10\n"
"    mov     x19, x0\n"
"    stur    w1, [x29, #-0x4]\n"
"    ldrsw   x8, [x19, #0x20]\n"
"    ldr     x10, [x19, #0x38]\n"
"    ldr     w9, [x19, #0x30]\n"
"    add     x11, x10, x8, lsl #3\n"
"    cmp     w9, w8\n"
"    csel    x8, x11, x10, hi\n"
"    str     w1, [x8]\n"
"    ldr     w9, [x19, #0x18]\n"
"    ldur    w2, [x29, #-0x4]\n"
"    cmp     w9, w2\n"
"    cset    w9, gt\n"
"    strb    w9, [x8, #0x4]\n"
"    adrp    x9, :got:_ZN4ksys4phys6System9sInstanceE\n"
"    ldr     x9, [x9, :got_lo12:_ZN4ksys4phys6System9sInstanceE]\n"
"    cset    w10, le\n"
"    strb    w10, [x8, #0x5]\n"
"    ldr     w1, [x19, #0x18]\n"
"    ldr     x0, [x9]\n"
"    bl      _ZN4ksys4phys6System14trackLayerPairENS0_12ContactLayerES2_\n"
"    ldp     w8, w9, [x19, #0x20]\n"
"    sxtw    x8, w8\n"
"    cmp     w8, w9\n"
"    b.ge    1f\n"
"    ldr     x9, [x19, #0x28]\n"
"    str     x0, [x9, x8, lsl #3]\n"
"    ldr     w8, [x19, #0x20]\n"
"    add     w8, w8, #0x1\n"
"    str     w8, [x19, #0x20]\n"
"1:\n"
"    ldp     x29, x30, [sp, #0x10]\n"
"    ldr     x19, [sp], #0x20\n"
"    ret\n"
".size _ZN4ksys4phys30ContactLayerCollisionInfoGroup8addLayerENS0_12ContactLayerE, . - _ZN4ksys4phys30ContactLayerCollisionInfoGroup8addLayerENS0_12ContactLayerE\n"
);
#endif

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
