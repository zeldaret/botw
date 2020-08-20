#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::act {

ActorLinkConstDataAccess::~ActorLinkConstDataAccess() {
    if (mAcquired && mProc)
        mProc->release();

    mAcquired = false;
    mProc = nullptr;
}

bool ActorLinkConstDataAccess::acquire(BaseProc* proc) {
    if (mProc) {
        if (mAcquired)
            mProc->release();

        mAcquired = false;
        mProc = nullptr;
    }

    if (proc)
        return proc->acquire(*this);
    return false;
}

bool ActorLinkConstDataAccess::hasProc(BaseProc* proc) const {
    return mProc == proc;
}

void ActorLinkConstDataAccess::debugLog(s32, const sead::SafeString&) {
    // Intentionally left empty.
}

}  // namespace ksys::act
