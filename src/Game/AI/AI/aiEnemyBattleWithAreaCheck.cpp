#include "Game/AI/AI/aiEnemyBattleWithAreaCheck.h"

namespace uking::ai {

EnemyBattleWithAreaCheck::EnemyBattleWithAreaCheck(const InitArg& arg) : EnemyBattle(arg) {}

EnemyBattleWithAreaCheck::~EnemyBattleWithAreaCheck() = default;

bool EnemyBattleWithAreaCheck::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void EnemyBattleWithAreaCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyBattleWithAreaCheck::leave_() {
    EnemyBattle::leave_();
}

void EnemyBattleWithAreaCheck::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mAttackFar_s, "AttackFar");
}

}  // namespace uking::ai
