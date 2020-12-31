#include "Game/AI/AI/aiForestGiantBattle.h"

namespace uking::ai {

ForestGiantBattle::ForestGiantBattle(const InitArg& arg) : EnemyBattle(arg) {}

ForestGiantBattle::~ForestGiantBattle() = default;

bool ForestGiantBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void ForestGiantBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void ForestGiantBattle::leave_() {
    EnemyBattle::leave_();
}

void ForestGiantBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mForceAttackArea_s, "ForceAttackArea");
}

}  // namespace uking::ai
