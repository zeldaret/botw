#pragma once

#include <prim/seadSafeString.h>
#include <heap/seadDisposer.h>
#include <container/seadOffsetList.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Patrol {
    SEAD_SINGLETON_DISPOSER(Patrol)

    Patrol();
    ~Patrol() = default;

public:
    //FIXME
    bool mField0;
    bool mHasAutoPlay;
    bool mHasAutoGenPatroller;
    bool mLoadStaticPhysUnstableMapUnit;
    sead::FixedSafeString<0x100> mBuildURL;
    //FIXME: Unknown template type
    sead::OffsetList<u32> mList;
};
KSYS_CHECK_SIZE_NX150(Patrol, 0x158);

}  // namespace ksys