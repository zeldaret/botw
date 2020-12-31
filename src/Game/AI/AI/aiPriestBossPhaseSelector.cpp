#include "Game/AI/AI/aiPriestBossPhaseSelector.h"

namespace uking::ai {

PriestBossPhaseSelector::PriestBossPhaseSelector(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossPhaseSelector::~PriestBossPhaseSelector() = default;

bool PriestBossPhaseSelector::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossPhaseSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossPhaseSelector::leave_() {
    PriestBossMode::leave_();
}

void PriestBossPhaseSelector::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mIsSelectOnlyOnce_s, "IsSelectOnlyOnce");
}

}  // namespace uking::ai
