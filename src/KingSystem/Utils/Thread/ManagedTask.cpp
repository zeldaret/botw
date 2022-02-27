#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"

namespace ksys::util {

ManagedTask::ManagedTask(sead::Heap* heap) : Task(heap) {}

ManagedTask::ManagedTask(sead::IDisposer::HeapNullOption heap_null_option)
    : Task(nullptr, heap_null_option) {}

ManagedTask::~ManagedTask() {
    if (mHandle) {
        mHandle->finalize();
        mHandle = nullptr;
    }
    finalize_();
}

void ManagedTask::prepare_(TaskRequest* request) {
    mIsIdle = false;
    prepareImpl_(request);
}

void ManagedTask::run_() {
    Task::run_();
    onRun_();
}

void ManagedTask::onRunFinished_() {}

void ManagedTask::onFinish_() {
    if (auto* handle = mHandle) {
        handle->setIsSuccess(isSuccess());
        handle->setStatus(ManagedTaskHandle::Status::TaskFinished);
    }

    if (!mHandle && mMgr)
        mMgr->freeTask(this);
}

void ManagedTask::onPostFinish_() {
    mIsIdle = true;
}

void ManagedTask::preRemove_() {
    preRemoveImpl_();

    if (mHandle)
        mHandle->setStatus(ManagedTaskHandle::Status::TaskRemoved);

    if (!mHandle && mMgr)
        mMgr->freeTask(this);
}

void ManagedTask::postRemove_() {
    mIsIdle = true;
}

void ManagedTask::onRun_() {}

void ManagedTask::prepareImpl_(TaskRequest*) {}

void ManagedTask::preRemoveImpl_() {}

bool ManagedTask::isIdle() const {
    return mIsIdle;
}

void ManagedTask::setMgr(TaskMgr* mgr) {
    mMgr = mgr;
}

void ManagedTask::attachHandle(ManagedTaskHandle* handle, TaskQueueBase* queue) {
    if (mHandle)
        return;

    if (handle) {
        handle->attachTask({this, queue});
        handle->setStatus(ManagedTaskHandle::Status::TaskAttached);
    }
    mHandle = handle;
}

// NON_MATCHING: switch
void ManagedTask::detachHandle() {
    TaskQueueLock lock;
    lock.lock(mQueue);

    if (mHandle) {
        switch (mHandle->getStatus()) {
        case ManagedTaskHandle::Status::TaskRemoved:
        case ManagedTaskHandle::Status::TaskFinished:
            mHandle = nullptr;
            if (mMgr)
                mMgr->freeTask(this);
            break;
        default:
            mHandle = nullptr;
            break;
        }
    }
}

}  // namespace ksys::util
