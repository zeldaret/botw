#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::act {

BaseProcUnitPool gUnitPool{};
BaseProcHandle gDummyProcHandle;

BaseProcHandle::BaseProcHandle() = default;

bool BaseProcHandle::isProcReady() const {
    return mUnit && mUnit->isReady();
}

bool BaseProcHandle::hasProcCreationFailed() const {
    if (mFailed)
        return true;

    if (!mUnit)
        return false;

    const auto status = mUnit->getStatus();
    if (status == BaseProcUnit::Status::NoProc || status == BaseProcUnit::Status::Cancelled)
        return true;

    if (mUnit->getCreateTask().getStatus() == util::Task::Status::RemovedFromQueue ||
        status == BaseProcUnit::Status::Cancelled) {
        return true;
    }

    return false;
}

bool BaseProcHandle::isProcCreationCancelled() const {
    if (!mUnit)
        return false;

    if (mUnit->getCreateTask().getStatus() == util::Task::Status::RemovedFromQueue)
        return true;

    if (mUnit->getStatus() == BaseProcUnit::Status::Cancelled)
        return true;

    return false;
}

void BaseProcHandle::deleteProcIfFailed() {
    if (mFailed && !mUnit) {
        mFailed = false;
        return;
    }

    if (hasProcCreationFailed())
        deleteProc();
}

void BaseProcHandle::deleteProc() {
    if (mUnit) {
        mUnit->deleteProc(0, this);
        mUnit = nullptr;
    }
    mFailed = false;
}

BaseProc* BaseProcHandle::getProc() const {
    if (mUnit)
        return mUnit->getProc();

    return nullptr;
}

BaseProc* BaseProcHandle::releaseProc() {
    if (!isProcReady())
        return nullptr;

    BaseProcUnit* unit = mUnit;
    BaseProc* proc = nullptr;

    {
        ActorLinkConstDataAccess accessor;
        {
            const auto lock = sead::makeScopedLock(unit->getCS());
            if (unit->compareExchangeHandle(this, &gDummyProcHandle)) {
                if (unit->getProc())
                    accessor.acquire(unit->getProc());
            }
        }

        proc = accessor.mProc;
        if (proc)
            proc->requestDeleteProcUnit();
    }

    mUnit = nullptr;
    return proc;
}

BaseProc* BaseProcHandle::releaseAndWakeProc() {
    if (!isProcReady())
        return nullptr;

    BaseProcUnit* unit = mUnit;
    BaseProc* proc = nullptr;

    {
        ActorLinkConstDataAccess accessor;
        {
            const auto lock = sead::makeScopedLock(unit->getCS());
            if (unit->compareExchangeHandle(this, &gDummyProcHandle)) {
                if (unit->getProc())
                    accessor.acquire(unit->getProc());
            }
        }

        proc = accessor.mProc;
        if (proc)
            proc->wakeUp(BaseProc::SleepWakeReason::_0);
    }

    mUnit = nullptr;
    return proc;
}

BaseProcCreateTask* BaseProcHandle::getCreateTask() const {
    sead::Atomic<BaseProcUnit*> unit = mUnit;
    auto* ret = unit ? &unit->getCreateTask() : nullptr;
    static_cast<void>(unit.load());
    return ret;
}

bool BaseProcHandle::allocUnit() {
    if (mUnit)
        return false;

    mUnit = gUnitPool.alloc(this);
    if (!mUnit)
        return false;

    mUnit->setInitializingStatus();
    return true;
}

BaseProcUnit* BaseProcUnitPool::alloc(BaseProcHandle* handle) {
    int idx = next;
    for (int i = 0; i < units.array.size(); ++idx, ++i) {
        idx = (idx == units.array.size()) ? 0 : idx;
        auto* unit = &units.array[idx];

        if (!unit->getCreateTask().canSubmitRequest())
            continue;
        if (unit->getProc() != nullptr)
            continue;
        if (!unit->compareExchangeHandle(nullptr, handle))
            continue;

        next = idx + 1;
        return unit;
    }
    return nullptr;
}

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
