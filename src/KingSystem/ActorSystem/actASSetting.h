#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

// FIXME: very incomplete
class ASSetting {
    SEAD_SINGLETON_DISPOSER(ASSetting)
    ASSetting() = default;
};

}  // namespace ksys::act
