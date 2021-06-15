#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::act {

BaseProcCreateTask::BaseProcCreateTask(sead::Heap* heap) : ManagedTask(heap) {}

bool BaseProcCreateTask::onTaskDelegateInvoked(void*) {
    BaseProcCreateArg arg;
    arg.heap = mHeap;
    arg.heap2 = arg.heap;
    arg.proc_class = mClass;
    arg.proc_name = mName;
    mDistanceToLoadSphere = -1.0;
    arg.params = mParams.getNumParams() != 0 ? &mParams : nullptr;
    arg.mubin_iter = mMubinIter.isValid() ? &mMubinIter : nullptr;
    arg.map_object = mMapObject;
    arg.proc_link = mLink;
    mLink.reset();
    static_cast<void>(arg.heap2->getMaxAllocatableSize(sizeof(void*)));

    BaseProc* proc = mCreateDelegate->invoke(arg);
    if (proc) {
        proc->setUnitForBaseProcCreateTask(mUnit);

        if (proc->isDeletedOrDeleting() || !proc->init(arg.heap2, false))
            onBaseProcCreationFailed(proc, false);

        proc->setInitializedFlag();
    } else {
        onBaseProcCreationFailed(proc, false);
    }

    return true;
}

void BaseProcCreateTask::onBaseProcCreationFailed(BaseProc* proc, bool set_flag_5) {
    if (mMapObject)
        mMapObject->onBaseProcCreated(proc);

    if (!proc && mUnit) {
        mUnit->cleanUp(proc, set_flag_5);
        mUnit = nullptr;
    }
}

void BaseProcCreateTask::doPrepare(const BaseProcCreateTaskData* arg) {
    auto data = sead::DynamicCast<const BaseProcCreateTaskData>(arg);
    [&] {
        mHeap = data->mHeap;
        mClass = data->mProcClass;
        mName = data->mProcName;

        if (data->mMubinIter)
            mMubinIter = *data->mMubinIter;
        else
            mMubinIter = {};

        mMapObject = data->mMapObject;

        if (data->mParams && data->mParams->getNumParams() != 0)
            mParams = *data->mParams;
        else
            mParams.clearFast();

        mCreateDelegate = data->mCreateDelegate;
        mUnit = data->mProcHandle ? data->mProcHandle->getUnit() : nullptr;

        if (data->mOtherProc)
            mLink.acquire(data->mOtherProc, false);
        else
            mLink.reset();
    }();
}

void BaseProcCreateTask::prepareImpl_(util::TaskRequest* req) {
    doPrepare(sead::DynamicCast<BaseProcCreateTaskRequest>(req)->mData);
    setDelegateInternal_(&mTaskDelegate);
}

}  // namespace ksys::act
