#include "Game/AI/Action/actionHorseRideViewWait.h"

namespace uking::action {

HorseRideViewWait::HorseRideViewWait(const InitArg& arg) : HorseRide(arg) {}

HorseRideViewWait::~HorseRideViewWait() = default;

bool HorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideViewWait::leave_() {
    HorseRide::leave_();
}

void HorseRideViewWait::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideViewWait::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
