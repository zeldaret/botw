#include "Game/AI/Action/actionPlayerClimbRest.h"

namespace uking::action {

PlayerClimbRest::PlayerClimbRest(const InitArg& arg) : PlayerAction(arg) {}

PlayerClimbRest::~PlayerClimbRest() = default;

void PlayerClimbRest::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerClimbRest::leave_() {
    PlayerAction::leave_();
}

void PlayerClimbRest::loadParams_() {
    getStaticParam(&mEnergyClimb_s, "EnergyClimb");
}

void PlayerClimbRest::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
