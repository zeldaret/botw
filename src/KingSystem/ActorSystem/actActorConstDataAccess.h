#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorConstDataAccess : public ActorLinkConstDataAccess {
public:
    ActorConstDataAccess() = default;
    explicit ActorConstDataAccess(BaseProc* proc) : ActorLinkConstDataAccess(proc) {}

    bool acquireActor(const ActorLinkConstDataAccess& other);

    bool hasProc() const { return ActorLinkConstDataAccess::hasProc(); }

    /// Checks whether the acquired BaseProc is `proc`.
    bool hasProc(BaseProc* proc) const;

    /// Checks whether the acquired BaseProc and the BaseProcLink's actor are the same
    /// by comparing the IDs.
    bool hasProc(const BaseProcLink& link) const;

    template <typename T>
    bool isDerivedFrom() const {
        return sead::IsDerivedFrom<T>(mProc);
    }

    bool linkAcquire(BaseProcLink* link) const;
    bool linkAcquireImmediately(BaseProcLink* link) const;

    void debugLog(s32, const sead::SafeString& method_name) const;

    const sead::SafeString& getProfile() const;
    const sead::SafeString& getName() const;
    bool hasTag(const char* tag) const;
    bool hasTag(u32 tag) const;
    u32 getId() const;
    bool acquireConnectedCalcParent(ActorLinkConstDataAccess* accessor) const;
    bool acquireConnectedCalcChild(ActorLinkConstDataAccess* accessor) const;
    bool hasConnectedCalcParent() const;

    bool deleteLater(BaseProc::DeleteReason reason) const;
    bool fadeOutDelete(BaseProc::DeleteReason reason) const;
    bool sleep(BaseProc::SleepWakeReason reason) const;
    bool wakeUp(BaseProc::SleepWakeReason reason) const;

    bool isAttClientEnabled(const sead::SafeString& client) const;

private:
    u8 _10 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorConstDataAccess, 0x18);

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor);

}  // namespace ksys::act
