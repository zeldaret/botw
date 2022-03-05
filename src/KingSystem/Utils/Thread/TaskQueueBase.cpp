#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include <algorithm>
#include <memory>
#include <thread/seadThread.h>
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::util {

static const auto cSleepSpan = sead::TickSpan::makeFromMicroSeconds(10);

TaskQueueBase::TaskQueueBase(sead::Heap* heap) : mQueueEmptyEvent(heap) {
    mActiveTasks.initOffset(Task::getListNodeOffset());
}

TaskQueueBase::~TaskQueueBase() {
    clear();

    for (auto& lane : mLanes) {
        delete lane.lane_empty_event;
        lane.lane_empty_event = nullptr;
    }

    mLanes.freeBuffer();
    mThreads.freeBuffer();
}

void TaskQueueBase::clear() {
    lock();

    // Clear all tasks.
    for (auto& task : mActiveTasks.robustRange()) {
        mActiveTasks.erase(&task);
        task.onRemove();
    }
    mActiveTasks.clear();

    for (auto& lane : mLanes)
        lane.head_task = nullptr;

    const bool is_any_thread_busy = isAnyThreadBusy();

    signalEmptyEventsIfNeeded();
    {
        ConditionalScopedLock lock{this};
        ScopedLock lock1{this};
        for (auto& thread : mThreads) {
            thread.cancelCurrentTask();
        }
    }

    unlock();

    if (is_any_thread_busy)
        mQueueEmptyEvent.wait();
}

bool TaskQueueBase::init(const InitArg& arg) {
    if (arg.max_num_threads == 0)
        return false;

    if (!mThreads.tryAllocBuffer(arg.max_num_threads, arg.heap))
        return false;

    mFlags.change(Flag::Lock, arg.enable_locks);

    if (arg.num_lanes <= 0 || arg.num_lanes > 0x100)
        return false;

    mLanes.allocBufferAssert(arg.num_lanes, arg.heap);
    for (auto& lane : mLanes) {
        lane.lane_empty_event = new (arg.heap) Event(arg.heap, true);
        lane.lane_empty_event->setSignal();
    }

    mQueueEmptyEvent.initialize(true);
    mQueueEmptyEvent.setSignal();
    mTaskSelectionDelegate = arg.task_selection_delegate;

    return true;
}

bool TaskQueueBase::addThread(TaskThread* thread) {
    if (mFlags.isOn(Flag::PreventThreadPoolChanges))
        return false;

    lockIfNeeded();

    if (mThreads.isFull()) {
        unlockIfNeeded();
        return false;
    }

    mThreads.pushBack(thread);
    unlockIfNeeded();
    return true;
}

void TaskQueueBase::removeThread(TaskThread* thread) {
    if (mFlags.isOn(Flag::PreventThreadPoolChanges))
        return;

    ConditionalScopedLock lock{this};
    mThreads.erase(mThreads.search(thread));
}

s32 TaskQueueBase::getNumActiveTasks() const {
    return mActiveTasks.size();
}

s32 TaskQueueBase::countTasksInLane(u16 id) const {
    lock();

    if (!mLanes[id].head_task) {
        unlock();
        return 0;
    }

    s32 count = 0;
    for (auto i = mActiveTasks.begin(mLanes[id].head_task), end = mActiveTasks.end(); i != end;
         ++i) {
        if (i->getLaneId() != id)
            break;
        ++count;
    }
    unlock();
    return count;
}

bool TaskQueueBase::areNoThreadsBusy() const {
    ScopedLock lock{this};

    if (!mActiveTasks.isEmpty())
        return false;
    return !isAnyThreadBusy();
}

bool TaskQueueBase::isAnyThreadBusy() const {
    ConditionalScopedLock lock{this};
    return std::any_of(mThreads.begin(), mThreads.end(),
                       [](const TaskThread& thread) { return thread.isBusyProcessingTask(); });
}

bool TaskQueueBase::areAllThreadsPaused() const {
    ConditionalScopedLock lock{this};
    return std::all_of(mThreads.begin(), mThreads.end(),
                       [](const TaskThread& thread) { return thread.isPaused(); });
}

void TaskQueueBase::waitForQueueToEmpty() {
    if (areAllThreadsPaused())
        return;

    for (const auto& lane : mLanes) {
        if (lane.blocked && lane.head_task)
            return;
    }

    mQueueEmptyEvent.wait();
}

void TaskQueueBase::waitForLaneToEmpty(u8 id) {
    if (areAllThreadsPaused())
        return;

    const auto& lane = mLanes[id];
    if (!lane.blocked || !lane.head_task)
        lane.lane_empty_event->wait();
}

void TaskQueueBase::cancelTasks(u8 id) {
    lock();

    if (mLanes[id].head_task) {
        for (auto it = mActiveTasks.robustBegin(mLanes[id].head_task),
                  end = mActiveTasks.robustEnd();
             it != end; ++it) {
            if (it->getLaneId() != id)
                break;
            mActiveTasks.erase(std::addressof(*it));
            it->onRemove();
        }
    }
    mLanes[id].head_task = nullptr;

    const auto cancel_current_tasks_if_needed = [&] {
        ConditionalScopedLock lock{this};
        ScopedLock lock1{this};
        for (auto it = mThreads.begin(), end = mThreads.end(); it != end; ++it) {
            if (it->mTask && it->mTask->getLaneId() == id)
                it->cancelCurrentTask();
        }
    };

    if (isProcessingTask(id)) {
        mLanes[id].lane_empty_event->resetSignal();
        signalEmptyEventsIfNeeded();
        cancel_current_tasks_if_needed();
        unlock();
        mLanes[id].lane_empty_event->wait();
    } else {
        signalEmptyEventsIfNeeded();
        cancel_current_tasks_if_needed();
        unlock();
    }
}

bool TaskQueueBase::isProcessingTask(u8 id) const {
    ConditionalScopedLock lock{this};
    ScopedLock lock1{this};
    return std::any_of(mThreads.begin(), mThreads.end(), [id](const TaskThread& thread) {
        return thread.mTask && thread.mTask->getLaneId() == id;
    });
}

void TaskQueueBase::signalEmptyEventsIfNeeded() {
    ScopedLock lock{this};

    const bool is_any_thread_busy = isAnyThreadBusy();
    const bool has_no_tasks = mActiveTasks.isEmpty();
    if (!is_any_thread_busy && has_no_tasks)
        mQueueEmptyEvent.setSignal();

    for (auto it = mLanes.begin(), end = mLanes.end(); it != end; ++it) {
        if (!isProcessingTask(it.getIndex()) && it->head_task == nullptr)
            it->lane_empty_event->setSignal();
    }
}

void TaskQueueBase::blockTasks(u8 id) {
    if (mLanes[id].blocked != 1)
        mLanes[id].blocked = true;
}

// NON_MATCHING: the while (!areAllThreadsPaused()) loop generates weird code in the original
void TaskQueueBase::blockTasksAndReloadThreads(u8 id) {
    blockTasks(id);

    {
        ConditionalScopedLock lock{this};
        for (auto& thread : mThreads)
            thread.pause();
    }

    const auto sleep_duration = sead::TickSpan::makeFromMilliSeconds(1);

    while (!areAllThreadsPaused())
        sead::Thread::sleep(sleep_duration);

    sead::Thread::sleep(sleep_duration);

    {
        ConditionalScopedLock lock{this};
        for (auto& thread : mThreads)
            thread.resume();
    }
}

void TaskQueueBase::unblockTasks(u8 id) {
    if (mLanes[id].blocked) {
        mLanes[id].blocked = false;
        notifyThreadsForNewTasks();
    }
}

void TaskQueueBase::lock(TaskQueueLock* lock) {
    lock->lock(this);
}

TaskThread* TaskQueueBase::getCurrentThread() const {
    const sead::Thread* current_thread = sead::ThreadMgr::instance()->getCurrentThread();
    lockIfNeeded();
    for (auto it = mThreads.begin(), end = mThreads.end(); it != end; ++it) {
        if (current_thread == std::addressof(*it)) {
            unlockIfNeeded();
            return std::addressof(*it);
        }
    }
    unlockIfNeeded();
    return nullptr;
}

sead::OffsetList<Task>::iterator TaskQueueBase::activeTasksBegin(TaskQueueLock* lock) {
    lock->lock(this);
    return mActiveTasks.begin();
}

sead::OffsetList<Task>::robustIterator TaskQueueBase::activeTasksRobustBegin(TaskQueueLock* lock) {
    lock->lock(this);
    return mActiveTasks.robustBegin();
}

sead::OffsetList<Task>::iterator TaskQueueBase::activeTasksEnd() const {
    return mActiveTasks.end();
}

sead::OffsetList<Task>::robustIterator TaskQueueBase::activeTasksRobustEnd() const {
    return mActiveTasks.robustEnd();
}

void TaskQueueBase::notifyThreadsForNewTasks() {
    s32 retry_count = 0;
    const sead::Thread* current_thread = sead::ThreadMgr::instance()->getCurrentThread();
    sead::BitFlag32 mask = 0;

    while (true) {
        lockIfNeeded();
        bool done = true;
        s32 i = 0;
        auto* data = mThreads.data();
        for (auto& thread : mThreads) {
            static_cast<void>(thread);
            if (current_thread != data[i] && !data[i]->isLookingForTask() &&
                !data[i]->receivedQueueUpdatedMsg() && !data[i]->receivedPauseMsg() &&
                !data[i]->receivedResumeMsg() && !data[i]->receivedQuitMsg() && !mask.isOnBit(i)) {
                const bool send_ok = data[i]->sendMessage(
                    TaskThread::cMessage_QueueUpdated, sead::MessageQueue::BlockType::NonBlocking);
                if (send_ok)
                    mask.setBit(i);
                done &= send_ok;
            }
            ++i;
        }
        unlockIfNeeded();

        if (done)
            break;

        ++retry_count;
        sead::Thread::sleep(cSleepSpan);
    }

    if (retry_count >= 2)
        PrintDebug(sead::FormatFixedSafeString<128>("↓↓↓\nリトライ回数 %d 回\n↑↑↑\n", retry_count));
}

bool TaskQueueBase::push(const PushArg& arg) {
    lock();

    if (!arg.task || mActiveTasks.isNodeLinked(arg.task)) {
        unlock();
        return false;
    }

    const auto num_tasks = mActiveTasks.size();
    const u8 id = arg.lane_id <= u8(mLanes.size() - 1) ? arg.lane_id : u8(mLanes.size() - 1);
    arg.task->setLaneId(id);

    bool added = false;
    for (u8 i = id - 1; i != 0xff; --i) {
        if (!mLanes[i].head_task)
            continue;

        mActiveTasks.insertBefore(mLanes[i].head_task, arg.task);
        added = true;
        break;
    }

    if (!added) {
        mActiveTasks.pushBack(arg.task);
        mLanes[id].lane_empty_event->resetSignal();
    }

    if (!mLanes[id].head_task)
        mLanes[id].head_task = arg.task;

    arg.task->setStatusPushed();

    if (num_tasks == 0)
        mQueueEmptyEvent.resetSignal();

    unlock();
    notifyThreadsForNewTasks();
    return true;
}

void TaskQueueBase::removeTask(Task* task, bool b) {
    if (!task)
        return;

    lock();

    if (!task->isInactive()) {
        if (task->getStatus() == Task::Status::Pushed) {
            const u8 id = task->getLaneId();
            if (mLanes[id].head_task == task) {
                auto* new_task = mActiveTasks.next(task);
                if (new_task && task->getLaneId() == new_task->getLaneId())
                    mLanes[id].head_task = new_task;
                else
                    mLanes[id].head_task = nullptr;
            }

            mActiveTasks.erase(task);
            task->onRemove();
            signalEmptyEventsIfNeeded();
        } else if (b) {
            task->cancel();
            unlock();
            task->wait();
            return;
        }
    }

    unlock();
}

// NON_MATCHING: regalloc inside the task lambda + reorderings for the loop counters.
void TaskQueueBase::fetchTask(Task** out_task) {
    lock();

    const auto check_state = [&] {
        if (!mActiveTasks.isEmpty() || isAnyThreadBusy())
            return true;
        mQueueEmptyEvent.setSignal();
        *out_task = nullptr;
        unlock();
        return false;
    };

    if (!check_state())
        return;

    auto* task = [&]() -> Task* {
        for (auto it = mLanes.rbegin(), end = mLanes.rend(); it != end; ++it) {
            if (it->blocked)
                continue;
            if (it->head_task == nullptr)
                continue;
            if (!mTaskSelectionDelegate)
                return it->head_task;

            const auto it_begin = mActiveTasks.begin(it->head_task);
            Task* end_ptr = nullptr;
            for (auto it2 = it; it2 != mLanes.rbegin(0);) {
                // XXX: This looks really weird.
                auto* t = std::addressof(*it2)[-1].head_task;
                ++it2;
                if (t) {
                    if (it2->head_task)
                        end_ptr = it2->head_task;
                    break;
                }
            }
            const auto it_end = end_ptr ? mActiveTasks.begin(end_ptr) : mActiveTasks.end();

            TaskSelectionContext context;
            context.lane_id = it->head_task->getLaneId();
            context.it_begin = &it_begin;
            context.it_end = &it_end;
            Task* task = mTaskSelectionDelegate->invoke(context);
            if (task)
                return task;
        }

        return nullptr;
    }();

    if (!check_state())
        return;

    if (task) {
        for (u8 id = mLanes.size() - 1; id != 0xff; --id) {
            if (mLanes[id].head_task == task) {
                auto* new_task = mActiveTasks.next(task);
                if (new_task && task->getLaneId() == new_task->getLaneId())
                    mLanes[id].head_task = new_task;
                else
                    mLanes[id].head_task = nullptr;
                break;
            }
        }
        mActiveTasks.erase(task);
        task->setStatusFetched();
        *out_task = task;
    } else {
        *out_task = nullptr;
    }

    unlock();
}

}  // namespace ksys::util
