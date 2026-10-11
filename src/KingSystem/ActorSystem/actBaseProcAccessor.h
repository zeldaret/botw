#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <utility>

namespace ksys::act {

class BaseProc;

/// Holds a reference to a BaseProc for safe, multi-threaded access.
class BaseProcAccessor {
public:
    BaseProcAccessor() = default;
    explicit BaseProcAccessor(BaseProc* proc) { acquire(proc); }
    /// Destructor that automatically releases any acquired BaseProc.
    ~BaseProcAccessor();

    BaseProcAccessor(const BaseProcAccessor&) = delete;
    BaseProcAccessor& operator=(const BaseProcAccessor&) = delete;
    BaseProcAccessor(BaseProcAccessor&& other) noexcept { *this = std::move(other); }
    BaseProcAccessor& operator=(BaseProcAccessor&& other) noexcept {
        std::swap(mAcquired, other.mAcquired);
        std::swap(mProc, other.mProc);
        return *this;
    }

    /// Acquire a BaseProc. This increments its reference count.
    /// If an actor was already acquired, it is released.
    bool acquire(BaseProc* proc);

    void release() { acquire(nullptr); }

    bool hasProc() const { return mProc != nullptr; }

protected:
    friend class ActorLinkConstDataAccess;
    friend class BaseProc;
    friend class BaseProcHandle;
    friend class BaseProcUnit;

    bool mAcquired = false;
    BaseProc* mProc = nullptr;
};

/// Acquire the specified BaseProc using `accessor`. Using ActorLinkConstDataAccess is mandatory
/// when acquiring from a low priority thread (see BaseProcMgr for a definition).
bool acquireProc(BaseProcAccessor* accessor, BaseProc* proc, const sead::SafeString& from, s32 = 2);

}  // namespace ksys::act
