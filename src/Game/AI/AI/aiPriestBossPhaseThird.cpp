#include "Game/AI/AI/aiPriestBossPhaseThird.h"

namespace uking::ai {

PriestBossPhaseThird::PriestBossPhaseThird(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseThird::~PriestBossPhaseThird() = default;

bool PriestBossPhaseThird::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseThird::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseThird::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseThird::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mBreakIronBallCount_s, "BreakIronBallCount");
}

}  // namespace uking::ai
