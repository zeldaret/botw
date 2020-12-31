#include "Game/AI/AI/aiPriestBossMode.h"

namespace uking::ai {

PriestBossMode::PriestBossMode(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMode::~PriestBossMode() = default;

bool PriestBossMode::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossMode::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMode::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
