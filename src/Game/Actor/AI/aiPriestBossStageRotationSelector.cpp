#include "Game/Actor/AI/aiPriestBossStageRotationSelector.h"

namespace uking::ai {

PriestBossStageRotationSelector::PriestBossStageRotationSelector(const InitArg& arg)
    : PriestBoss(arg) {}

PriestBossStageRotationSelector::~PriestBossStageRotationSelector() = default;

bool PriestBossStageRotationSelector::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossStageRotationSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossStageRotationSelector::leave_() {
    PriestBoss::leave_();
}

void PriestBossStageRotationSelector::loadParams_() {
    PriestBoss::loadParams_();
}

}  // namespace uking::ai
