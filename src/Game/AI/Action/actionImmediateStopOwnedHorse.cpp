#include "Game/AI/Action/actionImmediateStopOwnedHorse.h"

namespace uking::action {

ImmediateStopOwnedHorse::ImmediateStopOwnedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ImmediateStopOwnedHorse::~ImmediateStopOwnedHorse() = default;

bool ImmediateStopOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ImmediateStopOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ImmediateStopOwnedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ImmediateStopOwnedHorse::loadParams_() {
    getDynamicParam(&mResetChargeNum_d, "ResetChargeNum");
}

void ImmediateStopOwnedHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
