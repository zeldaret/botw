#include "Game/AI/Action/actionForkTimer.h"

namespace uking::action {

ForkTimer::ForkTimer(const InitArg& arg) : ForkTimerBase(arg) {}

ForkTimer::~ForkTimer() = default;

void ForkTimer::loadParams_() {
    ForkTimerBase::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
}

}  // namespace uking::action
