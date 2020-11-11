#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

class OverlayArena;

namespace util {
class Event;
}

namespace res {

class ArchiveWork {
public:
    struct InitArg {
        bool arena_set_flag_8;
        u32 arena_size;
        sead::Heap* heap;
        sead::Heap* arena_heap;
        sead::Heap* arena_heap2;
        sead::SafeString name;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x30);

    ArchiveWork();
    ~ArchiveWork();

    bool init(const InitArg& arg);
    u32 getHeapSize() const;
    OverlayArena* getArena() const;

    bool waitForEvent(u32 milliseconds = 0);
    void setEvent();

private:
    util::Event* mEvent = nullptr;
    OverlayArena* mArena = nullptr;
};
KSYS_CHECK_SIZE_NX150(ArchiveWork, 0x10);

}  // namespace res

}  // namespace ksys
