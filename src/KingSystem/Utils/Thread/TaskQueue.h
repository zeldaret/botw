#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Thread/TaskQueueBase.h"

namespace ksys::util {

class TaskQueue : public TaskQueueBase {
    SEAD_RTTI_OVERRIDE(TaskQueue, TaskQueueBase)
public:
    explicit TaskQueue(sead::Heap* heap);

private:
    void lock() const override { mCS.lock(); }
    void unlock() const override { mCS.unlock(); }

    mutable sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(TaskQueue, 0xd0);

}  // namespace ksys::util
