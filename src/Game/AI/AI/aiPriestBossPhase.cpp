#include "Game/AI/AI/aiPriestBossPhase.h"

namespace uking::ai {

PriestBossPhase::PriestBossPhase(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossPhase::~PriestBossPhase() = default;

bool PriestBossPhase::init_(sead::Heap* heap) {
    return PriestBossMeta::init_(heap);
}

void PriestBossPhase::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
}

void PriestBossPhase::leave_() {
    PriestBossMeta::leave_();
}

void PriestBossPhase::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mPercentLifeTransition_s, "PercentLifeTransition");
    getStaticParam(&mPercentLifePrevious_s, "PercentLifePrevious");
}

}  // namespace uking::ai
