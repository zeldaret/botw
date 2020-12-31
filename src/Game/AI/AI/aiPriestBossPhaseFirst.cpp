#include "Game/AI/AI/aiPriestBossPhaseFirst.h"

namespace uking::ai {

PriestBossPhaseFirst::PriestBossPhaseFirst(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFirst::~PriestBossPhaseFirst() = default;

bool PriestBossPhaseFirst::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFirst::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseFirst::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseFirst::loadParams_() {
    PriestBossPhase::loadParams_();
}

}  // namespace uking::ai
