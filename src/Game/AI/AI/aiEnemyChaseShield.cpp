#include "Game/AI/AI/aiEnemyChaseShield.h"

namespace uking::ai {

EnemyChaseShield::EnemyChaseShield(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChaseShield::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChaseShield::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChaseShield::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mTurnAng_s, "TurnAng");
    getStaticParam(&mShieldReachDist_s, "ShieldReachDist");
}

}  // namespace uking::ai
