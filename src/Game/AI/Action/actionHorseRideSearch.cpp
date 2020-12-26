#include "Game/AI/Action/actionHorseRideSearch.h"

namespace uking::action {

HorseRideSearch::HorseRideSearch(const InitArg& arg) : HorseRide(arg) {}

HorseRideSearch::~HorseRideSearch() = default;

bool HorseRideSearch::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideSearch::leave_() {
    HorseRide::leave_();
}

void HorseRideSearch::loadParams_() {
    HorseRide::loadParams_();
}

void HorseRideSearch::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
