#include "Game/AI/Action/actionPlayerGuardJust.h"

namespace uking::action {

PlayerGuardJust::PlayerGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardJust::leave_() {
    PlayerAction::leave_();
}

void PlayerGuardJust::loadParams_() {
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

void PlayerGuardJust::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
