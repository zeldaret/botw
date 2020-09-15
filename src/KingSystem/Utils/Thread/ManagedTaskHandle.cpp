#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"

namespace ksys::util {

ManagedTaskHandle::ManagedTaskHandle() = default;

ManagedTaskHandle::~ManagedTaskHandle() {
    removeTaskFromQueue();
    finalize();
}

void ManagedTaskHandle::removeTaskFromQueue() {
    if (!mQueue)
        return;

    incrementRef_();

    if (mTask)
        mTask->removeFromQueue();

    decrementRef_();
}

void ManagedTaskHandle::finalize() {
    if (mQueue)
        decrementRef_();
}

bool ManagedTaskHandle::hasTask() const {
    return mTask != nullptr;
}

bool ManagedTaskHandle::wait() {
    if (!mQueue)
        return true;

    incrementRef_();

    if (mTask)
        mTask->wait();

    decrementRef_();
    return true;
}

bool ManagedTaskHandle::wait(const sead::TickSpan& wait_duration) {
    if (!mQueue)
        return true;

    incrementRef_();

    if (!mTask) {
        decrementRef_();
        return true;
    }

    const bool ret = mTask->wait(wait_duration);
    decrementRef_();
    return ret;
}

bool ManagedTaskHandle::isTaskAttached() const {
    return mTask && mStatus == Status::TaskAttached;
}

bool ManagedTaskHandle::didTaskCompleteSuccessfully() const {
    return mStatus == Status::TaskFinished && mSuccess;
}

bool ManagedTaskHandle::attachTask(const SetTaskArg& arg) {
    mTask = arg.task;
    mQueue = arg.queue;
    incrementRef_();
    return true;
}

void ManagedTaskHandle::setStatus(Status status) {
    mStatus = status;
}

void ManagedTaskHandle::setIsSuccess(bool success) {
    mSuccess = success;
}

inline void ManagedTaskHandle::incrementRef_() {
    TaskQueueLock lock;
    mQueue->lock(&lock);
    ++mRefCount;
}

inline void ManagedTaskHandle::decrementRef_() {
    TaskQueueLock lock;
    mQueue->lock(&lock);

    if (mRefCount > 0)
        --mRefCount;

    if (mRefCount <= 0 && mTask) {
        mTask->detachHandle();
        mTask = nullptr;
    }
}

}  // namespace ksys::util
