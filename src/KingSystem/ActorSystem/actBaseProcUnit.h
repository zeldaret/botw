#pragma once

#include <basis/seadTypes.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include <thread/seadAtomic.h>
namespace ksys::act {

class BaseProc;
class BaseProcHandle;

class BaseProcUnit {
public:
    bool deleteProc(void*, BaseProcHandle* handle);
    bool setProc(BaseProc* proc);
    void unlinkProc(BaseProc* proc);
    void cleanUp(BaseProc* proc, bool set_flag_5);
    bool isParentHandleDefault() const;

private:
    u32 mFlags;
    sead::Atomic<BaseProcHandle*> mHandle;
    BaseProc* mProc;
    // FIXME:
    // BaseProcRequest mRequest;
    sead::CriticalSection mCS;
};

}  // namespace ksys::act
