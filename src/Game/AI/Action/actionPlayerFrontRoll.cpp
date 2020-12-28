#include "Game/AI/Action/actionPlayerFrontRoll.h"

namespace uking::action {

PlayerFrontRoll::PlayerFrontRoll(const InitArg& arg) : PlayerAction(arg) {}

void PlayerFrontRoll::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerFrontRoll::leave_() {
    PlayerAction::leave_();
}

void PlayerFrontRoll::loadParams_() {
    getStaticParam(&mEnergyDec_s, "EnergyDec");
    getStaticParam(&mSpeedDecByAngle_s, "SpeedDecByAngle");
}

void PlayerFrontRoll::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
