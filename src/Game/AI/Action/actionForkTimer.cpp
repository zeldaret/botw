#include "Game/AI/Action/actionForkTimer.h"

namespace uking::action {

ForkTimer::ForkTimer(const InitArg& arg) : ForkTimerBase(arg) {}

ForkTimer::~ForkTimer() = default;

bool ForkTimer::init_(sead::Heap* heap) {
    return ForkTimerBase::init_(heap);
}

void ForkTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimerBase::enter_(params);
}

void ForkTimer::leave_() {
    ForkTimerBase::leave_();
}

void ForkTimer::loadParams_() {
    ForkTimerBase::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
}

void ForkTimer::calc_() {
    ForkTimerBase::calc_();
}

}  // namespace uking::action
