#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys {

class DebugFinder {
    SEAD_SINGLETON_DISPOSER(DebugFinder)
    DebugFinder();
    virtual ~DebugFinder();

private:
    sead::FixedSafeString<0x40> unused_1;
    sead::FixedSafeString<0x100> unused_2;
    u32 unused_3 = 0;
};

}  // namespace ksys
