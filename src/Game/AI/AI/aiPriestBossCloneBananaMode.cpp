#include "Game/AI/AI/aiPriestBossCloneBananaMode.h"

namespace uking::ai {

PriestBossCloneBananaMode::PriestBossCloneBananaMode(const InitArg& arg)
    : PriestBossBananaMode(arg) {}

PriestBossCloneBananaMode::~PriestBossCloneBananaMode() = default;

bool PriestBossCloneBananaMode::init_(sead::Heap* heap) {
    return PriestBossBananaMode::init_(heap);
}

void PriestBossCloneBananaMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossBananaMode::enter_(params);
}

void PriestBossCloneBananaMode::leave_() {
    PriestBossBananaMode::leave_();
}

void PriestBossCloneBananaMode::loadParams_() {
    PriestBossBananaMode::loadParams_();
}

}  // namespace uking::ai
