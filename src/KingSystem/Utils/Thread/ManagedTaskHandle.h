#pragma once

#include <basis/seadTypes.h>
#include <time/seadTickSpan.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class ManagedTask;
class TaskQueueBase;

class ManagedTaskHandle {
public:
    enum class Status {
        Uninitialized = 0,
        TaskAttached = 1,
        TaskFinished = 2,
        TaskRemoved = 3,
    };

    ManagedTaskHandle();
    virtual ~ManagedTaskHandle();

    void finalize();

    Status getStatus() const { return mStatus; }

    void removeTaskFromQueue();
    bool hasTask() const;

    bool wait();
    bool wait(const sead::TickSpan& wait_duration);

    bool isTaskAttached() const;
    bool didTaskCompleteSuccessfully() const;

private:
    friend class ManagedTask;

    struct SetTaskArg {
        ManagedTask* task;
        TaskQueueBase* queue;
    };

    bool attachTask(const SetTaskArg& arg);
    void setIsSuccess(bool success);
    void setStatus(Status status);

    void incrementRef_();
    void decrementRef_();

    bool mSuccess = false;
    Status mStatus = Status::Uninitialized;
    s32 mRefCount = 0;
    ManagedTask* mTask = nullptr;
    TaskQueueBase* mQueue = nullptr;
};
KSYS_CHECK_SIZE_NX150(ManagedTaskHandle, 0x28);

}  // namespace ksys::util
