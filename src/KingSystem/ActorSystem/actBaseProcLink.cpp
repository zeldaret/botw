#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace ksys::act {

BaseProcLink::BaseProcLink() = default;

BaseProcLink& BaseProcLink::operator=(const BaseProcLink& rhs) {
    if (this == &rhs)
        return *this;

    reset();

    if (rhs.mData)
        mData = rhs.mData;
    mId = rhs.mId;

    return *this;
}

bool BaseProcLink::operator==(const BaseProcLink& rhs) const {
    return (!hasProc() && !rhs.hasProc()) || mId == rhs.mId;
}

bool BaseProcLink::hasProc() const {
    return getProc();
}

bool BaseProcLink::hasProcInCalcState() const {
    return getProcInContext(
        [](BaseProc* proc, bool) { return proc && proc->getState() == BaseProc::State::Calc; });
}

bool BaseProcLink::hasProcById(BaseProc* proc) const {
    return proc != nullptr & mId != cInvalidId && mId == proc->getId();
}

BaseProc* BaseProcLink::getProc(ActorLinkConstDataAccess* accessor, BaseProc* other_proc) const {
    return getProcInContext([&](BaseProc* proc, bool) -> BaseProc* {
        if (proc && acquireProc(accessor, proc, "frm::BaseProcLink") &&
            BaseProcMgr::instance()->isAccessingProcSafe(proc, other_proc)) {
            return proc;
        }
        return nullptr;
    });
}

BaseProc* BaseProcLink::getProc(ActorLinkConstDataAccess* accessor) const {
    return getProcInContext([&](BaseProc* proc, bool) -> BaseProc* {
        if (proc && acquireProc(accessor, proc, "frm::BaseProcLink"))
            return proc;
        return nullptr;
    });
}

bool BaseProcLink::acquire(BaseProc* proc, bool acquire_immediately) {
    reset();

    if (!proc || proc->isDeletedOrDeleting())
        return false;

    mData = proc->getBaseProcLinkData();

    if (!mData) {
        static constexpr const char* sStateNames[] = {"Init", "Calc", "Sleep", "Delete"};
        sead::FixedSafeString<256> message;
        message.format("%s:%s", proc->getName().cstr(), sStateNames[u8(proc->getState())]);
        return false;
    }

    mId = proc->getId();
    if (acquire_immediately) {
        mData->mRefCount.increment();
        mAcquired = true;
    }
    return true;
}

void BaseProcLink::reset() {
    if (mAcquired) {
        mAcquired = false;
        if (mData)
            mData->mRefCount.decrement();
    }
    mId = cInvalidId;
}

bool BaseProcLink::isAccessingSpecifiedProcUnsafe(BaseProc* other) const {
    return getProcInContext([&](BaseProc* proc, bool) {
        return proc && !BaseProcMgr::instance()->isAccessingProcSafe(proc, other);
    });
}

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcLinkDataMgr)

BaseProc* BaseProcLinkData::getProc(u32 id, bool allow_deleted) const {
    if (id == u32(-1) || mId != id)
        return nullptr;

    if (!allow_deleted && (!mProc || mProc->getState() == BaseProc::State::Delete))
        return nullptr;

    return mProc;
}

sead::CriticalSection* BaseProcLinkData::lockIfNeeded() {
    if (BaseProcMgr::instance()->isHighPriorityThread())
        return nullptr;

    mCS.lock();
    return &mCS;
}

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
