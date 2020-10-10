#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

ControlTask::ControlTask(sead::Heap* heap) : util::ManagedTask(heap) {}

void ControlTask::onRun_() {}

void ControlTask::prepareImpl_(util::TaskRequest* req_) {
    auto* req = static_cast<ControlTaskRequest*>(req_);

    mData.mHasResLoadReq = req->mHasResLoadReq;
    mData.mPackResUnit = req->mPackResUnit;
    mData.mResHandle = req->mResHandle;
    mData.mResPath = req->mResPath;
    mData.mResLoadReq = req->mResLoadReq;
    mData.mResLoadReq.mPath = mData.mResPath;

    if (getUserData() == nullptr)
        setUserData(&mData);
}

void ControlTask::preRemoveImpl_() {
    if (returnFalse())
        stubbedLogFunction();
}

}  // namespace ksys::res
