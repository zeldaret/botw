#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class TaskQueueBase;

class TaskQueueLock {
    SEAD_RTTI_BASE(TaskQueueLock)
public:
    TaskQueueLock();
    explicit TaskQueueLock(TaskThread* thread) : TaskQueueLock() { thread->lock(this); }
    TaskQueueLock(const TaskQueueLock&) = delete;
    virtual ~TaskQueueLock();
    TaskQueueLock& operator=(const TaskQueueLock&) = delete;

    void lock(TaskQueueBase* queue);
    void unlock();

private:
    TaskQueueBase* mQueue = nullptr;
};
KSYS_CHECK_SIZE_NX150(TaskQueueLock, 0x10);

}  // namespace ksys::util
