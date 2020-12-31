#include "Game/AI/AI/aiPriestBossMakeClone.h"

namespace uking::ai {

PriestBossMakeClone::PriestBossMakeClone(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMakeClone::~PriestBossMakeClone() = default;

bool PriestBossMakeClone::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMakeClone::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossMakeClone::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMakeClone::loadParams_() {
    getStaticParam(&mRespawnFrame_s, "RespawnFrame");
    getStaticParam(&mBackStepDistance_s, "BackStepDistance");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
