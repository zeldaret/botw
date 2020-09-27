#include "KingSystem/Resource/resMemoryTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

MemoryTask::MemoryTask(sead::Heap* heap) : util::ManagedTask(heap) {}

void MemoryTask::onRun_() {}

void MemoryTask::prepareImpl_(util::TaskRequest* req_) {
    auto* req = static_cast<MemoryTaskRequest*>(req_);
    mData._8 = req->mData_8;
    mData._c = req->mData_c;
    mData.mStr = req->mData_mStr;
    setUserData();
}

void MemoryTask::preRemoveImpl_() {
    if (returnFalse())
        stubbedLogFunction();
}

}  // namespace ksys::res
