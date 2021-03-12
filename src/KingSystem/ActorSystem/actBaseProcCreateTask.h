#pragma once

#include <basis/seadTypes.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
}

namespace ksys::act {

class BaseProc;
class BaseProcHandle;
class BaseProcUnit;

struct BaseProcCreateArg {
    sead::Heap* heap;
    sead::Heap* heap2;
    sead::SafeString proc_class;
    sead::SafeString proc_name;
    map::MubinIter* mubin_iter;
    map::Object* map_object;
    InstParamPack::Buffer* params;
    BaseProcLink proc_link;
};
KSYS_CHECK_SIZE_NX150(BaseProcCreateArg, 0x58);

class BaseProcCreateTaskData : public util::TaskData {
    SEAD_RTTI_OVERRIDE(BaseProcCreateTaskData, util::TaskData)

public:
    BaseProcCreateTaskData() = default;
    virtual ~BaseProcCreateTaskData() = default;

    sead::Heap* mHeap{};
    sead::SafeString mProcClass{};
    sead::SafeString mProcName{};
    sead::IDelegate1R<BaseProcCreateArg&, BaseProc*>* mCreateDelegate{};
    BaseProcHandle* mProcHandle{};
    map::MubinIter* mMubinIter{};
    map::Object* mMapObject{};
    InstParamPack::Buffer* mParams{};
    BaseProc* mOtherProc{};
    bool mSleepAfterInit{};
};
KSYS_CHECK_SIZE_NX150(BaseProcCreateTaskData, 0x68);

class BaseProcCreateTaskRequest : public util::TaskRequest {
    SEAD_RTTI_OVERRIDE(BaseProcCreateTaskRequest, util::TaskRequest)

public:
    BaseProcCreateTaskRequest() = default;

    BaseProcCreateTaskData* mData{};
};

class BaseProcCreateTask : public util::ManagedTask {
    SEAD_RTTI_OVERRIDE(BaseProcCreateTask, util::ManagedTask)

public:
    enum class LaneId : u8 {
        _0 = 0,
        _1 = 1,
        _2 = 2,
    };

    explicit BaseProcCreateTask(sead::Heap* heap);

    void onBaseProcCreationFailed(BaseProc* proc, bool set_flag_5);

protected:
    void prepareImpl_(util::TaskRequest* req) override;

private:
    friend class BaseProcCreateTaskSelector;

    bool onTaskDelegateInvoked(void* arg);
    void doPrepare(const BaseProcCreateTaskData* data);

    sead::Heap* mHeap;
    sead::FixedSafeString<64> mClass;
    sead::FixedSafeString<64> mName;
    map::MubinIter mMubinIter;
    sead::IDelegate1R<BaseProcCreateArg&, BaseProc*>* mCreateDelegate{};
    BaseProcUnit* mUnit{};
    map::Object* mMapObject{};
    util::TaskDelegateT<BaseProcCreateTask> mTaskDelegate{
        this, &BaseProcCreateTask::onTaskDelegateInvoked};
    BaseProcLink mLink;
    f32 mDistanceToLoadSphere = -1.0;
    InstParamPack::Buffer mParams;
};
KSYS_CHECK_SIZE_NX150(BaseProcCreateTask, 0x298);

}  // namespace ksys::act
