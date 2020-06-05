#include "KingSystem/ActorSystem/actBaseProcLinkDataMgr.h"
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcLinkDataMgr)

bool BaseProcLinkDataMgr::acquireLink(BaseProc* proc) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = mIndex;
    for (s32 i = 0; i < mData.size(); ++i) {
        const s32 j = index == 0x800 ? 0 : index;
        auto& data = mData[j];
        if (data.mId == u32(-1)) {
            {
                auto data_lock = sead::makeScopedLock(data.mCS);
                data.mProc = proc;
                data.mId = proc->mId;
                proc->mBaseProcLinkData = &data;
            }
            mIndex = j + 1;
            return true;
        }
        index = j + 1;
    }

    for (s32 i = 0; i < mData.size(); ++i) {
        auto data_lock = sead::makeScopedLock(mData[i].mCS);
        // Debug code was probably here?
    }

    return false;
}

bool BaseProcLinkDataMgr::releaseLink(BaseProc* proc) {
    auto* data = proc->mBaseProcLinkData;
    if (!data)
        return false;

    const auto thread = sead::ThreadMgr::instance()->getCurrentThread();
    thread->getPriority();

    auto lock = sead::makeScopedLock(data->mCS);
    data->mProc = nullptr;
    data->mId = -1;
    proc->mBaseProcLinkData = nullptr;
    return true;
}

}  // namespace ksys::act
