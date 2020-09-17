#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

bool ActorConstDataAccess::acquireActor(const ActorLinkConstDataAccess& other) {
    return acquire(getProcIfActor(other.mProc));
}

bool ActorConstDataAccess::hasProc(BaseProc* proc) const {
    return mProc == proc;
}

bool ActorConstDataAccess::hasProc(const BaseProcLink& link) const {
    return link.hasProcById(getProcIfActor(mProc));
}

bool ActorConstDataAccess::linkAcquire(BaseProcLink* link) const {
    auto* proc = getProcIfActor(mProc);
    if (proc)
        return link->acquire(proc, false);

    link->reset();
    return false;
}

bool ActorConstDataAccess::linkAcquireImmediately(BaseProcLink* link) const {
    auto* proc = getProcIfActor(mProc);
    if (proc)
        return link->acquire(proc, true);

    link->reset();
    return false;
}

void ActorConstDataAccess::debugLog(s32, const sead::SafeString&) const {
    // Intentionally left empty.
}

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor) {
    return link->getProcInContext([accessor](BaseProc* proc, bool valid) {
        if (!proc) {
            if (!valid)
                accessor->acquire(nullptr);
            return false;
        }
        return accessor->acquire(sead::DynamicCast<Actor>(proc));
    });
}

}  // namespace ksys::act
