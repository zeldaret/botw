#include "Game/AI/Action/actionPlayerWeaponThrow.h"

namespace uking::action {

PlayerWeaponThrow::PlayerWeaponThrow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWeaponThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWeaponThrow::leave_() {
    PlayerAction::leave_();
}

void PlayerWeaponThrow::loadParams_() {
    getStaticParam(&mThrowSpeedY_s, "ThrowSpeedY");
    getStaticParam(&mThrowSpeedF_s, "ThrowSpeedF");
    getStaticParam(&mSquatThrowSpeedF_s, "SquatThrowSpeedF");
}

void PlayerWeaponThrow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
