#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcMgr)

void BaseProcMgr::generateProcId(u32* id) {
    *id = mCreatedProcCounter.increment();
}

void BaseProcMgr::registerProc(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcMapCS);
    proc.mMapNode.key().setKey(proc.mName);
    mProcMap.insert(&proc.mMapNode);
}

void BaseProcMgr::unregisterProc(BaseProc& proc) {
    if (!proc.mMapNode.isInserted())
        return;

    auto lock = sead::makeScopedLock(mProcMapCS);
    mProcMap.erase(&proc.mMapNode);
}

void BaseProcMgr::addToPreDeleteList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcPreDeleteListCS);
    mProcPreDeleteList.pushBack(&proc);
}

void BaseProcMgr::doAddToUpdateStateList_(BaseProc& proc) {
    if (mProcUpdateStateList.isNodeLinked(&proc))
        return;

    if (proc.mCreatePriorityState == 1) {
        proc.mCreatePriorityState = 0;
        mProcUpdateStateList.pushFront(&proc);
    } else {
        mProcUpdateStateList.pushBack(&proc);
    }
}

void BaseProcMgr::eraseFromPreDeleteList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcPreDeleteListCS);
    if (mProcPreDeleteList.isNodeLinked(&proc))
        mProcPreDeleteList.erase(&proc);
}

void BaseProcMgr::eraseFromUpdateStateList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcUpdateStateListCS);
    if (mProcUpdateStateList.isNodeLinked(&proc))
        mProcUpdateStateList.erase(&proc);
}

void BaseProcMgr::processPreDeleteList() {
    mStatus = Status::ProcessingPreDeleteList;

    auto lock = sead::makeScopedLock(mProcPreDeleteListCS);
    for (auto& proc : mProcPreDeleteList.robustRange())
        proc.processPreDelete();

    mStatus = Status::Idle;
}

bool BaseProcMgr::hasExtraJobLink(BaseProcJobLink* job_link, s32 idx) {
    for (auto& ptr : mExtraJobLinkArrays[idx]) {
        if (&ptr == job_link)
            return true;
    }
    return false;
}

void BaseProcMgr::clearExtraJobArrays() {
    mExtraJobLinkArrays[0].clear();
    mExtraJobLinkArrays[1].clear();
}

void BaseProcMgr::setActorJobTypeAndPrio(JobType type, s32 prio, bool x) {
    mStatus = Status::ProcessingActorJobs;
    mJobType = type;
    mCurrentlyProcessingPrio = prio;
    mUnk2 = x;
}

void BaseProcMgr::goIdle() {
    mStatus = Status::Idle;
    mJobType = JobType::Invalid;
    mIsPushingJobs = false;
    mUnk2 = false;
    mEnableExtraJobPush = false;
    mCurrentlyProcessingPrio = 8;
}

void BaseProcMgr::clearMode() {
    mMode = Mode::_0;
}

bool BaseProcMgr::isHighPriorityThread() const {
    const auto current_thread = sead::ThreadMgr::instance()->getCurrentThread();

    if (!current_thread)
        return false;

    const auto id = current_thread->getId();

    if (!current_thread->isDefaultPriority())
        return false;

    return id == mMainThreadId || id == mHavokThreadId1 || id == mHavokThreadId2;
}

void BaseProcMgr::incrementUnk3() {
    if (mUnk3 != 0xFF)
        ++mUnk3;
}

void BaseProcMgr::decrementUnk3() {
    if (mUnk3 != 0)
        --mUnk3;
}

sead::CriticalSection* BaseProcMgr::lockProcMap() {
    mProcMapCS.lock();
    return &mProcMapCS;
}

void BaseProcMgr::unlockProcMap() {
    mLastProcMapNode = nullptr;
    mProcMapCS.unlock();
}

}  // namespace ksys::act
