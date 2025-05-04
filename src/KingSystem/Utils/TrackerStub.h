#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

// Used in CreatePlayerEquipActorMgr and CreatePlayerTrashActorMgr
class TrackerStub {
public:
    void destroy();

private:
    u64 _ = 0;
};
KSYS_CHECK_SIZE_NX150(TrackerStub, 0x8);

TrackerStub makeTracker(const sead::SafeString& name, u32 x);

class TrackerStubScope {
public:
    TrackerStubScope(TrackerStub tracker, const sead::SafeString& name,
                     const sead::SafeString& caller, s32 level);
    virtual ~TrackerStubScope();

private:
    TrackerStub mTracker;
};
KSYS_CHECK_SIZE_NX150(TrackerStubScope, 0x10);

}  // namespace ksys::util
