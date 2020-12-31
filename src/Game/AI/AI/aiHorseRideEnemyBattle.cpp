#include "Game/AI/AI/aiHorseRideEnemyBattle.h"

namespace uking::ai {

HorseRideEnemyBattle::HorseRideEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

HorseRideEnemyBattle::~HorseRideEnemyBattle() = default;

bool HorseRideEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void HorseRideEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void HorseRideEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void HorseRideEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackRadius_s, "AttackRadius");
}

}  // namespace uking::ai
