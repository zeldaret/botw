#include "Game/AI/AI/aiDynTgBreathAttackEnemyBattle.h"

namespace uking::ai {

DynTgBreathAttackEnemyBattle::DynTgBreathAttackEnemyBattle(const InitArg& arg)
    : BreathAttackEnemyBattle(arg) {}

DynTgBreathAttackEnemyBattle::~DynTgBreathAttackEnemyBattle() = default;

bool DynTgBreathAttackEnemyBattle::init_(sead::Heap* heap) {
    return BreathAttackEnemyBattle::init_(heap);
}

void DynTgBreathAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void DynTgBreathAttackEnemyBattle::leave_() {
    BreathAttackEnemyBattle::leave_();
}

void DynTgBreathAttackEnemyBattle::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
