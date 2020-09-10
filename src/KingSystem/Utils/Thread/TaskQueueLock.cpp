#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/TaskQueueBase.h"

namespace ksys::util {

TaskQueueLock::TaskQueueLock() = default;

TaskQueueLock::~TaskQueueLock() {
    unlock();
}

void TaskQueueLock::lock(TaskQueueBase* queue) {
    if (!mQueue) {
        mQueue = queue;
        mQueue->lock();
    }
}

void TaskQueueLock::unlock() {
    if (mQueue) {
        mQueue->unlock();
        mQueue = nullptr;
    }
}

}  // namespace ksys::util
