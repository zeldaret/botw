#include "Game/AI/Action/actionForkNoCountActionReservedTimer.h"

namespace uking::action {

ForkNoCountActionReservedTimer::ForkNoCountActionReservedTimer(const InitArg& arg)
    : ForkTimer(arg) {}

ForkNoCountActionReservedTimer::~ForkNoCountActionReservedTimer() = default;

bool ForkNoCountActionReservedTimer::init_(sead::Heap* heap) {
    return ForkTimerBase::init_(heap);  // NOLINT(bugprone-parent-virtual-call)
}

void ForkNoCountActionReservedTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkNoCountActionReservedTimer::leave_() {
    ForkTimerBase::leave_();  // NOLINT(bugprone-parent-virtual-call)
}

void ForkNoCountActionReservedTimer::loadParams_() {
    ForkTimer::loadParams_();
    getAITreeVariable(&mIsNextActionReserved_a, "IsNextActionReserved");
}

void ForkNoCountActionReservedTimer::calc_() {
    ForkTimer::calc_();
}

}  // namespace uking::action
