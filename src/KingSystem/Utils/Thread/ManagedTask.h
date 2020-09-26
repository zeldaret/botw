#pragma once

#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class ManagedTaskHandle;
class TaskMgr;

class ManagedTask : public Task {
    SEAD_RTTI_OVERRIDE(ManagedTask, Task)
public:
    explicit ManagedTask(sead::Heap* heap);
    explicit ManagedTask(sead::IDisposer::HeapNullOption heap_null_option);
    ~ManagedTask() override;

    bool isIdle() const;

protected:
    friend class ManagedTaskHandle;
    friend class TaskMgr;

    void setMgr(TaskMgr* mgr);
    void attachHandle(ManagedTaskHandle* handle, TaskQueueBase* queue);
    void detachHandle();

    void prepare_(TaskRequest* request) override;
    void run_() override;
    void onRunFinished_() override;
    void onFinish_() override;
    void onPostFinish_() override;
    void preRemove_() override;
    void postRemove_() override;

    virtual void onRun_();
    virtual void prepareImpl_(TaskRequest* req);
    virtual void preRemoveImpl_();

    bool mIsIdle = true;
    TaskMgr* mMgr = nullptr;
    ManagedTaskHandle* mHandle = nullptr;
};
KSYS_CHECK_SIZE_NX150(ManagedTask, 0xc0);

}  // namespace ksys::util
