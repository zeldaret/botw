#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
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
        s32 queueSize;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    struct CoreThreadTask {
        TaskThread* taskThread{};
        TaskMgr* taskMgr{};
    };
    KSYS_CHECK_SIZE_NX150(CoreThreadTask, 0x10);

    struct Request {
        s8 unk_00;
        s32 laneId;
        sead::BitFlag32 flags;
        TaskDelegate* delegate;
        void* userData;
        TaskRemoveCallback* removeCallback;
        TaskPostRunCallback* postCallback;
        ManagedTask* task;
        TaskMgr* mgr;
        ManagedTaskHandle* handle;
        sead::SafeString name;
    };
    KSYS_CHECK_SIZE_NX150(Request, 0x58);

    LowPrioThreadMgr() = default;
    virtual ~LowPrioThreadMgr();

    auto startThread(LowPrioThreadMgr::InitArg* initArg) -> bool;
    auto submitRequest(const LowPrioThreadMgr::Request& request) -> bool;
    auto pauseAllThreads() -> void;
    auto resumeAllThreads() -> void;

private:
    sead::Buffer<CoreThreadTask> mCoreThreadTasks{};
};

}  // namespace ksys::util
