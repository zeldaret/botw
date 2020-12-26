#include "Game/AI/Action/actionTimeredHorseRideViewWait.h"

namespace uking::action {

TimeredHorseRideViewWait::TimeredHorseRideViewWait(const InitArg& arg) : HorseRideViewWait(arg) {}

TimeredHorseRideViewWait::~TimeredHorseRideViewWait() = default;

bool TimeredHorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRideViewWait::init_(heap);
}

void TimeredHorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideViewWait::enter_(params);
}

void TimeredHorseRideViewWait::leave_() {
    HorseRideViewWait::leave_();
}

void TimeredHorseRideViewWait::loadParams_() {
    HorseRideViewWait::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void TimeredHorseRideViewWait::calc_() {
    HorseRideViewWait::calc_();
}

}  // namespace uking::action
