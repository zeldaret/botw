#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <time/seadTickSpan.h>
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class Task;
class TaskQueueLock;
class TaskThread;

struct TaskSelectionContext {
    const auto& begin() const { return *it_begin; }
    const auto& end() const { return *it_end; }
    u8 lane_id;
    const sead::OffsetList<Task>::iterator* it_begin;
    const sead::OffsetList<Task>::iterator* it_end;
};

using TaskSelectionDelegate = sead::IDelegate1R<const TaskSelectionContext&, Task*>;
template <typename T>
using TaskSelectionDelegateT = sead::Delegate1R<T, const TaskSelectionContext&, Task*>;

class TaskQueueBase {
    SEAD_RTTI_BASE(TaskQueueBase)
public:
    struct InitArg {
        bool enable_locks;
        /// Number of lanes.
        u16 num_lanes;
        /// Maximum number of threads that will be processing the queue.
        u16 max_num_threads;
        sead::Heap* heap;
        TaskSelectionDelegate* task_selection_delegate;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x18);

    struct PushArg {
        u8 lane_id;
        Task* task;
    };
    KSYS_CHECK_SIZE_NX150(PushArg, 0x10);

    explicit TaskQueueBase(sead::Heap* heap);
    virtual ~TaskQueueBase();

    void clear();
    bool init(const InitArg& arg);

    bool addThread(TaskThread* thread);
    void removeThread(TaskThread* thread);

    s32 getNumActiveTasks() const;
    s32 countTasksInLane(u16 id) const;
    bool areNoThreadsBusy() const;
    bool isAnyThreadBusy() const;
    bool areAllThreadsPaused() const;

    void waitForQueueToEmpty();
    void waitForLaneToEmpty(u8 id);

    void cancelTasks(u8 id);
    bool isProcessingTask(u8 id) const;
    void signalEmptyEventsIfNeeded();

    void blockTasks(u8 id);
    void blockTasksAndReloadThreads(u8 id);
    void unblockTasks(u8 id);

    void lock(TaskQueueLock* lock);

    /// @returns the current thread if it is in the thread pool and nullptr otherwise.
    TaskThread* getCurrentThread() const;

    sead::OffsetList<Task>::iterator activeTasksBegin(TaskQueueLock* lock);
    sead::OffsetList<Task>::robustIterator activeTasksRobustBegin(TaskQueueLock* lock);
    sead::OffsetList<Task>::iterator activeTasksEnd() const;
    sead::OffsetList<Task>::robustIterator activeTasksRobustEnd() const;

    bool push(const PushArg& arg);
    void removeTask(Task* task, bool b);
    void fetchTask(Task** out_task);

protected:
    enum class Flag : u8 {
        Lock = 0x1,
        PreventThreadPoolChanges = 0x2,
    };

    struct Lane {
        /// If true, tasks in this lane are not allowed to be fetched by any thread.
        bool blocked = false;
        /// First task in the lane. Tasks are also added to a linked list (mActiveTasks).
        Task* head_task = nullptr;
        Event* lane_empty_event = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(Lane, 0x18);

    class ScopedLock {
    public:
        explicit ScopedLock(const TaskQueueBase* queue) : mQueue(queue) { mQueue->lock(); }
        ScopedLock(const ScopedLock&) = delete;
        ~ScopedLock() { mQueue->unlock(); }
        ScopedLock& operator=(const ScopedLock&) = delete;

    private:
        const TaskQueueBase* mQueue;
    };

    class ConditionalScopedLock {
    public:
        explicit ConditionalScopedLock(const TaskQueueBase* queue) : mQueue(queue) {
            mQueue->lockIfNeeded();
        }
        ConditionalScopedLock(const ConditionalScopedLock&) = delete;
        ~ConditionalScopedLock() { mQueue->unlockIfNeeded(); }
        ConditionalScopedLock& operator=(const ConditionalScopedLock&) = delete;

    private:
        const TaskQueueBase* mQueue;
    };

    friend class TaskQueueLock;

    virtual void lock() const {}
    virtual void unlock() const {}

    bool shouldLock() const { return mFlags.isOn(Flag::Lock); }

    void lockIfNeeded() const {
        if (shouldLock())
            lock();
    }

    void unlockIfNeeded() const {
        if (shouldLock())
            unlock();
    }

    void notifyThreadsForNewTasks();

    sead::TypedBitFlag<Flag> mFlags;
    sead::OffsetList<Task> mActiveTasks;
    sead::Buffer<Lane> mLanes;
    Event mQueueEmptyEvent;
    sead::PtrArray<TaskThread> mThreads;
    TaskSelectionDelegate* mTaskSelectionDelegate = nullptr;
};
KSYS_CHECK_SIZE_NX150(TaskQueueBase, 0x90);

}  // namespace ksys::util
