
#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

class DebugInput {
    SEAD_SINGLETON_DISPOSER(DebugInput)

public:
    DebugInput() = default;
    virtual ~DebugInput() = default;
    void update();

private:
    sead::BitFlag8 mFlags = false;
    float mLastDelta = 0;
};

}  // namespace ksys
