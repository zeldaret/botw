#pragma once

#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class SystemTimers {
    SEAD_SINGLETON_DISPOSER(SystemTimers);

    SystemTimers() = default;
    virtual ~SystemTimers();

public:
    void init();
    void init2();
    void prepareStageUnload();
    void incrementCountersAndUpdate();
    void incrementCounters();

    unsigned int mFrameCounter = 0;
    int mFrameCounter2 = 0;
    float mVfrTimer = 0;
    int mFrameCounterB = 0;
    float mVfrTimer2 = 0;
    int mFrameCounterB2 = 0;
};
KSYS_CHECK_SIZE_NX150(SystemTimers, 0x40);

}  // namespace ksys
