#include "Game/AI/AI/aiPriestBossBananaMode.h"

namespace uking::ai {

PriestBossBananaMode::PriestBossBananaMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossBananaMode::~PriestBossBananaMode() = default;

bool PriestBossBananaMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossBananaMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossBananaMode::leave_() {
    PriestBossMode::leave_();
}

void PriestBossBananaMode::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mHealAmount_s, "HealAmount");
    getStaticParam(&mTimeUpFrames_s, "TimeUpFrames");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
