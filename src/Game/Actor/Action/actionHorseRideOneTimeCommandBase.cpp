#include "Game/Actor/Action/actionHorseRideOneTimeCommandBase.h"

namespace uking::action {

HorseRideOneTimeCommandBase::HorseRideOneTimeCommandBase(const InitArg& arg)
    : HorseRideLookWait(arg) {}

HorseRideOneTimeCommandBase::~HorseRideOneTimeCommandBase() = default;

bool HorseRideOneTimeCommandBase::init_(sead::Heap* heap) {
    return HorseRideLookWait::init_(heap);
}

void HorseRideOneTimeCommandBase::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideLookWait::enter_(params);
}

void HorseRideOneTimeCommandBase::leave_() {
    HorseRideLookWait::leave_();
}

void HorseRideOneTimeCommandBase::loadParams_() {
    HorseRideLookWait::loadParams_();
}

void HorseRideOneTimeCommandBase::calc_() {
    HorseRideLookWait::calc_();
}

}  // namespace uking::action
