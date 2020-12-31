#include "Game/AI/AI/aiForestGiantBattleMove.h"

namespace uking::ai {

ForestGiantBattleMove::ForestGiantBattleMove(const InitArg& arg) : WaitNearTarget(arg) {}

ForestGiantBattleMove::~ForestGiantBattleMove() = default;

bool ForestGiantBattleMove::init_(sead::Heap* heap) {
    return WaitNearTarget::init_(heap);
}

void ForestGiantBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitNearTarget::enter_(params);
}

void ForestGiantBattleMove::leave_() {
    WaitNearTarget::leave_();
}

void ForestGiantBattleMove::loadParams_() {
    WaitNearTarget::loadParams_();
    getStaticParam(&mAttackHeightMin_s, "AttackHeightMin");
    getStaticParam(&mAttackHeightMax_s, "AttackHeightMax");
}

}  // namespace uking::ai
