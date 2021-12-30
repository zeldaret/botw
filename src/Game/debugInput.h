
#pragma once

#include <heap/seadDisposer.h>

class DebugInput {
    SEAD_SINGLETON_DISPOSER(DebugInput);

public:
    DebugInput() = default;
    virtual ~DebugInput() = default;

private:
    bool t1 = false;
    u32 t2 = 0;
};
