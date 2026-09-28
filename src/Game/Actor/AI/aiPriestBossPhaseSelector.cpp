#include "Game/Actor/AI/aiPriestBossPhaseSelector.h"

namespace uking::ai {

PriestBossPhaseSelector::PriestBossPhaseSelector(const InitArg& arg) : PriestBoss(arg) {}

PriestBossPhaseSelector::~PriestBossPhaseSelector() = default;

bool PriestBossPhaseSelector::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossPhaseSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossPhaseSelector::leave_() {
    PriestBoss::leave_();
}

void PriestBossPhaseSelector::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mIsSelectOnlyOnce_s, "IsSelectOnlyOnce");
}

}  // namespace uking::ai
