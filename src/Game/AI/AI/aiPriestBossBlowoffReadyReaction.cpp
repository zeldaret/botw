#include "Game/AI/AI/aiPriestBossBlowoffReadyReaction.h"

namespace uking::ai {

PriestBossBlowoffReadyReaction::PriestBossBlowoffReadyReaction(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossBlowoffReadyReaction::~PriestBossBlowoffReadyReaction() = default;

bool PriestBossBlowoffReadyReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossBlowoffReadyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossBlowoffReadyReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossBlowoffReadyReaction::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
