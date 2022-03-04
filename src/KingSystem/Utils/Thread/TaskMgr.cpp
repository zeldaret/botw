#include "KingSystem/Utils/Thread/TaskMgr.h"
#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::util {

TaskMgr::TaskMgr(sead::Heap* heap)
    : mTasksCS(heap), mCS2(heap), mNewFreeTaskEvent(heap, true), mEvent2(heap, true) {
    mFreeTaskLists[0].initOffset(ManagedTask::getListNodeOffset());
    mFreeTaskLists[1].initOffset(ManagedTask::getListNodeOffset());
    mNewFreeTaskEvent.resetSignal();
}

TaskMgr::~TaskMgr() {
    finalize();
}

void TaskMgr::finalize() {
    if (mFlags.isOn(Flag::HeapIsFreeable)) {
        if (mTask)
            delete mTask;
        mTask = nullptr;

        for (auto*& task : mTasks) {
            if (task)
                delete task;
            task = nullptr;
        }

        mTasks.freeBuffer();

    } else {
        if (mTask) {
            mTask->~ManagedTask();
            mTask = nullptr;
        }

        for (auto* task : mTasks)
            task->~ManagedTask();
    }
}

void TaskMgr::submitRequest(TaskMgrRequest& request) {
    bool request_had_no_task = false;
    if (!request.task) {
        request_had_no_task = true;
        fetchIdleTaskForRequest_(request, true);
    }

    if (!request.task)
        return;

    auto* task = request.task;
    if (request.handle) {
        auto* queue = request.request->mQueue;
        if (!queue) {
            auto* thread = request.request->mThread;
            queue = thread ? thread->getTaskQueue() : nullptr;
        }
        task->attachHandle(request.handle, queue);
    } else {
        task->attachHandle(nullptr, nullptr);
    }

    const bool ok = task->submitRequest(*request.request);
    if (!ok) {
        if (auto* managed_task = sead::DynamicCast<ManagedTask>(request.task)) {
            managed_task->attachHandle(nullptr, nullptr);
            if (!request_had_no_task)
                return;
            freeTask(managed_task);
        } else if (!request_had_no_task) {
            return;
        }
    }

    if (request_had_no_task || !ok)
        request.task = nullptr;
}

// NON_MATCHING: reorderings
bool TaskMgr::fetchIdleTaskForRequest_(TaskMgrRequest& request, bool retry_until_success) {
    if (!hasTasks())
        return false;

    ManagedTask* task = [this, retry_until_success] {
        const auto lock1 = sead::makeScopedLock(mTasksCS);
        if (auto* task = fetchIdleTask_(retry_until_success))
            return task;

        swapLists_();
        if (!retry_until_success)
            return fetchIdleTask_(retry_until_success);

        while (true) {
            if (auto* task_1 = fetchIdleTask_(retry_until_success))
                return task_1;
            mNewFreeTaskEvent.wait();
            swapLists_();
        }
    }();

    if (!task)
        return false;

    request.task = task;
    return true;
}

void TaskMgr::freeTask(ManagedTask* task) {
    auto lock = sead::makeScopedLock(mCS2);
    mFreeTaskLists[getListIndex2_()].pushBack(task);
    mNewFreeTaskEvent.setSignal();
}

bool TaskMgr::trySubmitRequest(TaskMgrRequest& request) {
    bool request_had_no_task = false;
    if (!request.task) {
        request_had_no_task = true;
        if (!tryFetchTaskForRequest_(request, false))
            return false;
    }

    if (!request.task)
        return false;

    auto* task = request.task;
    if (request.handle) {
        auto* queue = request.request->mQueue;
        if (!queue) {
            auto* thread = request.request->mThread;
            queue = thread ? thread->getTaskQueue() : nullptr;
        }
        task->attachHandle(request.handle, queue);
    } else {
        task->attachHandle(nullptr, nullptr);
    }

    const bool ok = task->submitRequest(*request.request);
    if (!ok) {
        if (auto* managed_task = sead::DynamicCast<ManagedTask>(request.task)) {
            managed_task->attachHandle(nullptr, nullptr);
            if (!request_had_no_task)
                return ok;
            freeTask(managed_task);
        } else if (!request_had_no_task) {
            return ok;
        }
    }

    if (request_had_no_task || !ok)
        request.task = nullptr;
    return ok;
}

// NON_MATCHING: the factory invoke function pointer is loaded earlier in the original code
void TaskMgr::init(s32 num_tasks, sead::Heap* heap, ManagedTaskFactory& factory) {
    if (!heap->isFreeable())
        mFlags.reset(Flag::HeapIsFreeable);
    else
        mFlags.set(Flag::HeapIsFreeable);

    const sead::ScopedCurrentHeapSetter heap_setter{heap};

    mTasks.allocBufferAssert(num_tasks, heap);

    if (mTasks.size() != 0) {
        auto& list = mFreeTaskLists[mListIndex];
        for (auto*& task : mTasks) {
            factory(&task);
            task->setMgr(this);
            list.pushBack(task);
        }
    }

    factory(&mTask);
}

bool TaskMgr::hasTasks() const {
    return mTasks.size() > 0;
}

ManagedTask* TaskMgr::fetchIdleTask_(bool retry_until_success) {
    auto lock = sead::makeScopedLock(mTasksCS);

    if (mFreeTaskLists[mListIndex].isEmpty())
        return nullptr;

    ManagedTask* result = nullptr;
    while (true) {
        for (auto& task : mFreeTaskLists[mListIndex]) {
            if (task.isIdle()) {
                result = std::addressof(task);
                break;
            }
        }

        if (result) {
            auto lock1 = sead::makeScopedLock(mTasksCS);
            mFreeTaskLists[mListIndex].erase(result);
            return result;
        }

        if (!retry_until_success)
            return nullptr;
        mEvent2.wait(sead::TickSpan::makeFromMilliSeconds(1));
    }
}

}  // namespace ksys::util
