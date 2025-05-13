#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;
class BaseProcCreateTask;
class BaseProcUnit;

class BaseProcHandle {
public:
    BaseProcHandle();
    ~BaseProcHandle() { deleteProc(); }

    BaseProcHandle(const BaseProcHandle&) = delete;
    BaseProcHandle(BaseProcHandle&&) = delete;
    auto operator=(const BaseProcHandle&) = delete;
    auto operator=(BaseProcHandle&&) = delete;

    bool isProcReady() const;
    bool hasProcCreationFailed() const;
    bool isProcCreationCancelled() const;

    void deleteProcIfFailed();
    void deleteProc();

    BaseProc* getProc() const;
    BaseProc* releaseProc();
    BaseProc* releaseAndWakeProc();
    BaseProcCreateTask* getCreateTask() const;
    BaseProcUnit* getUnit() const { return mUnit; }
    bool allocUnit();

    bool hasFailed() const { return mFailed; }
    void setFailed(bool failed) { mFailed = failed; }

private:
    BaseProcUnit* mUnit = nullptr;
    bool mFailed = false;
};
KSYS_CHECK_SIZE_NX150(BaseProcHandle, 0x10);

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
    sead::Atomic<BaseProcHandle*> mHandle;
    BaseProc* mProc{};
    BaseProcCreateTask mCreateTask{nullptr};
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(BaseProcUnit, 0x2f0);

struct BaseProcUnitPool {
    struct Impl {
        sead::SafeArray<BaseProcUnit, 256> array;
    } units{};
    int next = 0;

    BaseProcUnit* alloc(BaseProcHandle* handle) {
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
};

extern BaseProcUnitPool gUnitPool;
extern BaseProcHandle gDummyProcHandle;

}  // namespace ksys::act
