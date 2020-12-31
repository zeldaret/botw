#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadScopeGuard.h>
#include <prim/seadScopedLock.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorLinkConstDataAccess;
class BaseProc;
class BaseProcLinkData;

class BaseProcLink {
public:
    BaseProcLink();
    ~BaseProcLink() { reset(); }
    BaseProcLink& operator=(const BaseProcLink& rhs);

    bool operator==(const BaseProcLink& rhs) const;
    bool operator!=(const BaseProcLink& rhs) const { return !operator==(rhs); }
    explicit operator bool() const { return hasProc(); }

    bool hasProc() const;
    bool hasProcInCalcState() const;
    bool hasProcById(BaseProc* proc) const;

    BaseProc* getProc(ActorLinkConstDataAccess* accessor, BaseProc* other_proc) const;
    BaseProc* getProc(ActorLinkConstDataAccess* accessor) const;

    /// Acquire the specified BaseProc.
    /// If a BaseProc has already been specified, it is released.
    ///
    /// @param acquire_immediately  If true, the BaseProc's reference count is immediately
    ///                             incremented. Otherwise, full acquisition is delayed until
    ///                             the next call to getProc(accessor[, proc]).
    bool acquire(BaseProc* proc, bool acquire_immediately);
    void reset();

    bool isAccessingSpecifiedProcUnsafe(BaseProc* other) const;

    template <typename Function>
    auto getProcInContext(const Function& function) const;

private:
    static constexpr u32 cInvalidId = -1;

    BaseProc* getProc() const;

    BaseProcLinkData* mData = nullptr;
    u32 mId = cInvalidId;
    bool mAcquired = false;
};
KSYS_CHECK_SIZE_NX150(BaseProcLink, 0x10);

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
    friend class BaseProcLink;
    friend class BaseProcLinkDataMgr;

    sead::CriticalSection mCS;
    u32 mId = -1;
    BaseProc* mProc = nullptr;
    sead::Atomic<s32> mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(BaseProcLinkData, 0x58);

class BaseProcLinkDataMgr {
    SEAD_SINGLETON_DISPOSER(BaseProcLinkDataMgr)
    BaseProcLinkDataMgr() = default;

public:
    bool acquireLink(BaseProc* proc);
    bool releaseLink(BaseProc* proc);

private:
    sead::CriticalSection mCS;
    s32 mIndex = 0;
    sead::SafeArray<BaseProcLinkData, 2048> mData{};
};
KSYS_CHECK_SIZE_NX150(BaseProcLinkDataMgr, 0x2C068);

inline BaseProc* BaseProcLink::getProc() const {
    return mData->getProc(mId, mAcquired);
}

template <typename Function>
inline auto BaseProcLink::getProcInContext(const Function& function) const {
    if (mId == cInvalidId)
        return function(nullptr, false);

    const auto guard = sead::makeScopeGuard([crit_section = mData->lockIfNeeded()] {
        if (crit_section)
            crit_section->unlock();
    });

    return function(getProc(), true);
}

}  // namespace ksys::act
