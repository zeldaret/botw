#pragma once

#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class __attribute__((aligned(8))) PlacementGlobal {
    SEAD_SINGLETON_DISPOSER(PlacementGlobal);

    PlacementGlobal() = default;
    virtual ~PlacementGlobal();
    void init();
    void __auto();
    void prepareStageUnload();
    void incrementCountersAndUpdate();
    void incrementCounters();

    unsigned int frameCounter = 0;
    int frameCounter2 = 0;
    float vfrTimer = 0;
    int frameCounterB = 0;
    float vfrTimer2 = 0;
    int frameCounterB2 = 0;
};
KSYS_CHECK_SIZE_NX150(PlacementGlobal, 0x40);

}  // namespace ksys::map
