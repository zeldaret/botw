#include "Game/AI/Action/actionPlayerCutTurn.h"

namespace uking::action {

PlayerCutTurn::PlayerCutTurn(const InitArg& arg) : PlayerAction(arg) {}

PlayerCutTurn::~PlayerCutTurn() = default;

void PlayerCutTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutTurn::leave_() {
    PlayerAction::leave_();
}

void PlayerCutTurn::loadParams_() {
    getStaticParam(&mAttackRatioNSword_s, "AttackRatioNSword");
    getStaticParam(&mAttackRatioLSword_s, "AttackRatioLSword");
    getStaticParam(&mAttackRatioSpear_s, "AttackRatioSpear");
    getStaticParam(&mEnergyAttack_s, "EnergyAttack");
    getStaticParam(&mEnergyChargeStart_s, "EnergyChargeStart");
    getStaticParam(&mRangeDiam_s, "RangeDiam");
    getStaticParam(&mRangeDiamAdd_s, "RangeDiamAdd");
    getStaticParam(&mMaxChargeLvNSword_s, "MaxChargeLvNSword");
    getStaticParam(&mRangeDiamAddNSword_s, "RangeDiamAddNSword");
}

void PlayerCutTurn::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
