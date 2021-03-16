#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::util {
class TaskMgr;
class TaskQueue;
class TaskThread;
}  // namespace ksys::util

namespace ksys::act {

class BaseProc;
struct BaseProcCreateRequest;

struct BaseProcInitializerArgs {
    u32 queue_size;
    sead::SafeString thread_name = "BaseProcCreate";
    util::TaskSelectionDelegate* task_selector = nullptr;
};

class BaseProcInitializer {
public:
    struct ThreadInfo {
        bool valid = false;
        util::TaskThread* thread = nullptr;
        sead::FixedSafeString<32> thread_name;
    };
    KSYS_CHECK_SIZE_NX150(ThreadInfo, 0x48);

    BaseProcInitializer();
    virtual ~BaseProcInitializer();

    BaseProcInitializer(const BaseProcInitializer&) = delete;
    BaseProcInitializer(BaseProcInitializer&&) = delete;
    auto operator=(const BaseProcInitializer&) = delete;
    auto operator=(BaseProcInitializer&&) = delete;

    const sead::Buffer<ThreadInfo>& getThreads() const { return mThreads; }

    bool isActorGenerationEnabled() const { return mActorGenerationEnabled; }

    void init(sead::Heap* parent_heap, const BaseProcInitializerArgs& args);
    void deleteThreadIfPaused();

    bool requestCreateBaseProc(const BaseProcCreateRequest& req);
    BaseProc* createBaseProc(const BaseProcCreateRequest& req);

    void restartThreads();
    void blockPendingTasks();
    void pauseThreads();
    void resumeThreads();
    void unblockPendingTasks();

    void pauseMainThread();
    void resumeMainThread();

    bool isAnyThreadActive() const;
    void waitForTaskQueuesToEmpty();
    void cancelTasks();
    int getQueueSize(int x = -1) const;

    void removeTasksIf(sead::IDelegate1R<util::Task*, bool>& predicate);
    void setActorGenerationEnabled(bool enabled);

    util::TaskQueue* getTaskQueue() const { return mTaskQueue; }

private:
    sead::Buffer<ThreadInfo> mThreads;
    util::TaskMgr* mTaskMgr = nullptr;
    util::TaskQueue* mTaskQueue = nullptr;
    sead::Heap* mHeap = nullptr;
    bool mActorGenerationEnabled = true;
};
KSYS_CHECK_SIZE_NX150(BaseProcInitializer, 0x38);

}  // namespace ksys::act
