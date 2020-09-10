#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadThread.h>
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class Task;
class TaskQueueBase;
class TaskQueueLock;

class TaskThread : public sead::Thread {
    SEAD_RTTI_BASE(TaskThread)
public:
    enum Message {
        cMessage_QueueUpdated = 1,
        cMessage_Pause = 2,
        cMessage_Resume = 3,
    };

    struct InitArg {
        /// Number of lanes if a new queue is to be created.
        /// Only used if queue is nullptr.
        u16 num_lanes;
        /// Number of tasks to process in a row before yielding. Can be zero to disable the limit.
        u32 batch_size;
        /// Heap that will be used to allocate a new queue if necessary.
        /// Only used if queue is nullptr.
        sead::Heap* heap;
        /// Task queue. If null, a new queue will be created and owned by this thread.
        TaskQueueBase* queue;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x18);

    TaskThread(const sead::SafeString& name, sead::Heap* heap, s32 priority,
               sead::MessageQueue::BlockType block_type, sead::MessageQueue::Element quit_msg,
               s32 stack_size, s32 message_queue_size);
    ~TaskThread() override;

    bool init(const InitArg& arg);

    s32 getNumActiveTasks() const;

    void waitForQueueToEmpty();
    void cancelTasks(u8 id);
    void clearQueue();
    void lock(TaskQueueLock* lock);

    bool isActiveAndReceivedQueueUpdateMsg() const;
    bool isPaused() const;
    bool receivedQueueUpdatedMsg() const;

    void pause();
    void pauseAndWaitForAck();
    void resume();
    void resumeAndWaitForAck();

    bool isBusyProcessingTask() const;
    bool isLookingForTask() const;

    bool receivedPauseMsg() const;
    bool receivedResumeMsg() const;
    bool receivedQuitMsg() const;

    void cancelCurrentTask();

    TaskQueueBase* getTaskQueue() const { return mTaskQueue; }

protected:
    friend class TaskQueueBase;

    enum class Flag {
        _1 = 0x1,
        _2 = 0x2,
        _4 = 0x4,
        Paused = 0x8,
        /// The task queue is *not* owned by this TaskThread.
        DoesNotOwnTaskQueue = 0x10,
        /// A batch is being processed.
        IsActive = 0x20,
        /// This thread is looking for a task to process.
        IsLookingForTask = 0x40,
        /// A task is being processed.
        IsBusyProcessingTask = 0x80,
    };

    void calc_(sead::MessageQueue::Element msg) override;

    sead::TypedBitFlag<Flag, u8> mFlags = [] {
        decltype(mFlags) flags;
        flags.set(Flag::_2);
        flags.set(Flag::_4);
        return flags;
    }();
    Task* mTask = nullptr;
    s32 mBatchSize = 0;
    s32 mNumRemainingTasksInBatch = 0;
    sead::Atomic<Message> mPauseResumeMsg = cMessage_Resume;
    Event mPauseResumeEvent;
    Event mTaskProcessedEvent;
    TaskQueueBase* mTaskQueue = nullptr;
};
KSYS_CHECK_SIZE_NX150(TaskThread, 0x1a0);

}  // namespace ksys::util
