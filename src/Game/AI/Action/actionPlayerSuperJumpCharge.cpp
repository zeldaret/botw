#include "Game/AI/Action/actionPlayerSuperJumpCharge.h"

namespace uking::action {

PlayerSuperJumpCharge::PlayerSuperJumpCharge(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJumpCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperJumpCharge::leave_() {
    PlayerAction::leave_();
}

void PlayerSuperJumpCharge::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
}

void PlayerSuperJumpCharge::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
