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
    s32 refCount() const { return mRefCount; }

    /// Get the stored BaseProc.
    BaseProc* getProc() const { return mProc; }
    /// Get the stored BaseProc or nullptr if its ID or state are unexpected.
    /// @param id  The expected ID.
    /// @param allow_deleted  Whether to allow the BaseProc to be in the Delete state.
    BaseProc* getProc(u32 id, bool allow_deleted) const;

    /// Locks the critical section if on a low priority thread and returns it;
    /// unlocking it is the responsibility of the caller.
    /// Returns nullptr if on a high priority thread. In that case, nothing needs to be done.
    sead::CriticalSection* lockIfNeeded();

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
