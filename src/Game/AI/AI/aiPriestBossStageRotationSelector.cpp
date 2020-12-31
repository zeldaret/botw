#include "Game/AI/AI/aiPriestBossStageRotationSelector.h"

namespace uking::ai {

PriestBossStageRotationSelector::PriestBossStageRotationSelector(const InitArg& arg)
    : PriestBossMode(arg) {}

PriestBossStageRotationSelector::~PriestBossStageRotationSelector() = default;

bool PriestBossStageRotationSelector::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossStageRotationSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossStageRotationSelector::leave_() {
    PriestBossMode::leave_();
}

void PriestBossStageRotationSelector::loadParams_() {
    PriestBossMode::loadParams_();
}

}  // namespace uking::ai
