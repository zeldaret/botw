#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::act {

// NON_MATCHING: Equivalent but branches are off.
bool BaseProcUnit::setProc(BaseProc* proc) {
    bool ret;
    static constexpr const char* sStateNames[] = {"Init", "Calc", "Sleep", "Delete"};

    auto lock = sead::makeScopedLock(mCS);
    if (mProc)
        mProc = nullptr;

    if (mHandle == &BaseProcHandle::sDummyHandle)
        return false;

    if (mHandle) {
        if (mFlags != 1) {
            sead::FixedSafeString<64> message;

            if (proc)
                message.format("%s, %d, %d, %s, ( %p:%p )", proc->getName().cstr(), mFlags,
                               proc->isInitialized(), sStateNames[u8(proc->getState())], this,
                               mHandle.load());
            else
                message.format("なし, %d, ?, ?, ( %p:%p )", mFlags, this, mHandle.load());

            util::PrintDebug(message);
        }
        mProc = proc;
        mFlags = 2;
        ret = true;
    } else {
        sead::FixedSafeString<64> message;

        if (proc)
            message.format("%s, %d, %d, %s, ( %p:%p )", proc->getName().cstr(), mFlags,
                           proc->isInitialized(), sStateNames[u8(proc->getState())], this,
                           mHandle.load());
        else
            message.format("なし, %d, ?, ?, ( %p:%p )", mFlags, this, mHandle.load());

        util::PrintDebug(message);
        ret = false;
    }
    return ret;
}

bool BaseProcUnit::isParentHandleDefault() const {
    return mHandle == &BaseProcHandle::sDummyHandle;
}

}  // namespace ksys::act
