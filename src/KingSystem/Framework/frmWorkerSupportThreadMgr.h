#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadMessageQueue.h>
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class DelegateThread;
class Thread;
}  // namespace sead

namespace ksys {
class GameTaskThread;
class ManagedTask;
class ManagedTaskHandle;
class TaskMgr;
}  // namespace ksys

namespace ksys::frm {

class WorkerSupportThreadMgr {
    SEAD_SINGLETON_DISPOSER(WorkerSupportThreadMgr)
    WorkerSupportThreadMgr() = default;
    ~WorkerSupportThreadMgr() = default;

public:
    void init(sead::Heap* heap);

    void submitRequest(int id, TaskDelegate* delegate);
    void waitForTask(int id);
    void pauseThreads();
    void resumeThreads();
    void destroyThreads();

private:
    static constexpr int NumWorkers = 2;
    static constexpr int NumTasks = 5;

    struct Worker {
        GameTaskThread* task_thread = nullptr;
        sead::DelegateThread* thread;
        ManagedTask* tasks[NumTasks];
        TaskMgr* task_mgr = nullptr;
        ManagedTaskHandle* task_handle;
        sead::FixedSafeString<32> thread_name;
    };

    void initSleeperThreads();
    void sleeperThreadFun(sead::Thread* thread, sead::MessageQueue::Element);

    ManagedTask* getTask(int id);

    Worker mWorkers[NumWorkers];
    bool mThreadsPaused = false;
    sead::Heap* mSleeperHeap;
};
KSYS_CHECK_SIZE_NX150(WorkerSupportThreadMgr, 0x130);

}  // namespace ksys::frm
