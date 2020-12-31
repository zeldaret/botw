#include "Game/AI/AI/aiPriestBossPhaseFinish.h"

namespace uking::ai {

PriestBossPhaseFinish::PriestBossPhaseFinish(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFinish::~PriestBossPhaseFinish() = default;

bool PriestBossPhaseFinish::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFinish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseFinish::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseFinish::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mStartDemoDelayFrames_s, "StartDemoDelayFrames");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

}  // namespace uking::ai
