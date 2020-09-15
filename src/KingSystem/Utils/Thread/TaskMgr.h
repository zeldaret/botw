#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadScopedLock.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class ManagedTask;
class ManagedTaskHandle;
class TaskRequest;
struct TaskMgrRequest;

using ManagedTaskFactory = sead::IDelegate1<ManagedTask**>;

struct TaskMgrRequest {
    /// Optional. If null, a task from the internal buffer will be used.
    ManagedTask* task;
    /// Must not be null.
    TaskRequest* request;
    /// Optional.
    ManagedTaskHandle* handle;
};
KSYS_CHECK_SIZE_NX150(TaskMgrRequest, 0x18);

class TaskMgr {
    SEAD_RTTI_BASE(TaskMgr)
public:
    explicit TaskMgr(sead::Heap* heap);
    virtual ~TaskMgr();

    void init(s32 num_tasks, sead::Heap* heap, ManagedTaskFactory& factory);
    void finalize();

    void submitRequest(TaskMgrRequest& request);
    bool trySubmitRequest(TaskMgrRequest& request);

    bool hasTasks() const;

    void freeTask(ManagedTask* task);

protected:
    enum class Flag {
        HeapIsFreeable = 0x1,
    };

    bool fetchIdleTaskForRequest_(TaskMgrRequest& request, bool retry_until_success);
    ManagedTask* fetchIdleTask_(bool retry_until_success);

    u8 getListIndex_() const { return mListIndex; }
    u8 getListIndex2_() const { return ~mListIndex & 1; }

    void swapLists_() {
        auto lock = sead::makeScopedLock(mCS2);
        mListIndex = getListIndex2_();
        mNewFreeTaskEvent.resetSignal();
    }

    bool tryFetchTaskForRequest_(TaskMgrRequest& request, bool b) {
        if (!mTasksCS.tryLock())
            return false;

        const bool ret = fetchIdleTaskForRequest_(request, b);
        mTasksCS.unlock();
        return ret;
    }

    sead::TypedBitFlag<Flag, u8> mFlags;
    u8 mListIndex = 0;
    ManagedTask* mTask = nullptr;
    sead::CriticalSection mTasksCS;
    sead::CriticalSection mCS2;
    Event mNewFreeTaskEvent;
    Event mEvent2;
    sead::SafeArray<sead::OffsetList<ManagedTask>, 2> mFreeTaskLists;
    sead::Buffer<ManagedTask*> mTasks;
};
KSYS_CHECK_SIZE_NX150(TaskMgr, 0x158);

}  // namespace ksys::util
