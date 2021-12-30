
#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

class DebugInput {
    SEAD_SINGLETON_DISPOSER(DebugInput)

public:
    DebugInput() = default;
    virtual ~DebugInput() = default;

private:
    bool _8 = false;
    u32  _c = 0;
};

}  // namespace ksys
