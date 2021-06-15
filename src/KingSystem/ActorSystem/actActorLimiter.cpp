#include "KingSystem/ActorSystem/actActorLimiter.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace ksys::act {

bool ActorLimiter::List::init(sead::Heap* heap, int capacity) {
    mNodes.allocBufferAssert(capacity, heap);
    if (!mNodes.isBufferReady())
        return false;

    for (auto& node : mNodes)
        mActorList.pushBack(&node);

    return true;
}

bool ActorLimiter::List::addActor(BaseProc* proc, bool allow_evicting_old_actors) {
    const auto lock = sead::makeScopedLock(mCritSection);

    // Find a free node.
    Node* target_node = nullptr;
    for (auto& node : mActorList) {
        if (node.proc_link.hasProc())
            continue;

        mActorList.erase(&node);
        target_node = &node;
        break;
    }

    if (target_node == nullptr) {
        if (!allow_evicting_old_actors)
            return false;

        target_node = mActorList.popFront();
        if (target_node) {
            ActorConstDataAccess acc;
            acquireActor(&target_node->proc_link, &acc);

            // Priority material actors will not be evicted if possible.
            if (acc.hasTag(tags::PriorityMaterial)) {
                mActorList.pushBack(target_node);
                target_node = mActorList.popFront();
                if (target_node)
                    acquireActor(&target_node->proc_link, &acc);
            }

            acc.deleteEx(BaseProc::DeleteReason::_f);
        }

        if (target_node == nullptr)
            return false;
    }

    target_node->proc_link.acquire(proc, false);
    mActorList.pushBack(target_node);
    return true;
}

SEAD_SINGLETON_DISPOSER_IMPL(ActorLimiter)

bool ActorLimiter::init(sead::Heap* heap, const sead::SafeArray<int, NumCategories>& capacities) {
    for (s32 i = 0; i < NumCategories; ++i) {
        if (!mLists.ref()[i].init(heap, capacities[i]))
            return false;
    }
    return true;
}

}  // namespace ksys::act
