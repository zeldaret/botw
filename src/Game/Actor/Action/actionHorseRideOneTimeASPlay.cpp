#include "Game/Actor/Action/actionHorseRideOneTimeASPlay.h"

namespace uking::action {

HorseRideOneTimeASPlay::HorseRideOneTimeASPlay(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideOneTimeASPlay::~HorseRideOneTimeASPlay() = default;

bool HorseRideOneTimeASPlay::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideOneTimeASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideOneTimeASPlay::leave_() {
    HorseRideBase::leave_();
}

void HorseRideOneTimeASPlay::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mIgnoreSameAS_s, "IgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideOneTimeASPlay::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
