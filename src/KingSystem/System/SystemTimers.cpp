#include "KingSystem/System/SystemTimers.h"

#include "KingSystem/System/VFR.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(SystemTimers)

SystemTimers::~SystemTimers() = default;

void SystemTimers::init() {
    mVfrTimer = 0;
    mFrameCounterB = 0;
    mVfrTimer2 = 0;
    mFrameCounterB2 = 0;
    mFrameCounter = 0;
    mFrameCounter2 = 0;
}

void SystemTimers::init2() {
    init();
}

void SystemTimers::prepareStageUnload() {}

void SystemTimers::incrementCountersAndUpdate() {
    mFrameCounter++;
    mFrameCounter2++;
    f32 deltaTime = VFR::instance()->getDeltaTime();
    mVfrTimer += deltaTime;

    while (mVfrTimer >= 1) {
        mFrameCounterB++;
        mVfrTimer--;
    }

    mVfrTimer2 += deltaTime;
    while (mVfrTimer2 >= 1) {
        mFrameCounterB2++;
        mVfrTimer2--;
    }
}

void SystemTimers::incrementCounters() {
    mFrameCounter++;
    mFrameCounterB++;
}

}  // namespace ksys
