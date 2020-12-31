#include "Game/AI/AI/aiBackAttackEnemyBattle.h"

namespace uking::ai {

BackAttackEnemyBattle::BackAttackEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

BackAttackEnemyBattle::~BackAttackEnemyBattle() = default;

bool BackAttackEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void BackAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void BackAttackEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void BackAttackEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAttackAngle_s, "BackAttackAngle");
}

}  // namespace uking::ai
