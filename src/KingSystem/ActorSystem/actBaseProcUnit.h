#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"

namespace ksys::act {

class BaseProc;
class BaseProcHandle;

/// Glue code between a BaseProcHandle and its associated BaseProc.
/// Used while a BaseProc is being created.
class BaseProcUnit {
public:
    enum class Status : u32 {
        Unused = 0,
        Initializing = 1,
        Ready = 2,
        NoProc = 3,
        _4 = 4,
        Cancelled = 5,
    };

    BaseProcUnit() = default;
    ~BaseProcUnit();

    BaseProcUnit(const BaseProcUnit&) = delete;
    BaseProcUnit(BaseProcUnit&&) = delete;
    auto operator=(const BaseProcUnit&) = delete;
    auto operator=(BaseProcUnit&&) = delete;

    bool deleteProc(u32, BaseProcHandle* handle);
    bool setProc(BaseProc* proc);
    void unlinkProc(BaseProc* proc);
    void cleanUp(BaseProc* proc, bool is_cancellation);
    bool isParentHandleDefault() const;

    Status getStatus() const { return mStatus; }
    BaseProc* getProc() const { return mProc; }
    BaseProcCreateTask& getCreateTask() { return mCreateTask; }
    const BaseProcCreateTask& getCreateTask() const { return mCreateTask; }
    sead::CriticalSection& getCS() { return mCS; }

    bool isReady() const { return mStatus == Status::Ready; }

    bool compareExchangeHandle(BaseProcHandle* expected, BaseProcHandle* desired) {
        return mHandle.compareExchange(expected, desired);
    }

    void setInitializingStatus() { mStatus = Status::Initializing; }

private:
    void reset();

    BaseProcHandle* getHandle() const { return mHandle.load(); }

    sead::Atomic<Status> mStatus = Status::Unused;
    sead::Atomic<BaseProcHandle*> mHandle{};
    BaseProc* mProc{};
    BaseProcCreateTask mCreateTask{nullptr};
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(BaseProcUnit, 0x2f0);

struct BaseProcUnitPool {
    BaseProcUnit* get(int i) { return &units[i]; }

    sead::SafeArray<BaseProcUnit, 256> units;
    int idx = 0;
};

extern BaseProcUnitPool gUnitPool;
extern BaseProcHandle gDummyProcHandle;

}  // namespace ksys::act
