#include "Game/AI/AI/aiPriestBossFormation.h"

namespace uking::ai {

PriestBossFormation::PriestBossFormation(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossFormation::~PriestBossFormation() = default;

bool PriestBossFormation::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossFormation::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossFormation::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossFormation::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
