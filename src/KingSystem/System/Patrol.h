#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Patrol {
    SEAD_SINGLETON_DISPOSER(Patrol)

public:
    Patrol() = default;
    ~Patrol() = default;

    u8 _0[0x3 - 0x0];
    bool mLoadStaticPhysUnstableMapUnit;
    sead::FixedSafeString<0x100> mBuildURL;
    sead::ListNode _140;
    u32 _150;
    u32 _154;
};
KSYS_CHECK_SIZE_NX150(Patrol, 0x158);
}  // namespace ksys
