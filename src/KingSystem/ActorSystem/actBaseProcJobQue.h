#pragma once

#include <agl/utl/aglAtomicPtrArray.h>
#include <array>
#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <mc/seadJob.h>
#include <mc/seadJobQueue.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class WorkerMgr;
}

namespace ksys::act {

class BaseProcJobQue {
public:
    BaseProcJobQue();
    BaseProcJobQue(const BaseProcJobQue&) = delete;
    auto operator=(const BaseProcJobQue&) = delete;
    virtual ~BaseProcJobQue();

    void init(sead::Heap* heap);
    bool pushJobQueue(sead::WorkerMgr* worker_mgr, BaseProcJobLists* lists, int priority,
                      JobType type);
    bool pushExtraJobs(sead::FixedSizeJQ* queue, BaseProcJobLists* lists, int priority,
                       JobType type);
    bool pushExtraJobs(sead::FixedSizeJQ* queue,
                       const agl::utl::AtomicPtrArray<BaseProcJobLink>& links);

    void clear() { mNumExtraJobs = 0; }

private:
    bool pushJobs(sead::FixedSizeJQ* queue, BaseProcJobLists* lists, int priority,
                  bool should_reset_job_idx, JobType type);
    bool isIndexValid(int idx) const { return u32(idx) < u32(mPool.size()); }

    int mFreeJobIdx = 0;
    sead::FixedSizeJQ mJobQueue;
    sead::SafeArray<BaseProcJob, 1200> mPool;
    sead::Atomic<int> mNumExtraJobs = 0;
};
KSYS_CHECK_SIZE_NX150(BaseProcJobQue, 0xbc38);

}  // namespace ksys::act
