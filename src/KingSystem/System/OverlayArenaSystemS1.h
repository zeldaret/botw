#pragma once

#include "KingSystem/Utils/Types.h"

namespace ksys {

// FIXME: incomplete
// Unknown struct seen in OverlayArenaSystem.
class OverlayArenaSystemS1 final {
public:
    OverlayArenaSystemS1();
    virtual ~OverlayArenaSystemS1();

    // TODO: figure out if this is the same interface as SystemPauseMgr.
    // Both have the exact same number of virtual functions and some of the functions
    // look somewhat similar (suspending threads, looping while waiting for their status to change).

    virtual void init();
    // Resume resource compaction
    virtual void m3();
    virtual void m4();
    // Resume resource compaction + EventMgr
    virtual void m5();
    // Stop threads, clear cache, etc.
    virtual void m6();
    virtual bool m7();
    virtual void m8();
    virtual void m9();
    // Does nothing
    virtual void m10();
    virtual bool m11();
    virtual void m12();
    virtual void m13();
    // Does nothing
    virtual void m14();
};
KSYS_CHECK_SIZE_NX150(OverlayArenaSystemS1, 0x8);

}  // namespace ksys
