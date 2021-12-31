#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadTypedBitFlag.h>

namespace ksys {

class DebugInput {
    SEAD_SINGLETON_DISPOSER(DebugInput)

public:
    DebugInput() = default;
    virtual ~DebugInput() = default;
    void update();

private:
    sead::BitFlag8 mFlags;
    float mLastDelta = 0;
};

}  // namespace ksys
