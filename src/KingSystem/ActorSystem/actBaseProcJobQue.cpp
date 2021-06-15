#include "KingSystem/ActorSystem/actBaseProcJobQue.h"
#include <mc/seadWorkerMgr.h>
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::act {

BaseProcJobQue::BaseProcJobQue() = default;

BaseProcJobQue::~BaseProcJobQue() {
    mJobQueue.clear();
}

void BaseProcJobQue::init(sead::Heap* heap) {
    mJobQueue.initialize(mPool.size(), heap);
    mJobQueue.clear();
    for (u32 i = 0; i < sead::CoreInfo::getNumCores(); ++i)
        mJobQueue.setGranularity(i, 1);
}

bool BaseProcJobQue::pushJobQueue(sead::WorkerMgr* worker_mgr, BaseProcJobLists* lists,
                                  int priority, JobType type) {
    mJobQueue.clear();
    const bool ok = pushJobs(&mJobQueue, lists, priority, true, type);
    if (ok) {
        sead::CoreIdMask cores{sead::CoreId::cMain, sead::CoreId::cSub1, sead::CoreId::cSub2};
        worker_mgr->pushJobQueue("BaseProcJobQue::pushJobQueue", &mJobQueue, cores,
                                 sead::SyncType::cNoSync, sead::JobQueuePushType::cForward);
    }
    return ok;
}

bool BaseProcJobQue::pushJobs(sead::FixedSizeJQ* queue, BaseProcJobLists* lists, int priority,
                              bool should_reset_job_idx, JobType type) {
    if (should_reset_job_idx)
        mFreeJobIdx = 0;

    const auto& list = lists->getList(priority);
    const int num_jobs = list.size();
    int num_remaining_jobs = num_jobs;
    if (num_jobs == 0)
        return false;

    const int capacity = int(mPool.size() / 2);

    const int num_free = capacity - mFreeJobIdx;
    if (num_free <= 0)
        return false;

    auto* link = static_cast<BaseProcJobLink*>(list.front());

    if (num_remaining_jobs > num_free) {
        if (num_remaining_jobs <= 0)
            return true;

        int rounds = num_remaining_jobs / num_free + 1;
        do {
            auto* const batch_head = link;

            for (int i = 1; link && i <= rounds; ++i)
                link = static_cast<BaseProcJobLink*>(lists->getNextJob(link));

            mPool[mFreeJobIdx].set(batch_head, rounds);
            queue->enque(&mPool[mFreeJobIdx]);
            num_remaining_jobs -= rounds;
            rounds = std::min(rounds, num_remaining_jobs);
            ++mFreeJobIdx;
        } while (num_remaining_jobs > 0 && num_remaining_jobs > capacity - mFreeJobIdx);
    }

    for (int i = 1; link && i <= num_remaining_jobs; ++i) {
        link->getProc()->onJobPush(type);
        if (!link->getProc()->shouldSkipJobPush(type)) {
            mPool[mFreeJobIdx].set(link, 1);
            queue->enque(&mPool[mFreeJobIdx]);
            ++mFreeJobIdx;
        }
        link = static_cast<BaseProcJobLink*>(lists->getNextJob(link));
    }

    return true;
}

// NON_MATCHING: sxtw + madd -> smaddl
bool BaseProcJobQue::pushExtraJobs(sead::FixedSizeJQ* queue, BaseProcJobLists* lists, int priority,
                                   JobType type) {
    const auto& list = lists->getList(priority);
    if (list.size() == 0)
        return false;

    for (auto* link = static_cast<BaseProcJobLink*>(list.front()); link;
         link = static_cast<BaseProcJobLink*>(lists->getNextJob(link))) {
        const auto idx = mNumExtraJobs.increment();
        if (idx >= mPool.size())
            return false;

        link->getProc()->onJobPush(type);

        if (!link->getProc()->shouldSkipJobPush(type)) {
            mPool[idx].set(link, 1);
            if (!queue->enque(&mPool[idx]))
                return false;
        }
    }

    return true;
}

bool BaseProcJobQue::pushExtraJobs(sead::FixedSizeJQ* queue,
                                   const agl::utl::AtomicPtrArray<BaseProcJobLink>& links) {
    if (links.size() <= 0)
        return false;

    for (auto it = links.begin(), end = links.end(); it != end; ++it) {
        const auto idx = mNumExtraJobs.increment();
        if (idx >= mPool.size())
            return false;

        mPool[idx].mJobLink = &*it;
        mPool[idx].mRequiredCalcRounds = 1;
        if (!queue->enque(&mPool[idx]))
            return false;
    }

    return true;
}

}  // namespace ksys::act
