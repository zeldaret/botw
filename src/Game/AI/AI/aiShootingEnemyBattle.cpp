#include "Game/AI/AI/aiShootingEnemyBattle.h"

namespace uking::ai {

ShootingEnemyBattle::ShootingEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

ShootingEnemyBattle::~ShootingEnemyBattle() = default;

bool ShootingEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void ShootingEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void ShootingEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void ShootingEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mOutScreenAttackNum_s, "OutScreenAttackNum");
    getStaticParam(&mOutScreenDist_s, "OutScreenDist");
    getStaticParam(&mOutScrnAtkOffset_s, "OutScrnAtkOffset");
    getStaticParam(&mOutScrnAtkOffsetY_s, "OutScrnAtkOffsetY");
}

}  // namespace uking::ai
