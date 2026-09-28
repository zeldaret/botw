#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class MemoryTaskData : public TaskData {
    SEAD_RTTI_OVERRIDE(MemoryTaskData, TaskData)
public:
    virtual ~MemoryTaskData() = default;

    bool _8 = false;
    s32 _c = -1;
    sead::FixedSafeString<128> mStr;
};
KSYS_CHECK_SIZE_NX150(MemoryTaskData, 0xa8);

class MemoryTask : public ManagedTask {
    SEAD_RTTI_OVERRIDE(MemoryTask, ManagedTask)
public:
    explicit MemoryTask(sead::Heap* heap);
    ~MemoryTask() override { ; }

private:
    void onRun_() override;
    void prepareImpl_(TaskRequest* req) override;
    void preRemoveImpl_() override;

    void setUserData() { ManagedTask::setUserData(&mData); }

    MemoryTaskData mData;
};
KSYS_CHECK_SIZE_NX150(MemoryTask, 0x168);

class MemoryTaskRequest : public TaskRequest {
    SEAD_RTTI_OVERRIDE(MemoryTaskRequest, TaskRequest)
public:
    MemoryTaskRequest() = default;

    bool mData_8 = false;
    s32 mData_c = -1;
    sead::SafeString mData_mStr;
};
KSYS_CHECK_SIZE_NX150(MemoryTaskRequest, 0x68);

}  // namespace ksys::res
