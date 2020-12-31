#include "Game/AI/AI/aiStoneShootEnemyBattle.h"

namespace uking::ai {

StoneShootEnemyBattle::StoneShootEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

StoneShootEnemyBattle::~StoneShootEnemyBattle() = default;

bool StoneShootEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void StoneShootEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void StoneShootEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void StoneShootEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mShootItemName_s, "ShootItemName");
}

}  // namespace uking::ai
