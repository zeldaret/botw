#include "Game/AI/Action/actionHorseRideWait.h"

namespace uking::action {

HorseRideWait::HorseRideWait(const InitArg& arg) : HorseRide(arg) {}

HorseRideWait::~HorseRideWait() = default;

bool HorseRideWait::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideWait::leave_() {
    HorseRide::leave_();
}

void HorseRideWait::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void HorseRideWait::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
