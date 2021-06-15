#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::act {

static util::InitTimeInfo sInfo;

BaseProcHandle::BaseProcHandle() = default;

BaseProcHandle::~BaseProcHandle() {
    deleteProc();
}

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

    int idx = gUnitPool.idx;
    for (int i = 0; i < gUnitPool.units.size(); ++idx, ++i) {
        idx = (idx == gUnitPool.units.size()) ? 0 : idx;
        auto* unit = gUnitPool.get(idx);

        if (!unit->getCreateTask().canSubmitRequest())
            continue;
        if (unit->getProc() != nullptr)
            continue;
        if (!unit->compareExchangeHandle(nullptr, this))
            continue;

        gUnitPool.idx = idx + 1;
        mUnit = unit;
        if (!mUnit)
            return false;

        mUnit->setInitializingStatus();
        return true;
    }

    mUnit = nullptr;
    return false;
}

}  // namespace ksys::act
