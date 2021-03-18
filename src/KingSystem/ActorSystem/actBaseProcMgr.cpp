#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include <mc/seadWorkerMgr.h>
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actBaseProcDeleter.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actBaseProcInitializer.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/ActorSystem/actBaseProcJobQue.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcMgr)

BaseProcMgr::BaseProcMgr() {
    mProcPreDeleteList.initOffset(offsetof(BaseProc, mPreDeleteListNode));
    mProcUpdateStateList.initOffset(offsetof(BaseProc, mUpdateStateListNode));
}

BaseProcMgr::~BaseProcMgr() {
    if (mProcJobQue) {
        delete mProcJobQue;
        mProcJobQue = nullptr;
    }

    mJobLists.freeBuffer();

    if (mProcInitializer) {
        delete mProcInitializer;
        mProcInitializer = nullptr;
    }

    if (mProcDeleter) {
        delete mProcDeleter;
        mProcDeleter = nullptr;
    }

    BaseProcHeapMgr::deleteInstance();
}

// NON_MATCHING: mJobLists.allocBufferAssert - BaseProcJobLists ctor
void BaseProcMgr::init(sead::Heap* heap, s32 num_job_types, u32 main_thread_id,
                       u32 havok_thread_id1, u32 havok_thread_id2,
                       const BaseProcInitializerArgs& initializer_args) {
    mProcJobQue = new (heap) BaseProcJobQue;
    mProcJobQue->init(heap);

    mJobLists.allocBufferAssert(num_job_types, heap);

    mProcInitializer = new (heap) BaseProcInitializer;
    mProcInitializer->init(heap, initializer_args);

    mProcDeleter = new (heap) BaseProcDeleter;
    BaseProcDeleter::InitArg deleter_arg;
    deleter_arg.heap = heap;
    deleter_arg.task_queue = mProcInitializer->getTaskQueue();
    deleter_arg.task_queue_size = 2048;
    mProcDeleter->init(deleter_arg);

    mMainThreadId = main_thread_id;
    mHavokThreadId1 = havok_thread_id1;
    mHavokThreadId2 = havok_thread_id2;

    BaseProcHeapMgr::createInstance(heap);
    BaseProcLinkDataMgr::createInstance(heap);
}

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

bool BaseProcMgr::requestPreDelete(BaseProc& proc) {
    return mProcDeleter->requestPreDelete(&proc);
}

void BaseProcMgr::requestUnloadActorParam(ActorParam* param) {
    return mProcDeleter->requestUnloadActorParam(param);
}

void BaseProcMgr::addToPreDeleteList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcPreDeleteListCS);
    mProcPreDeleteList.pushFront(&proc);
}

void BaseProcMgr::eraseFromPreDeleteList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcPreDeleteListCS);
    if (mProcPreDeleteList.isNodeLinked(&proc))
        mProcPreDeleteList.erase(&proc);
}

void BaseProcMgr::pushJob(BaseProc& proc, JobType type) {
    if (proc.isSleep() || !proc.hasJobType_(type))
        return;

    getJobLists(type).pushJob(proc.getJobHandler(type)->getLink());
}

void BaseProcMgr::pushJobs(BaseProc& proc) {
    for (u32 i = 0; i < u32(mJobLists.size()); ++i) {
        pushJob(proc, JobType(i));
    }
}

void BaseProcMgr::eraseJob(BaseProc& proc, JobType type) {
    auto* handler = proc.getJobHandler(type);
    if (handler)
        getJobLists(type).eraseJob(handler->getLink());
}

void BaseProcMgr::eraseJobs(BaseProc& proc) {
    for (u32 i = 0; i < u32(mJobLists.size()); ++i) {
        auto* handler = proc.getJobHandler(JobType(i));
        if (handler)
            mJobLists[i].eraseJob(handler->getLink());
    }
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

BaseProcMgr::ExtraJobLinkArray& BaseProcMgr::getExtraJobs() {
    return mExtraJobLinkArrays.ref()[mCurrentExtraJobArrayIdx];
}

void BaseProcMgr::swapExtraJobArray() {
    mCurrentExtraJobArrayIdx ^= 1;
    getExtraJobs().clear();
}

bool BaseProcMgr::checkJobPushState() const {
    return mEnableExtraJobPush && mUnk4 != 1;
}

void BaseProcMgr::pushJobQueues(sead::WorkerMgr* mgr, JobType type, bool x) {
    if (!checkJobPushState())
        return;

    mJobType = type;
    const auto type_ = mJobType;
    mStatus = Status::ProcessingActorJobs;
    mIsPushingJobs = true;
    mUnk2 = x;

    int i = 0;
    do {
        mPushActorJobType3InsteadOf6 = false;

        auto& lists = getJobLists(type_);
        for (int priority = 0; priority < 8; ++priority) {
            mCurrentlyProcessingPrio = priority;
            if (mProcJobQue->pushJobQueue(mgr, &lists, priority, type_)) {
                mgr->run();
                mgr->sync();
            }
        }

        mCurrentlyProcessingPrio = 8;
        ++i;
    } while (mPushActorJobType3InsteadOf6 && i < 8);

    mIsPushingJobs = false;
    mUnk2 = false;
    mStatus = Status::Idle;
    mJobType = JobType::Invalid;
}

bool BaseProcMgr::pushExtraJobsEx(sead::FixedSizeJQ* jq, JobType type, u8 priority, bool x,
                                  bool y) {
    if (!checkJobPushState())
        return false;

    if (x) {
        mUnk2 = y;
        auto* queue = mProcJobQue;
        mStatus = Status::ProcessingActorJobs;
        mJobType = type;
        mCurrentlyProcessingPrio = priority;
        queue->clear();
    }

    const auto type_ = JobType(u8(type));
    mIsPushingJobs = true;
    mProcJobQue->pushExtraJobs(jq, &getJobLists(type_), priority, type_);
    return true;
}

bool BaseProcMgr::pushExtraJobsForCurrentTypeAndPrio(sead::FixedSizeJQ* jq,
                                                     ExtraJobLinkArray* array) {
    if (!checkJobPushState())
        return false;
    if (array)
        mProcJobQue->pushExtraJobs(jq, *array);
    return true;
}

void BaseProcMgr::setJobType(JobType type) {
    mProcJobQue->clear();
    mJobType = type;
}

bool BaseProcMgr::pushPreCalcJobs(sead::FixedSizeJQ* jq, JobType type, u8 prio, bool x, bool y) {
    if (!checkJobPushState())
        return false;

    if (x) {
        mStatus = Status::ProcessingActorJobs;
        mJobType = type;
        mCurrentlyProcessingPrio = prio;
        mUnk2 = y;
    }

    const auto type_ = JobType(u8(type));
    mProcJobQue->pushExtraJobs(jq, &getJobLists(type_), prio, type_);
    return true;
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

void BaseProcMgr::jobInvoked(BaseProcJobLink* link, s32 required_calc_rounds) {
    if (required_calc_rounds == 1) {
        link->getProc()->jobInvoked(mJobType);
        return;
    }

    const auto& lists = getJobLists(mJobType);
    for (int i = 0; link && [&] { return i < required_calc_rounds; }(); ++i) {
        link->getProc()->jobInvoked(mJobType);
        link = static_cast<BaseProcJobLink*>(lists.getNextJob(link));
    }
}

bool BaseProcMgr::isSpecialJobType(JobType type) const {
    return mSpecialJobTypesMask.isOnBit(int(type));
}

void BaseProcMgr::addSpecialJobTypes(u16 mask) {
    mSpecialJobTypesMask.set(mask);
}

void BaseProcMgr::removeSpecialJobTypes(u16 mask) {
    mSpecialJobTypesMask.reset(mask);
}

void BaseProcMgr::calc() {
    ActorSystem::instance()->onBaseProcMgrCalc();
    mProcInitializer->deleteThreadIfPaused();

    if (mIsInitialisingQuestMgrMaybe)
        return;

    if (!mProcUpdateStateList.isEmpty()) {
        const auto lock = sead::makeScopedLock(mProcUpdateStateListCS);
        mStatus = Status::ProcessingUpdateStateList;

        for (auto& proc : mProcUpdateStateList)
            proc.processStateUpdate(mCounter);

        for (auto it = mProcUpdateStateList.robustBegin(), end = mProcUpdateStateList.robustEnd();
             it != end; ++it) {
            it->afterUpdateState_();
            if (it->mStateFlags.isZero()) {
                mProcUpdateStateList.erase(std::addressof(*it));
            }
        }

        mStatus = Status::Idle;
    }

    ++mCounter;
}

void BaseProcMgr::clearMode() {
    mMode = Mode::_0;
}

sead::CriticalSection* BaseProcMgr::lockProcMap() {
    mProcMapCS.lock();
    return &mProcMapCS;
}

void BaseProcMgr::unlockProcMap() {
    mLastProcMapNode = nullptr;
    mProcMapCS.unlock();
}

void BaseProcMgr::deleteAllProcs() {
    auto procs =
        getProcs(ProcFilter::Sleeping | ProcFilter::Initializing | ProcFilter::SkipAccessCheck);
    while (auto* proc = procs.next()) {
        if (!proc->mFlags.isOn(BaseProc::Flags::DoNotDelete))
            proc->deleteLater(BaseProc::DeleteReason::BaseProcMgrDeleteAll);
    }
}

bool BaseProcMgr::hasFinishedDeletingAllProcs() {
    auto procs = getProcs(ProcFilter::Sleeping | ProcFilter::DeletedOrDeleting |
                          ProcFilter::Initializing | ProcFilter::SkipAccessCheck);
    while (auto* proc = procs.next()) {
        if (!proc->mFlags.isOn(BaseProc::Flags::DoNotDelete))
            return false;
    }
    return mNumPendingDeletions == 0;
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

bool BaseProcMgr::isAccessingProcSafe(BaseProc* proc, BaseProc* other) const {
    [[maybe_unused]] const auto current_thread = sead::ThreadMgr::instance()->getCurrentThread();

    if (!isHighPriorityThread())
        return true;

    if (mUnk2)
        return true;

    if (other) {
        if (other == proc)
            return true;
        if (other->getConnectedCalcChild() == proc)
            return true;
        if (other->getConnectedCalcParent() == proc)
            return true;
    }

    if (!mIsPushingJobs)
        return true;

    const auto type = mJobType;

    if (type == JobType::Invalid || mStatus != Status::ProcessingActorJobs) {
#ifdef MATCHING_HACK_NX_CLANG
        if (proc->isInit()) {
        fail:
            return false;
        }
        return true;
#else
        return !proc->isInit();
#endif
    }

    if (auto* handler = proc->getJobHandler(type)) {
        u8 priority = handler->getLink().getPriority();
        while ((proc = proc->getConnectedCalcParent())) {
            if (auto* h = proc->getJobHandler(type))
                priority = h->getLink().getPriority();
        }
        if (mCurrentlyProcessingPrio != priority)
            return true;
    } else if (!proc->isInit()) {
        return true;
    }
#ifdef MATCHING_HACK_NX_CLANG
    goto fail;
#else
    return false;
#endif
}

bool BaseProcMgr::requestCreateProc(const BaseProcCreateRequest& req) {
    return mProcInitializer->requestCreateBaseProc(req);
}

BaseProc* BaseProcMgr::createProc(const BaseProcCreateRequest& req) {
    return mProcInitializer->createBaseProc(req);
}

struct ProcForEachContextData {
    inline void handle(BaseProcMapNode* node) const {
        if (BaseProcMgr::instance()->checkFilters(node->proc(), filters))
            callback->invoke(node->proc());
    }

    BaseProcMgr::ProcFilters filters;
    sead::IDelegate1<BaseProc*>* callback{};
};

struct ProcForEachContext {
    void forEach(util::StrTreeMapNode* node) {  // NOLINT(readability-make-member-function-const)
        for (auto it = static_cast<BaseProcMapNode*>(node); it; it = it->next())
            data->handle(it);
    }

    ProcForEachContextData* data;
};

inline bool BaseProcMgr::checkFilters(BaseProc* proc, ProcFilters filters) const {
    if (proc->isDeleting() && filters.isOff(ProcFilter::Deleting))
        return false;

    if (!proc->isInitialized() && filters.isOff(ProcFilter::Uninitialized))
        return false;

    if (proc->isSleep() && filters.isOff(ProcFilter::Sleeping))
        return false;

    if (proc->isDeletedOrDeleting() && filters.isOff(ProcFilter::DeletedOrDeleting))
        return false;

    if (proc->isInit() && filters.isOff(ProcFilter::Initializing))
        return false;

    return !filters.isOff(ProcFilter::SkipAccessCheck) || isAccessingProcSafe(proc, nullptr);
}

BaseProc* BaseProcMgr::getNextProc(sead::CriticalSection* cs, BaseProc* current_proc,
                                   BaseProcMgr::ProcFilters filters) {
    if (&mProcMapCS != cs)
        return nullptr;

    BaseProcMapNode* node = nullptr;
    if (current_proc)
        node = current_proc->mMapNode.next();
    else
        node = mLastProcMapNode = mProcMap.startIterating();

    if (!node && mLastProcMapNode)
        node = mLastProcMapNode = mProcMap.nextNode(mLastProcMapNode);

    auto* proc = node ? node->proc() : nullptr;
    while (proc) {
        if (checkFilters(proc, filters))
            return proc;

        node = proc->mMapNode.next();
        if (!node && mLastProcMapNode)
            node = mLastProcMapNode = mProcMap.nextNode(mLastProcMapNode);

        if (!node)
            return nullptr;

        proc = node->proc();
    }
    return nullptr;
}

BaseProc* BaseProcMgr::getProc(const sead::SafeString& name, BaseProcMgr::ProcFilters filters) {
    const auto lock = sead::makeScopedLock(mProcMapCS);

    if (auto* node = mProcMap.find(name)) {
        auto* proc = node->proc();
        if (checkFilters(proc, filters))
            return proc;
    }

    return nullptr;
}

BaseProc* BaseProcMgr::getProc(const u32& id, BaseProcMgr::ProcFilters filters) {
    auto* cs = lockProcMap();
    auto guard = sead::makeScopeGuard([this] { unlockProcMap(); });

    BaseProc* proc = nullptr;
    do {
        proc = getNextProc(cs, proc, filters);
        if (proc && proc->getId() == id) {
            if (!checkFilters(proc, filters))
                proc = nullptr;
            break;
        }
    } while (proc);
    return proc;
}

// NON_MATCHING: stack
void BaseProcMgr::forEachProc(sead::IDelegate1<BaseProc*>& callback, ProcFilters filters) {
    const auto lock = sead::makeScopedLock(mProcMapCS);

    ProcForEachContextData data;
    ProcForEachContext context;
    context.data = &data;
    data.filters = filters;
    data.callback = &callback;

    mProcMap.forEach(sead::Delegate1<ProcForEachContext, util::StrTreeMapNode*>(
        &context, &ProcForEachContext::forEach));
}

void BaseProcMgr::forEachProc(const sead::SafeString& proc_name,
                              sead::IDelegate1<BaseProc*>& callback,
                              BaseProcMgr::ProcFilters filters) {
    const auto lock = sead::makeScopedLock(mProcMapCS);

    BaseProc* proc = nullptr;
    if (auto* node = mProcMap.find(proc_name))
        proc = node->proc();

    while (proc) {
        if (checkFilters(proc, filters))
            callback.invoke(proc);

        auto* next = proc->mMapNode.next();
        proc = next ? next->proc() : nullptr;
    }
}

bool BaseProcMgr::areInitializerThreadsIdle() const {
    return !mProcInitializer->isAnyThreadActive();
}

void BaseProcMgr::waitForInitializerQueueToEmpty() {
    mProcInitializer->waitForTaskQueuesToEmpty();
}

void BaseProcMgr::cancelInitializerTasks() {
    mProcInitializer->cancelTasks();
}

void BaseProcMgr::blockInitializerTasks() {
    mProcInitializer->blockPendingTasks();
}

void BaseProcMgr::restartInitializerThreads() {
    blockInitializerTasks();
    mProcInitializer->restartThreads();
}

void BaseProcMgr::pauseInitializerThreads() {
    mProcInitializer->pauseThreads();
}

void BaseProcMgr::resumeInitializerThreads() {
    mProcInitializer->resumeThreads();
}

void BaseProcMgr::unblockInitDeleteTasks() {
    mProcDeleter->unblockTasks();
    mProcInitializer->unblockPendingTasks();
}

void BaseProcMgr::pauseInitializerMainThread() {
    mProcInitializer->pauseMainThread();
}

void BaseProcMgr::resumeInitializerMainThread() {
    mProcInitializer->resumeMainThread();
}

bool BaseProcMgr::isAnyInitializerThreadActive() const {
    return mProcInitializer->isAnyThreadActive();
}

int BaseProcMgr::getInitializerQueueSize() const {
    return mProcInitializer->getQueueSize();
}

int BaseProcMgr::getInitializerQueueSizeEx(int x) const {
    return mProcInitializer->getQueueSize(x);
}

void BaseProcMgr::removeInitializerTasksIf(sead::IDelegate1R<util::Task*, bool>& predicate) {
    mProcInitializer->removeTasksIf(predicate);
}

void BaseProcMgr::setActorGenerationEnabled(bool enabled) {
    mProcInitializer->setActorGenerationEnabled(enabled);
}

void BaseProcMgr::incrementUnk3() {
    if (mUnk3 != 0xFF)
        ++mUnk3;
}

void BaseProcMgr::decrementUnk3() {
    if (mUnk3 != 0)
        --mUnk3;
}

// NON_MATCHING: reorderings
void BaseProcMgr::queueExtraJobPush(BaseProcJobLink* job_link) {
    getExtraJobs().pushBack(job_link);
}

// NON_MATCHING: ???
void BaseProcMgr::moveExtraJobsToOtherBuffer(JobType type) {
    const auto old_idx = mCurrentExtraJobArrayIdx;
    swapExtraJobArray();
    auto& array = mExtraJobLinkArrays.ref()[old_idx];
    for (auto& link : array) {
        link.getProc()->queueExtraJobPush_(type, mCurrentExtraJobArrayIdx);
    }
}

bool BaseProcMgr::hasExtraJobLink(BaseProcJobLink* job_link, s32 idx) {
    for (auto& ptr : mExtraJobLinkArrays.ref()[idx]) {
        if (&ptr == job_link)
            return true;
    }
    return false;
}

void BaseProcMgr::clearExtraJobArrays() {
    mExtraJobLinkArrays.ref()[0].clear();
    mExtraJobLinkArrays.ref()[1].clear();
}

}  // namespace ksys::act
