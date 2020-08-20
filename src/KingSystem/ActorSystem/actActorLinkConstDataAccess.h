#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys {

namespace act {

class BaseProc;

/// Provides read-only access to actor data for safe, multi-threaded access.
class ActorLinkConstDataAccess {
public:
    ActorLinkConstDataAccess() = default;
    explicit ActorLinkConstDataAccess(BaseProc* proc) { acquire(proc); }
    /// Destructor that automatically releases any acquired BaseProc.
    ~ActorLinkConstDataAccess();

    /// Acquire a BaseProc. This increments its reference count.
    /// If an actor was already acquired, it is released.
    bool acquire(BaseProc* proc);

    void release() { acquire(nullptr); }

    /// Checks whether the acquired BaseProc is `proc`.
    bool hasProc(BaseProc* proc) const;

    void debugLog(s32, const sead::SafeString& method_name);

private:
    bool mAcquired = false;
    BaseProc* mProc = nullptr;
};

/// Acquire the specified BaseProc using `accessor`. Using ActorLinkConstDataAccess is mandatory
/// when acquiring from a low priority thread (see BaseProcMgr for a definition).
bool acquireProc(ActorLinkConstDataAccess* accessor, BaseProc* proc, const sead::SafeString& from,
                 s32 = 2);

}  // namespace act

}  // namespace ksys
