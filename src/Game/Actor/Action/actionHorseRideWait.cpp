#include "Game/Actor/Action/actionHorseRideWait.h"

namespace uking::action {

HorseRideWait::HorseRideWait(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideWait::~HorseRideWait() = default;

bool HorseRideWait::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideWait::leave_() {
    HorseRideBase::leave_();
}

void HorseRideWait::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void HorseRideWait::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
