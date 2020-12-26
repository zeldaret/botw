#include "Game/AI/Action/actionRideHorseAction.h"

namespace uking::action {

RideHorseAction::RideHorseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorseAction::~RideHorseAction() = default;

bool RideHorseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RideHorseAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void RideHorseAction::loadParams_() {
    getDynamicParam(&mHorse_d, "Horse");
}

void RideHorseAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
