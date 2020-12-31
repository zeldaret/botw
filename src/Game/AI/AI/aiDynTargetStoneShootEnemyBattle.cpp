#include "Game/AI/AI/aiDynTargetStoneShootEnemyBattle.h"

namespace uking::ai {

DynTargetStoneShootEnemyBattle::DynTargetStoneShootEnemyBattle(const InitArg& arg)
    : StoneShootEnemyBattle(arg) {}

DynTargetStoneShootEnemyBattle::~DynTargetStoneShootEnemyBattle() = default;

bool DynTargetStoneShootEnemyBattle::init_(sead::Heap* heap) {
    return StoneShootEnemyBattle::init_(heap);
}

void DynTargetStoneShootEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    StoneShootEnemyBattle::enter_(params);
}

void DynTargetStoneShootEnemyBattle::leave_() {
    StoneShootEnemyBattle::leave_();
}

void DynTargetStoneShootEnemyBattle::loadParams_() {
    StoneShootEnemyBattle::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
