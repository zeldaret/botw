#include "Game/AI/Action/actionHorseRideOneTimeViewASPlay.h"

namespace uking::action {

HorseRideOneTimeViewASPlay::HorseRideOneTimeViewASPlay(const InitArg& arg)
    : HorseRideViewWait(arg) {}

HorseRideOneTimeViewASPlay::~HorseRideOneTimeViewASPlay() = default;

bool HorseRideOneTimeViewASPlay::init_(sead::Heap* heap) {
    return HorseRideViewWait::init_(heap);
}

void HorseRideOneTimeViewASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideViewWait::enter_(params);
}

void HorseRideOneTimeViewASPlay::leave_() {
    HorseRideViewWait::leave_();
}

void HorseRideOneTimeViewASPlay::loadParams_() {
    HorseRideViewWait::loadParams_();
}

void HorseRideOneTimeViewASPlay::calc_() {
    HorseRideViewWait::calc_();
}

}  // namespace uking::action
