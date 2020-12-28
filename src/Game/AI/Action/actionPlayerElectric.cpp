#include "Game/AI/Action/actionPlayerElectric.h"

namespace uking::action {

PlayerElectric::PlayerElectric(const InitArg& arg) : PlayerAction(arg) {}

void PlayerElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerElectric::leave_() {
    PlayerAction::leave_();
}

void PlayerElectric::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerElectric::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
