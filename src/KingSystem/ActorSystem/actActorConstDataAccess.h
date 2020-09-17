#pragma once

#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorConstDataAccess : public ActorLinkConstDataAccess {
public:
    ActorConstDataAccess() = default;

    bool acquireActor(const ActorLinkConstDataAccess& other);

    bool hasProc() const { return ActorLinkConstDataAccess::hasProc(); }

    /// Checks whether the acquired BaseProc is `proc`.
    bool hasProc(BaseProc* proc) const;

    /// Checks whether the acquired BaseProc and the BaseProcLink's actor are the same
    /// by comparing the IDs.
    bool hasProc(const BaseProcLink& link) const;

    bool linkAcquire(BaseProcLink* link) const;
    bool linkAcquireImmediately(BaseProcLink* link) const;

    void debugLog(s32, const sead::SafeString& method_name) const;

    const sead::SafeString& getProfile() const;
    const sead::SafeString& getName() const;
    bool hasTag(const sead::SafeString& tag) const;
    bool hasTag(Tag tag) const;
    u32 getId() const;
    bool acquireConnectedCalcParent(ActorLinkConstDataAccess* accessor) const;
    bool acquireConnectedCalcChild(ActorLinkConstDataAccess* accessor) const;
    bool hasConnectedCalcParent() const;

private:
    u8 _10 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorConstDataAccess, 0x18);

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor);

}  // namespace ksys::act
