#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorDebug {
    SEAD_SINGLETON_DISPOSER(ActorDebug)
    ActorDebug();
    virtual ~ActorDebug();

public:
    enum class Flag {
        _10000000 = 0x10000000,
        _20000000 = 0x20000000,
    };

    struct HashUnused {
        u32 hash = 0;
        u32 b;
    };

    const char* getNullStr(HashUnused* u);
    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }

    void* _28;
    sead::TypedBitFlag<Flag> mFlags;
    u8 TEMP1[0x2DC];
    f32 mDispDistanceMultiplier;
    u8 TEMP2[0x114];
};
KSYS_CHECK_SIZE_NX150(ActorDebug, 0x428);

}  // namespace ksys::act
