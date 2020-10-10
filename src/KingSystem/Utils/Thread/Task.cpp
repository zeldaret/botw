#include "KingSystem/Utils/Thread/Task.h"
#include <thread/seadThread.h>
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::util {

TaskDelegateSetter::TaskDelegateSetter() = default;

TaskDelegateSetter::~TaskDelegateSetter() = default;

void TaskDelegateSetter::setDelegate(TaskDelegate* delegate) {
    mDelegate = delegate;
}

Task::Task(sead::Heap* heap) : mEvent(heap, true) {
    mEvent.setSignal();
}

Task::Task(sead::Heap* heap, sead::IDisposer::HeapNullOption heap_null_option)
    : mEvent(heap, heap_null_option, true) {
    mEvent.setSignal();
}

Task::~Task() {
    finalize_();
}

void Task::deleteDelegate_() {
    if (mDelegate && mFlags.isOn(Flag::DeleteDelegate) && mFlags.isOff(Flag::DoNotDeleteDelegate)) {
        ::operator delete(mDelegate);
        mDelegate = nullptr;
    }
}

// NON_MATCHING: mDelegate2 = nullptr store
void Task::finalize_() {
    if (mStatus == Status::Finalized)
        return;

    removeFromQueue();
    deleteDelegate_();
    mUserData = nullptr;
    mQueue = nullptr;
    mPostRunCallback = nullptr;
    mRemoveCallback = nullptr;
    mStatus = Status::Finalized;
}

bool Task::setDelegate(const TaskDelegateSetter& setter) {
    mDelegate = setter.getDelegate();
    mFlags.reset(Flag::DeleteDelegate);
    mFlags.reset(Flag::DoNotDeleteDelegate);
    mFlags.set(Flag::DoNotDeleteDelegate);
    return onSetDelegate_(setter);
}

// NON_MATCHING: branching
bool Task::submitRequest(TaskRequest& request) {
    // Processing this request is impossible if there is no thread *and* no queue!
    if (request.mThread == nullptr && request.mQueue == nullptr)
        return false;

    if (!canSubmitRequest())
        return false;

    if (request.mSynchronous || request.mHasHandle)
        mFlags.set(Flag::NeedsToSignalEvent);
    else
        mFlags.reset(Flag::NeedsToSignalEvent);

    mFlags.change(Flag::SynchronousRequest, request.mSynchronous);

    if (mListNode.isLinked())
        return false;

    if (mFlags.isOn(Flag::NeedsToSignalEvent))
        mEvent.resetSignal();

    mQueue = request.mQueue;
    if (!mQueue) {
        mQueue = request.mThread->getTaskQueue();
        request.mQueue = mQueue;
    }
    mUserData = request.mUserData;
    if (request.mDelegate)
        setDelegateInternal_(request.mDelegate);
    mRemoveCallback = request.mRemoveCallback;
    mPostRunCallback = request.mPostRunCallback;
    mName = request.mName;

    prepare_(&request);

    if (request.mSynchronous) {
        auto* thread = mQueue->getCurrentThread();
        if (thread) {
            processOnCurrentThreadDirectly(thread);
            return true;
        }
    }

    TaskQueueBase::PushArg arg;
    arg.lane_id = request.mLaneId;
    arg.task = this;
    const bool push_ok = mQueue->push(arg);
    bool b;
    if (push_ok) {
        if (request.mSynchronous)
            mEvent.wait();
        b = true;
    } else {
        b = false;
    }
    return push_ok || b;
}

bool Task::canSubmitRequest() const {
    const bool run_finished_on_current_thread =
        mThread && mStatus == Status::RunFinished &&
        mThread == sead::ThreadMgr::instance()->getCurrentThread();
    const bool cond2 = isInactive();
    return run_finished_on_current_thread || cond2;
}

void Task::setUserData(void* user_data) {
    mUserData = user_data;
}

bool Task::setDelegateInternal_(TaskDelegate* delegate) {
    deleteDelegate_();
    mFlags.set(Flag::DoNotDeleteDelegate);
    mDelegate = delegate;
    return delegate != nullptr;
}

void Task::processOnCurrentThreadDirectly(TaskThread* thread) {
    {
        TaskQueueLock lock{thread};
        mThread = thread;
        mStatus = Status::Pushed;
    }

    run();

    {
        TaskQueueLock lock{thread};
        onRunFinished();
    }

    TaskPostRunResult result;
    invokePostRunCallback(&result);

    {
        TaskQueueLock lock{thread};
        if (!result.getResult())
            finish();
    }
}

void Task::removeFromQueue() {
    if (mQueue)
        mQueue->removeTask(this, true);
}

void Task::removeFromQueue2() {
    // TODO: how does this differ from removeFromQueue?
    removeFromQueue();
}

void Task::run_() {
    if (mDelegate)
        mDelegateResult = mDelegate->invoke(mUserData);
}

bool Task::wait() {
    mEvent.wait();
    return true;
}

bool Task::wait(const sead::TickSpan& span) {
    return mEvent.wait(span);
}

u8 Task::getLaneId() const {
    return mLaneId;
}

bool Task::isSuccess() const {
    return (mStatus == Status::PreFinishCallback || mStatus == Status::RunFinished ||
            mStatus == Status::PostFinishCallback) &&
           mDelegateResult;
}

bool Task::isInactive() const {
    return mStatus == Status::Uninitialized || mStatus == Status::RemovedFromQueue ||
           mStatus == Status::PostFinishCallback;
}

void Task::setStatusPushed() {
    mStatus = Status::Pushed;
}

void Task::setThread(TaskThread* thread) {
    mThread = thread;
}

void Task::run() {
    run_();
    mStatus = Status::RunFinished;
}

void Task::onRunFinished() {
    onRunFinished_();
}

void Task::invokePostRunCallback(TaskPostRunResult* result) {
    mRemoveCallback = nullptr;
    TaskPostRunContext context;
    context.mCancelled = mFlags.isOn(Flag::Cancelled);
    context.mTask = this;
    context.mUserData = mUserData;
    if (auto* delegate = mPostRunCallback) {
        mPostRunCallback = nullptr;
        delegate->invoke(result, context);
    }
}

void Task::finish() {
    mStatus = Status::PreFinishCallback;
    onFinish_();
    mStatus = Status::PostFinishCallback;

    mThread = nullptr;
    signalEvent();

    onPostFinish_();
}

void* Task::getUserData() const {
    return mUserData;
}

void Task::cancel() {
    mEvent.resetSignal();
    mFlags.set(Flag::Cancelled);
    mFlags.set(Flag::NeedsToSignalEvent);
}

void Task::onRemove() {
    invokeRemoveCallback_();

    TaskQueueLock lock;
    mQueue->lock(&lock);

    preRemove_();

    mStatus = Status::RemovedFromQueue;
    mThread = nullptr;
    signalEvent();

    postRemove_();
}

void Task::invokeRemoveCallback_() {
    mPostRunCallback = nullptr;
    TaskRemoveCallbackContext context;
    context.mTask = this;
    context.mUserData = mUserData;

    if (auto* delegate = mRemoveCallback) {
        mRemoveCallback = nullptr;
        delegate->invoke(context);
    }
}

void Task::setStatusFetched() {
    mStatus = Status::Fetched;
}

void Task::setLaneId(u8 id) {
    mLaneId = id;
}

}  // namespace ksys::util
