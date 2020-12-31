#include "Game/AI/AI/aiAnimalBattleAggressive.h"

namespace uking::ai {

AnimalBattleAggressive::AnimalBattleAggressive(const InitArg& arg) : EnemyBattle(arg) {}

AnimalBattleAggressive::~AnimalBattleAggressive() = default;

bool AnimalBattleAggressive::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AnimalBattleAggressive::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void AnimalBattleAggressive::leave_() {
    EnemyBattle::leave_();
}

void AnimalBattleAggressive::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mForceAttackTimer_s, "ForceAttackTimer");
    getStaticParam(&mCounterAttackTimer_s, "CounterAttackTimer");
    getStaticParam(&mForceAttackRange_s, "ForceAttackRange");
    getStaticParam(&mCounterAttackRange_s, "CounterAttackRange");
    getAITreeVariable(&mAnimalEnableCounterFlag_a, "AnimalEnableCounterFlag");
}

}  // namespace uking::ai
