#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// FIXME
class AwarenessInstance {
public:
    AwarenessInstance();
    virtual ~AwarenessInstance();

    void calcForEvent();
    void calc();
    void calc2();

    u8 _8[0x334 - 0x8];
    s8 _334;
    u32 _338;
};
KSYS_CHECK_SIZE_NX150(AwarenessInstance, 0x340);

}  // namespace ksys::act
