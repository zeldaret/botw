#include "Game/Actor/Action/actionHorseRideSearch.h"

namespace uking::action {

HorseRideSearch::HorseRideSearch(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideSearch::~HorseRideSearch() = default;

bool HorseRideSearch::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideSearch::leave_() {
    HorseRideBase::leave_();
}

void HorseRideSearch::loadParams_() {
    HorseRideBase::loadParams_();
}

void HorseRideSearch::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
