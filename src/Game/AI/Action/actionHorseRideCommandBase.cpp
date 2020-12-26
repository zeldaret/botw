#include "Game/AI/Action/actionHorseRideCommandBase.h"

namespace uking::action {

HorseRideCommandBase::HorseRideCommandBase(const InitArg& arg) : HorseRideLookWait(arg) {}

HorseRideCommandBase::~HorseRideCommandBase() = default;

bool HorseRideCommandBase::init_(sead::Heap* heap) {
    return HorseRideLookWait::init_(heap);
}

void HorseRideCommandBase::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideLookWait::enter_(params);
}

void HorseRideCommandBase::leave_() {
    HorseRideLookWait::leave_();
}

void HorseRideCommandBase::loadParams_() {
    HorseRideLookWait::loadParams_();
}

void HorseRideCommandBase::calc_() {
    HorseRideLookWait::calc_();
}

}  // namespace uking::action
