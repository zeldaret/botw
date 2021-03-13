#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::act {

bool BaseProcUnit::deleteProc(u32, BaseProcHandle* handle) {
    ActorLinkConstDataAccess accessor;

    {
        const auto lock = sead::makeScopedLock(mCS);
        BaseProcHandle* current_handle = mHandle;
        if (current_handle == handle) {
            if (mProc)
                accessor.acquire(mProc);

            if (mStatus == Status::_1 || mProc) {
                mHandle.compareExchange(handle, &BaseProcHandle::sDummyHandle);
            } else {
                mStatus = Status::Unused;
                mHandle = nullptr;
            }
        } else {
            sead::FixedSafeString<256> message;
            message.format("BaseProcUnit:(%p, %p), 呼び出し(%p)", this, current_handle, handle);
            util::PrintDebug(message);
        }
    }

    if (accessor.hasProc())
        accessor.mProc->deleteLater(BaseProc::DeleteReason::_2);

    return true;
}

bool BaseProcUnit::setProc(BaseProc* proc) {
    static constexpr const char* sStateNames[] = {"Init", "Calc", "Sleep", "Delete"};

    auto lock = sead::makeScopedLock(mCS);

    if (mProc)
        mProc = nullptr;

    if (isParentHandleDefault())
        return false;

    const auto print_info = [&] {
        sead::FixedSafeString<64> message;
        if (proc) {
            message.format("%s, %d, %d, %s, ( %p:%p )", proc->getName().cstr(), u32(mStatus.load()),
                           proc->isInitialized(), sStateNames[u8(proc->getState())], this,
                           mHandle.load());
        } else {
            message.format("なし, %d, ?, ?, ( %p:%p )", u32(mStatus.load()), this, mHandle.load());
        }
        util::PrintDebug(message);
    };

    if (!mHandle) {
        print_info();
        return false;
    }

    if (mStatus != Status::_1)
        print_info();

    mProc = proc;
    mStatus = Status::Ready;
    return true;
}

void BaseProcUnit::reset() {
    auto* handle = getHandle();
    if (handle != &BaseProcHandle::sDummyHandle) {
        sead::FixedSafeString<256> message;
        message.format("BaseProcUnit:%p, %p", this, handle);
        util::PrintDebug(message);
    }
    mProc = nullptr;
    mStatus = Status::Unused;
    mHandle = nullptr;
}

void BaseProcUnit::cleanUp(BaseProc* proc, bool set_status_5) {
    const auto lock = sead::makeScopedLock(mCS);

    mProc = nullptr;

    const auto print_info = [&] {
        sead::FixedSafeString<64> message;
        message.format("%d, ( %p:%p )", u32(mStatus.load()), this, mHandle.load());
        util::PrintDebug(message);
    };

    if (isParentHandleDefault()) {
        reset();
    } else if (!mHandle) {
        print_info();
    } else {
        const auto status = mStatus.load();
        if (status == Status::Unused || (status > Status::_3 && status != Status::_5))
            print_info();
        mStatus = set_status_5 ? Status::_5 : Status::_3;
    }
}

void BaseProcUnit::unlinkProc(BaseProc* proc) {
    const auto lock = sead::makeScopedLock(mCS);

    if (mProc != proc && mProc != nullptr) {
        sead::FixedSafeString<256> message;
        message.format("BaseProcUnit:(%p:%p), BaseProc:(%s:%p), 残りBaseProc(%s:%p)", this,
                       mHandle.load(), proc->getName().cstr(), proc, mProc->getName().cstr(),
                       mProc);
        util::PrintDebug(message);
    }

    reset();
}

bool BaseProcUnit::isParentHandleDefault() const {
    return mHandle == &BaseProcHandle::sDummyHandle;
}

}  // namespace ksys::act
