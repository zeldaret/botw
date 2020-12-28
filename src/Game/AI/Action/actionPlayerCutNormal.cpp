#include "Game/AI/Action/actionPlayerCutNormal.h"

namespace uking::action {

PlayerCutNormal::PlayerCutNormal(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutNormal::leave_() {
    PlayerAction::leave_();
}

void PlayerCutNormal::loadParams_() {
    getStaticParam(&mAttackRatioNSwordS1_s, "AttackRatioNSwordS1");
    getStaticParam(&mAttackRatioNSwordS2_s, "AttackRatioNSwordS2");
    getStaticParam(&mAttackRatioNSwordS3_s, "AttackRatioNSwordS3");
    getStaticParam(&mAttackRatioLSwordS1_s, "AttackRatioLSwordS1");
    getStaticParam(&mAttackRatioLSwordS2_s, "AttackRatioLSwordS2");
    getStaticParam(&mAttackRatioLSwordS3_s, "AttackRatioLSwordS3");
    getStaticParam(&mAttackRatioSpearS1_s, "AttackRatioSpearS1");
    getStaticParam(&mAttackRatioSpearS2_s, "AttackRatioSpearS2");
    getStaticParam(&mAttackRatioSpearS3_s, "AttackRatioSpearS3");
    getStaticParam(&mAttackRatioSpearS4_s, "AttackRatioSpearS4");
    getStaticParam(&mAttackRatioSpearS5_s, "AttackRatioSpearS5");
    getStaticParam(&mSwordSearchFrame_s, "SwordSearchFrame");
    getStaticParam(&mSwordSearchAngle_s, "SwordSearchAngle");
}

void PlayerCutNormal::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
