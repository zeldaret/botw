#include "Game/AI/AI/aiPriestBossNormalMoveSelector.h"

namespace uking::ai {

PriestBossNormalMoveSelector::PriestBossNormalMoveSelector(const InitArg& arg)
    : PriestBossMode(arg) {}

PriestBossNormalMoveSelector::~PriestBossNormalMoveSelector() = default;

bool PriestBossNormalMoveSelector::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossNormalMoveSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossNormalMoveSelector::leave_() {
    PriestBossMode::leave_();
}

void PriestBossNormalMoveSelector::loadParams_() {
    PriestBossMode::loadParams_();
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
}

}  // namespace uking::ai
