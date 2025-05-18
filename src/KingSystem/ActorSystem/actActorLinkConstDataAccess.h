#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace ksys {
struct MesTransceiverId;
namespace act {

class Actor;
class BaseProc;

/// Provides read-only access to actor data for safe, multi-threaded access.
class ActorLinkConstDataAccess {
public:
    ActorLinkConstDataAccess() = default;
    explicit ActorLinkConstDataAccess(BaseProc* proc) { acquire(proc); }
    /// Destructor that automatically releases any acquired BaseProc.
    ~ActorLinkConstDataAccess();

    ActorLinkConstDataAccess(const ActorLinkConstDataAccess&) = delete;
    ActorLinkConstDataAccess& operator=(const ActorLinkConstDataAccess&) = delete;
    ActorLinkConstDataAccess(ActorLinkConstDataAccess&& other) noexcept {
        *this = std::move(other);
    }
    ActorLinkConstDataAccess& operator=(ActorLinkConstDataAccess&& other) noexcept {
        std::swap(mAcquired, other.mAcquired);
        std::swap(mProc, other.mProc);
        return *this;
    }

    /// Acquire a BaseProc. This increments its reference count.
    /// If an actor was already acquired, it is released.
    bool acquire(BaseProc* proc);

    void release() { acquire(nullptr); }

    bool hasProc() const { return mProc != nullptr; }

    const MesTransceiverId* getMessageTransceiverId() const;
    const Actor* getActor() const;
    const sead::Matrix34f& getActorMtx();

protected:
    friend class ActorConstDataAccess;
    friend class BaseProc;
    friend class BaseProcHandle;
    friend class BaseProcUnit;

    bool mAcquired = false;
    BaseProc* mProc = nullptr;
};

/// Acquire the specified BaseProc using `accessor`. Using ActorLinkConstDataAccess is mandatory
/// when acquiring from a low priority thread (see BaseProcMgr for a definition).
bool acquireProc(ActorLinkConstDataAccess* accessor, BaseProc* proc, const sead::SafeString& from,
                 s32 = 2);

}  // namespace act

}  // namespace ksys
