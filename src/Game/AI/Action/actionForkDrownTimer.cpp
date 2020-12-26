#include "Game/AI/Action/actionForkDrownTimer.h"

namespace uking::action {

ForkDrownTimer::ForkDrownTimer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDrownTimer::~ForkDrownTimer() = default;

bool ForkDrownTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDrownTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkDrownTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDrownTimer::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
}

void ForkDrownTimer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
