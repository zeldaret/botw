#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"

namespace ksys::act {

class BaseProc;
class BaseProcHandle;

class BaseProcUnit {
public:
    bool deleteProc(u32, BaseProcHandle* handle);
    bool setProc(BaseProc* proc);
    void unlinkProc(BaseProc* proc);
    void cleanUp(BaseProc* proc, bool set_status_5);
    bool isParentHandleDefault() const;

    BaseProc* getProc() const { return mProc; }
    bool isReady() const { return mStatus == Status::Ready; }

private:
    enum class Status : u32 {
        Unused = 0,
        _1 = 1,
        Ready = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
    };

    void reset();

    BaseProcHandle* getHandle() const { return mHandle.load(); }

    sead::Atomic<Status> mStatus = Status::Unused;
    sead::Atomic<BaseProcHandle*> mHandle{};
    BaseProc* mProc{};
    BaseProcCreateTask mCreateTask;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(BaseProcUnit, 0x2f0);

}  // namespace ksys::act
