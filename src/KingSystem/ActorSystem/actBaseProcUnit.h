#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>

namespace ksys::act {

class BaseProc;
class BaseProcHandle;

class BaseProcUnit {
public:
    bool deleteProc(u32, BaseProcHandle* handle);
    bool setProc(BaseProc* proc);
    void unlinkProc(BaseProc* proc);
    void cleanUp(BaseProc* proc, bool set_flag_5);
    bool isParentHandleDefault() const;

    BaseProc* getProc() const { return mProc; }
    bool isReady() const { return mFlags == 2; }

private:
    u32 mFlags;
    sead::Atomic<BaseProcHandle*> mHandle;
    BaseProc* mProc;
    // FIXME:
    // BaseProcRequest mRequest;
    sead::CriticalSection mCS;
};

}  // namespace ksys::act
