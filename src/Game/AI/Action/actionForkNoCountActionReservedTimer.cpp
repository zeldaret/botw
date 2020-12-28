#include "Game/AI/Action/actionForkNoCountActionReservedTimer.h"

namespace uking::action {

ForkNoCountActionReservedTimer::ForkNoCountActionReservedTimer(const InitArg& arg)
    : ForkTimer(arg) {}

ForkNoCountActionReservedTimer::~ForkNoCountActionReservedTimer() = default;

bool ForkNoCountActionReservedTimer::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void ForkNoCountActionReservedTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkNoCountActionReservedTimer::leave_() {
    ForkTimer::leave_();
}

void ForkNoCountActionReservedTimer::loadParams_() {
    ForkTimer::loadParams_();
    getAITreeVariable(&mIsNextActionReserved_a, "IsNextActionReserved");
}

void ForkNoCountActionReservedTimer::calc_() {
    ForkTimer::calc_();
}

}  // namespace uking::action
