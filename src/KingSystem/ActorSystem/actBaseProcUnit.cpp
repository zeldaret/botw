#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::act {

BaseProcUnitPool gUnitPool{};
BaseProcHandle gDummyProcHandle;

BaseProcUnit::~BaseProcUnit() {
    deleteProc(0, nullptr);
}

bool BaseProcUnit::deleteProc([[maybe_unused]] u32 x, BaseProcHandle* handle) {
#ifdef MATCHING_HACK_NX_CLANG
    // Ensure x is not optimized out.
    __builtin_assume(x);
#endif

    ActorLinkConstDataAccess accessor;

    {
        const auto lock = sead::makeScopedLock(mCS);
        BaseProcHandle* current_handle = mHandle;
        if (current_handle == handle) {
            if (mProc)
                accessor.acquire(mProc);

            if (mStatus == Status::Initializing || mProc) {
                mHandle.compareExchange(handle, &gDummyProcHandle);
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

    if (mStatus != Status::Initializing)
        print_info();

    mProc = proc;
    mStatus = Status::Ready;
    return true;
}

void BaseProcUnit::reset() {
    auto* handle = getHandle();
    if (handle != &gDummyProcHandle) {
        sead::FixedSafeString<256> message;
        message.format("BaseProcUnit:%p, %p", this, handle);
        util::PrintDebug(message);
    }
    mProc = nullptr;
    mStatus = Status::Unused;
    mHandle = nullptr;
}

void BaseProcUnit::cleanUp(BaseProc* proc, bool is_cancellation) {
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
        if (status == Status::Unused || (status > Status::NoProc && status != Status::Cancelled))
            print_info();
        mStatus = is_cancellation ? Status::Cancelled : Status::NoProc;
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
    return mHandle == &gDummyProcHandle;
}

}  // namespace ksys::act
