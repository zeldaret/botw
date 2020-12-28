#include "Game/AI/Action/actionPlayerCutTurnLSword.h"

namespace uking::action {

PlayerCutTurnLSword::PlayerCutTurnLSword(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutTurnLSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutTurnLSword::leave_() {
    PlayerAction::leave_();
}

void PlayerCutTurnLSword::loadParams_() {
    getStaticParam(&mEnergyMove_s, "EnergyMove");
    getStaticParam(&mEnergyLastAttack_s, "EnergyLastAttack");
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
    getStaticParam(&mAccSpeed_s, "AccSpeed");
    getStaticParam(&mDecSpeed_s, "DecSpeed");
    getStaticParam(&mSpAttackRadiusMin_s, "SpAttackRadiusMin");
    getStaticParam(&mSpAttackRadiusMax_s, "SpAttackRadiusMax");
    getStaticParam(&mSpAttackRadiusAdd_s, "SpAttackRadiusAdd");
    getStaticParam(&mSpAttackCheckUnderDist_s, "SpAttackCheckUnderDist");
    getStaticParam(&mSpLargeAttackRadius_s, "SpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
    getStaticParam(&mEnergyChargeStart_s, "EnergyChargeStart");
}

void PlayerCutTurnLSword::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
