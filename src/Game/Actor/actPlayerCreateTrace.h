
#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking::act {

// This is used in CreatePlayerEquipActorMgr and CreatePlayerTrashActorMgr
// and nowhere else. It's completely stubbed out, so the implementation is purely by usage-based
// guess

// This exists because makeScope doesn't match
// when made an inlined function in PlayerCreateTracer
// i.e. tracer.trace()->makeScope() matches but not tracer.makeScope()
class PlayerCreateTrace;

class PlayerCreateTraceScope {
public:
    PlayerCreateTraceScope(PlayerCreateTrace* trace, const sead::SafeString& name,
                           const sead::SafeString& caller, s32 level);
    virtual ~PlayerCreateTraceScope();

private:
    PlayerCreateTrace* mTrace = nullptr;
};
KSYS_CHECK_SIZE_NX150(PlayerCreateTraceScope, 0x10);

class PlayerCreateTrace {
public:
    PlayerCreateTraceScope makeScope(const sead::SafeString& name, const sead::SafeString& caller,
                                     s32 level) {
        return {this, name, caller, level};
    }
    static PlayerCreateTrace* make(const sead::SafeString& name, s32 level);
};

class PlayerCreateTracer {
public:
    void init(const sead::SafeString& name) { mTrace = PlayerCreateTrace::make(name, 0); }
    void finish();
    PlayerCreateTrace* trace() { return mTrace; }

private:
    PlayerCreateTrace* mTrace = nullptr;
};
KSYS_CHECK_SIZE_NX150(PlayerCreateTracer, 0x8);

}  // namespace uking::act
