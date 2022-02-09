#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::util {

class LowPrioThreadMgr {
    SEAD_SINGLETON_DISPOSER(LowPrioThreadMgr)
    SEAD_RTTI_BASE(LowPrioThreadMgr)

public:
    struct InitArg {
        sead::Heap* heap;
        s32 priority;
        s32 queue_size;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    struct CoreThreadTask {
        TaskThread* task_thread{};
        TaskMgr* task_mgr{};
    };
    KSYS_CHECK_SIZE_NX150(CoreThreadTask, 0x10);

    struct Request {
        bool try_submit;
        s32 lane_id;
        sead::BitFlag32 flags;
        TaskDelegate* delegate;
        void* user_data;
        TaskRemoveCallback* remove_callback;
        TaskPostRunCallback* post_callback;
        ManagedTask* task;
        TaskMgr* mgr;
        ManagedTaskHandle* handle;
        sead::SafeString name;
    };
    KSYS_CHECK_SIZE_NX150(Request, 0x58);

    LowPrioThreadMgr() = default;
    virtual ~LowPrioThreadMgr();

    bool startThread(const LowPrioThreadMgr::InitArg& initArg);
    bool submitRequest(const LowPrioThreadMgr::Request& request);
    void pauseAllTasks();
    void resumeAllTasks();
    void sub_710127AC40();

private:
    sead::Buffer<CoreThreadTask> mCoreThreadTasks{};
};

}  // namespace ksys::util
