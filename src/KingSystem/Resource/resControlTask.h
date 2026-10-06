#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class Handle;
class ResourceUnit;

class ControlTaskData : public TaskData {
    SEAD_RTTI_OVERRIDE(ControlTaskData, TaskData)
public:
    virtual ~ControlTaskData() = default;

    bool mHasResLoadReq = false;
    ResourceUnit* mPackResUnit = nullptr;
    Handle* mResHandle = nullptr;
    sead::FixedSafeString<128> mResPath;
    LoadRequest mResLoadReq;
};
KSYS_CHECK_SIZE_NX150(ControlTaskData, 0x138);

class ControlTask : public ManagedTask {
    SEAD_RTTI_OVERRIDE(ControlTask, ManagedTask)
public:
    explicit ControlTask(sead::Heap* heap);

private:
    void onRun_() override;
    void prepareImpl_(TaskRequest* req) override;
    void preRemoveImpl_() override;

    ControlTaskData mData;
};
KSYS_CHECK_SIZE_NX150(ControlTask, 0x1f8);

class ControlTaskRequest : public TaskRequest {
    SEAD_RTTI_OVERRIDE(ControlTaskRequest, TaskRequest)
public:
    explicit ControlTaskRequest(bool has_handle = false) : TaskRequest(has_handle) {}

    bool mHasResLoadReq = false;
    ResourceUnit* mPackResUnit = nullptr;
    Handle* mResHandle = nullptr;
    sead::FixedSafeString<128> mResPath;
    LoadRequest mResLoadReq;
};
KSYS_CHECK_SIZE_NX150(ControlTaskRequest, 0x180);

}  // namespace ksys::res
