#include "Game/AI/AI/aiGuardianMiniFinalBattle.h"

namespace uking::ai {

GuardianMiniFinalBattle::GuardianMiniFinalBattle(const InitArg& arg) : EnemyBattle(arg) {}

GuardianMiniFinalBattle::~GuardianMiniFinalBattle() = default;

void GuardianMiniFinalBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void GuardianMiniFinalBattle::leave_() {
    EnemyBattle::leave_();
}

void GuardianMiniFinalBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mAttackHitNum_s, "AttackHitNum");
    getStaticParam(&mIsPreAttackMove_s, "IsPreAttackMove");
    getStaticParam(&mRotNeckRate_s, "RotNeckRate");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

}  // namespace uking::ai
