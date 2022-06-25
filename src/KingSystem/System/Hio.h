#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Hio final : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Hio)

    Hio() = default;
    ~Hio() = default;
};
KSYS_CHECK_SIZE_NX150(Hio, 0x28);

}  // namespace ksys
