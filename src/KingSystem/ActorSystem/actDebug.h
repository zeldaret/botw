#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorDebug {
    SEAD_SINGLETON_DISPOSER(ActorDebug)
public:
    struct HashUnused {
        u32 hash = 0;
        u32 b;
    };

    const char* getNullStr(HashUnused* u);

    u8 TEMP1[0x2F0];
    f32 mDispDistanceMultiplier;
    u8 TEMP2[0x114];
};
KSYS_CHECK_SIZE_NX150(ActorDebug, 0x428);

}  // namespace ksys::act
