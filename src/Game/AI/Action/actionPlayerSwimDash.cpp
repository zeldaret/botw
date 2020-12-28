#include "Game/AI/Action/actionPlayerSwimDash.h"

namespace uking::action {

PlayerSwimDash::PlayerSwimDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimDash::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimDash::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

void PlayerSwimDash::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
