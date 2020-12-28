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

void RideHorseAction::loadParams_() {
    getDynamicParam(&mHorse_d, "Horse");
}

}  // namespace uking::action
