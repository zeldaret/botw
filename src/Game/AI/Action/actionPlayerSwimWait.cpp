#include "Game/AI/Action/actionPlayerSwimWait.h"

namespace uking::action {

PlayerSwimWait::PlayerSwimWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimWait::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimWait::loadParams_() {
    getStaticParam(&mEnergyWait_s, "EnergyWait");
    getStaticParam(&mDecSpeedRate_s, "DecSpeedRate");
}

void PlayerSwimWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
