#include "KingSystem/Utils/Thread/TaskThread.h"
#include <thread/seadThread.h>
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskQueue.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"

namespace ksys::util {

TaskThread::TaskThread(const sead::SafeString& name, sead::Heap* heap, s32 priority,
                       sead::MessageQueue::BlockType block_type,
                       sead::MessageQueue::Element quit_msg, s32 stack_size, s32 message_queue_size)
    : Thread(name, heap, priority, block_type, quit_msg, stack_size, message_queue_size),
      mPauseResumeEvent(heap), mTaskProcessedEvent(heap) {}

TaskThread::~TaskThread() {
    if (!mTaskQueue)
        return;

    mTaskQueue->removeThread(this);
    if (mFlags.isOff(Flag::DoesNotOwnTaskQueue)) {
        if (mTaskQueue)
            delete mTaskQueue;
        mTaskQueue = nullptr;
    }
}

bool TaskThread::init(const TaskThread::InitArg& arg) {
    if (arg.queue) {
        mTaskQueue = arg.queue;
        mFlags.set(Flag::DoesNotOwnTaskQueue);
    } else {
        mTaskQueue = new (arg.heap) TaskQueue(arg.heap);
        TaskQueueBase::InitArg queue_arg;
        queue_arg.enable_locks = false;
        queue_arg.task_selection_delegate = nullptr;
        queue_arg.heap = arg.heap;
        queue_arg.num_lanes = arg.num_lanes;
        queue_arg.max_num_threads = 1;
        mTaskQueue->init(queue_arg);
    }

    mTaskQueue->addThread(this);

    mPauseResumeEvent.initialize(true);
    mPauseResumeEvent.setSignal();

    mTaskProcessedEvent.initialize(true);
    mTaskProcessedEvent.setSignal();

    mBatchSize = arg.batch_size;

    return true;
}

s32 TaskThread::getNumActiveTasks() const {
    return mTaskQueue->getNumActiveTasks();
}

void TaskThread::waitForQueueToEmpty() {
    mTaskQueue->waitForQueueToEmpty();
}

void TaskThread::cancelTasks(u8 id) {
    mTaskQueue->cancelTasks(id);
}

void TaskThread::clearQueue() {
    mTaskQueue->clear();
}

void TaskThread::lock(TaskQueueLock* lock) {
    mTaskQueue->lock(lock);
}

bool TaskThread::isActiveAndReceivedQueueUpdateMsg() const {
    if (mFlags.isOn(Flag::Paused))
        return false;
    if (mFlags.isOn(Flag::IsActive))
        return true;
    return receivedQueueUpdatedMsg();
}

bool TaskThread::isPaused() const {
    return mFlags.isOn(Flag::Paused);
}

bool TaskThread::receivedQueueUpdatedMsg() const {
    return mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) == cMessage_QueueUpdated;
}

void TaskThread::pause() {
    if (sead::ThreadMgr::instance()->getCurrentThread() == this)
        return;

    if (!mPauseResumeMsg.compareExchange(cMessage_Resume, cMessage_Pause))
        return;

    mPauseResumeEvent.wait();
    mPauseResumeEvent.resetSignal();
    mMessageQueue.jam(cMessage_Pause, sead::MessageQueue::BlockType::Blocking);
}

void TaskThread::pauseAndWaitForAck() {
    if (sead::ThreadMgr::instance()->getCurrentThread() == this)
        return;

    pause();
    mPauseResumeEvent.wait();
}

void TaskThread::resume() {
    if (sead::ThreadMgr::instance()->getCurrentThread() == this)
        return;

    if (!mPauseResumeMsg.compareExchange(cMessage_Pause, cMessage_Resume))
        return;

    mPauseResumeEvent.wait();
    mPauseResumeEvent.resetSignal();
    mMessageQueue.jam(cMessage_Resume, sead::MessageQueue::BlockType::Blocking);
}

void TaskThread::resumeAndWaitForAck() {
    if (sead::ThreadMgr::instance()->getCurrentThread() == this)
        return;

    resume();
    mPauseResumeEvent.wait();
}

bool TaskThread::isBusyProcessingTask() const {
    return mFlags.isOn(Flag::IsBusyProcessingTask);
}

bool TaskThread::isLookingForTask() const {
    return mFlags.isOn(Flag::IsLookingForTask);
}

// NON_MATCHING: branching for `if (mTaskQueue->getNumActiveTasks() == 0)`:
// Clang got rid of the branch and merged the two mFlags writes
void TaskThread::calc_(sead::MessageQueue::Element msg) {
    if (mFlags.isOn(Flag::Paused)) {
        if (msg != cMessage_Resume)
            return;
        mFlags.reset(Flag::Paused);
        mPauseResumeEvent.setSignal();
    }

    if (msg == cMessage_Pause) {
        mPauseResumeEvent.setSignal();
        mFlags.set(Flag::Paused);
        return;
    }

    if (mBatchSize >= 1)
        mNumRemainingTasksInBatch = mBatchSize;

    while (true) {
        {
            TaskQueueLock lock{this};
            const auto latest_msg = mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking);

            if (latest_msg == mQuitMsg) {
                mFlags.reset(Flag::IsActive);
                mFlags.reset(Flag::IsLookingForTask);
                break;
            }

            if (latest_msg == cMessage_Pause) {
                mFlags.reset(Flag::IsActive);
                mFlags.reset(Flag::IsLookingForTask);
                break;
            }

            mFlags.set(Flag::IsActive);

            mFlags.set(Flag::IsLookingForTask);
            mTaskQueue->fetchTask(&mTask);
            mFlags.reset(Flag::IsLookingForTask);

            if (mTask == nullptr) {
                mFlags.reset(Flag::IsActive);
                mFlags.reset(Flag::IsLookingForTask);
                mTaskQueue->signalEmptyEventsIfNeeded();
                break;
            }

            mFlags.reset(Flag::IsLookingForTask);

            mFlags.set(Flag::IsBusyProcessingTask);
            mTask->setThread(this);
        }

        mTask->run();

        Task* task;
        {
            TaskQueueLock lock{this};
            mTask->onRunFinished();
            task = mTask;
            mTask = nullptr;
        }

        if (task) {
            TaskPostRunResult result;
            task->invokePostRunCallback(&result);

            TaskQueueLock lock{this};
            if (!result.getResult())
                task->finish();

            mFlags.reset(Flag::IsBusyProcessingTask);
            mTaskProcessedEvent.setSignal();
            mTaskQueue->signalEmptyEventsIfNeeded();

            if (mTaskQueue->getNumActiveTasks() == 0) {
                mFlags.reset(Flag::IsActive);
#ifdef MATCHING_HACK_NX_CLANG
                // To make it easier to see what this function is functionally equivalent.
                // Does not fix the matching issue, but turns it into a 2-line reordering.
                asm("" ::: "memory");
#endif
                break;
            }

            mFlags.set(Flag::IsLookingForTask);
        }

        if (mBatchSize <= 0)
            continue;

        --mNumRemainingTasksInBatch;
        if (mNumRemainingTasksInBatch == 0) {
            sead::Thread::yield();
            mNumRemainingTasksInBatch = mBatchSize;
        }
    }

    mFlags.reset(Flag::IsActive);
    mFlags.reset(Flag::IsLookingForTask);
}

bool TaskThread::receivedPauseMsg() const {
    return mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) == cMessage_Pause;
}

bool TaskThread::receivedResumeMsg() const {
    return mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) == cMessage_Resume;
}

bool TaskThread::receivedQuitMsg() const {
    const auto msg = static_cast<s32>(mQuitMsg);
    return mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) == msg;
}

void TaskThread::cancelCurrentTask() {
    TaskQueueLock lock{this};
    if (mTask)
        mTask->cancel();
}

}  // namespace ksys::util
