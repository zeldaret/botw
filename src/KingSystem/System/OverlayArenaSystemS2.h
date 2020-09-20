#pragma once

#include <basis/seadTypes.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class OverlayArenaSystemS1;
class SystemPauseMgr;

// FIXME: incomplete
class OverlayArenaSystemS2 {
public:
    struct InitArg {
        OverlayArenaSystemS1* s1;
        SystemPauseMgr* system_pause_mgr;
    };

    OverlayArenaSystemS2();

    void init(const InitArg& arg);

private:
    u32 _0 = 0;
    sead::Delegate1<OverlayArenaSystemS2, void*> mDelegate;
    u32 _28 = 1;
    void* _30 = nullptr;
    void* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(OverlayArenaSystemS2, 0x40);

}  // namespace ksys
