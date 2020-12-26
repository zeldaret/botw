#include "Game/AI/Action/actionRideHorseForEventAction.h"

namespace uking::action {

RideHorseForEventAction::RideHorseForEventAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorseForEventAction::~RideHorseForEventAction() = default;

bool RideHorseForEventAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorseForEventAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RideHorseForEventAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void RideHorseForEventAction::loadParams_() {}

void RideHorseForEventAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
