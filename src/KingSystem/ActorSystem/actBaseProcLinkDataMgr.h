#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;

class BaseProcLinkData {
public:
    u32 id() const { return mId; }
    BaseProc* proc() const { return mProc; }
    s32 refCount() const { return mRefCount; }

private:
    friend class BaseProcLinkDataMgr;

    sead::CriticalSection mCS;
    u32 mId = -1;
    BaseProc* mProc = nullptr;
    s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(BaseProcLinkData, 0x58);

class BaseProcLinkDataMgr {
    SEAD_SINGLETON_DISPOSER(BaseProcLinkDataMgr)

public:
    bool acquireLink(BaseProc* proc);
    bool releaseLink(BaseProc* proc);

private:
    sead::CriticalSection mCS;
    s32 mIndex = 0;
    sead::SafeArray<BaseProcLinkData, 2048> mData{};
};
KSYS_CHECK_SIZE_NX150(BaseProcLinkDataMgr, 0x2C068);

}  // namespace ksys::act
