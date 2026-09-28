#include "Game/Actor/AI/aiPriestBossNormalMoveSelector.h"

namespace uking::ai {

PriestBossNormalMoveSelector::PriestBossNormalMoveSelector(const InitArg& arg) : PriestBoss(arg) {}

PriestBossNormalMoveSelector::~PriestBossNormalMoveSelector() = default;

bool PriestBossNormalMoveSelector::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossNormalMoveSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossNormalMoveSelector::leave_() {
    PriestBoss::leave_();
}

void PriestBossNormalMoveSelector::loadParams_() {
    PriestBoss::loadParams_();
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
}

}  // namespace uking::ai
