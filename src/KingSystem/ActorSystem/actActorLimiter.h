#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadStorageFor.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorLimiter {
    SEAD_SINGLETON_DISPOSER(ActorLimiter)
    ActorLimiter() = default;
    ~ActorLimiter() { mLists.destruct(); }

public:
    enum class Category {
        LumberjackTreeDrops = 0,
        DroppedItems = 1,
        PlayerTrash = 2,
        Drops = 3,
        SandSeal = 4,
        Bullets = 5,
        AmiiboDrops = 6,
        _7 = 7,
    };
    static constexpr int NumCategories = 8;

    class List {
    public:
        List() { mActorList.initOffset(offsetof(Node, node)); }
        ~List() { mNodes.freeBuffer(); }

        bool init(sead::Heap* heap, int capacity);
        bool addActor(BaseProc* proc, bool allow_evicting_old_actors);

    private:
        struct Node {
            sead::ListNode node;
            BaseProcLink proc_link;
        };

        sead::Buffer<Node> mNodes;
        sead::OffsetList<Node> mActorList;
        sead::CriticalSection mCritSection;
    };
    KSYS_CHECK_SIZE_NX150(List, 0x68);

    bool init(sead::Heap* heap, const sead::SafeArray<int, NumCategories>& capacities);

    List& get(Category category) { return mLists.ref()[s32(category)]; }
    const List& get(Category category) const { return mLists.ref()[s32(category)]; }

private:
    sead::StorageFor<sead::SafeArray<List, NumCategories>> mLists{sead::ZeroInitializeTag{}};
};
KSYS_CHECK_SIZE_NX150(ActorLimiter, 0x360);

}  // namespace ksys::act
