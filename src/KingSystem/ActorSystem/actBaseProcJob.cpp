#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::act {

static util::InitTimeInfo sInfo;

BaseProcJobLink::BaseProcJobLink(BaseProc* proc, u8 priority)
    : TListNode(proc), mPriority(priority), mNewPriority(priority), mPriority2(3),
      mNewPriority2(3) {}

sead::TListNode<BaseProc*>* BaseProcJobList::front() const {
    for (const auto& list : lists) {
        if (list.front())
            return list.front();
    }
    return nullptr;
}

sead::TListNode<BaseProc*>* BaseProcJobList::next(BaseProcJobLink* link) const {
    if (auto* next = lists[link->getPriority2() >> 1].next(link))
        return next;

    for (int i = (link->getPriority2() >> 1) + 1; i < lists.size(); ++i) {
        if (lists[i].front())
            return lists[i].front();
    }

    return nullptr;
}

int BaseProcJobList::size() const {
    return lists[0].size() + lists[1].size();
}

void BaseProcJobLists::pushJob(BaseProcJobLink& link) {
    if (link.isLinked())
        return;

    auto& list = mLists[link.getPriority()].lists[link.getPriority2() >> 1];
    if (link.getPriority2() % 2 == 0)
        list.pushFront(&link);
    else
        list.pushBack(&link);
}

void BaseProcJobLists::eraseJob(BaseProcJobLink& link) {
    if (link.isLinked())
        link.erase();
}

sead::TListNode<BaseProc*>* BaseProcJobLists::getJobWithTopPriority() const {
    for (const auto& list : mLists) {
        if (auto* result = list.front())
            return result;
    }
    return nullptr;
}

sead::TListNode<BaseProc*>*
BaseProcJobLists::getNextJobWithTopPriority(BaseProcJobLink* link) const {
    if (auto* next = getNextJob(link))
        return next;

    for (u32 i = link->getPriority() + 1; i < u32(mLists.size()); ++i) {
        if (auto* next = mLists[i].front())
            return next;
    }

    return nullptr;
}

sead::TListNode<BaseProc*>* BaseProcJobLists::getNextJob(BaseProcJobLink* link) const {
    return mLists[link->getPriority()].next(link);
}

void BaseProcJob::invoke() {
    BaseProcMgr::instance()->jobInvoked(mJobLink, mRequiredCalcRounds);
}

}  // namespace ksys::act
