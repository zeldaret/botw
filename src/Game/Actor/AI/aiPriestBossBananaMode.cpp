#include "Game/Actor/AI/aiPriestBossBananaMode.h"

namespace uking::ai {

PriestBossBananaMode::PriestBossBananaMode(const InitArg& arg) : PriestBoss(arg) {}

PriestBossBananaMode::~PriestBossBananaMode() = default;

bool PriestBossBananaMode::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossBananaMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossBananaMode::leave_() {
    PriestBoss::leave_();
}

void PriestBossBananaMode::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mHealAmount_s, "HealAmount");
    getStaticParam(&mTimeUpFrames_s, "TimeUpFrames");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
