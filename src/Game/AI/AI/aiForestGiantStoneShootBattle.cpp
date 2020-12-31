#include "Game/AI/AI/aiForestGiantStoneShootBattle.h"

namespace uking::ai {

ForestGiantStoneShootBattle::ForestGiantStoneShootBattle(const InitArg& arg)
    : StoneShootEnemyBattle(arg) {}

ForestGiantStoneShootBattle::~ForestGiantStoneShootBattle() = default;

bool ForestGiantStoneShootBattle::init_(sead::Heap* heap) {
    return StoneShootEnemyBattle::init_(heap);
}

void ForestGiantStoneShootBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    StoneShootEnemyBattle::enter_(params);
}

void ForestGiantStoneShootBattle::leave_() {
    StoneShootEnemyBattle::leave_();
}

void ForestGiantStoneShootBattle::loadParams_() {
    StoneShootEnemyBattle::loadParams_();
    getStaticParam(&mShootItemRate1_s, "ShootItemRate1");
    getStaticParam(&mForceAttackArea_s, "ForceAttackArea");
    getStaticParam(&mShootItemName2_s, "ShootItemName2");
}

}  // namespace uking::ai
