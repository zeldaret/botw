#include "Game/AI/AI/aiPriestBossGiantDeadSelector.h"

namespace uking::ai {

PriestBossGiantDeadSelector::PriestBossGiantDeadSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossGiantDeadSelector::~PriestBossGiantDeadSelector() = default;

bool PriestBossGiantDeadSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossGiantDeadSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossGiantDeadSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossGiantDeadSelector::loadParams_() {
    getAITreeVariable(&mPriestBossDownSideASPlaying_a, "PriestBossDownSideASPlaying");
}

}  // namespace uking::ai
