#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Terminal : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Terminal)

    Terminal() = default;
    virtual ~Terminal() = default;

public:
    u32 mFlag = 0;
};
KSYS_CHECK_SIZE_NX150(Terminal, 0x30);

}  // namespace ksys
