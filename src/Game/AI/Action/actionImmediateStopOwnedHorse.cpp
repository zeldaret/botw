#include "Game/AI/Action/actionImmediateStopOwnedHorse.h"

namespace uking::action {

ImmediateStopOwnedHorse::ImmediateStopOwnedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ImmediateStopOwnedHorse::~ImmediateStopOwnedHorse() = default;

bool ImmediateStopOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ImmediateStopOwnedHorse::loadParams_() {
    getDynamicParam(&mResetChargeNum_d, "ResetChargeNum");
}

}  // namespace uking::action
