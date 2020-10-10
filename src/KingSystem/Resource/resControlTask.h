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

class ControlTaskData : public util::TaskData {
    SEAD_RTTI_OVERRIDE(ControlTaskData, util::TaskData)
public:
    virtual ~ControlTaskData() = default;

    bool mHasResLoadReq = false;
    ResourceUnit* mPackResUnit = nullptr;
    Handle* mResHandle = nullptr;
    sead::FixedSafeString<128> mResPath;
    LoadRequest mResLoadReq;
};
KSYS_CHECK_SIZE_NX150(ControlTaskData, 0x138);

class ControlTask : public util::ManagedTask {
    SEAD_RTTI_OVERRIDE(ControlTask, util::ManagedTask)
public:
    explicit ControlTask(sead::Heap* heap);

private:
    void onRun_() override;
    void prepareImpl_(util::TaskRequest* req) override;
    void preRemoveImpl_() override;

    ControlTaskData mData;
};
KSYS_CHECK_SIZE_NX150(ControlTask, 0x1f8);

class ControlTaskRequest : public util::TaskRequest {
    SEAD_RTTI_OVERRIDE(ControlTaskRequest, util::TaskRequest)
public:
    ControlTaskRequest() = default;

    bool mHasResLoadReq = false;
    ResourceUnit* mPackResUnit = nullptr;
    Handle* mResHandle = nullptr;
    sead::FixedSafeString<128> mResPath;
    LoadRequest mResLoadReq;
};
KSYS_CHECK_SIZE_NX150(ControlTaskRequest, 0x180);

}  // namespace ksys::res
