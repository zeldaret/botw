#include "Game/AI/AI/aiPriestBossBeamExplode.h"

namespace uking::ai {

PriestBossBeamExplode::PriestBossBeamExplode(const InitArg& arg) : BeamExplodeEitherHit(arg) {}

PriestBossBeamExplode::~PriestBossBeamExplode() = default;

bool PriestBossBeamExplode::init_(sead::Heap* heap) {
    return BeamExplodeEitherHit::init_(heap);
}

void PriestBossBeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeEitherHit::enter_(params);
}

void PriestBossBeamExplode::leave_() {
    BeamExplodeEitherHit::leave_();
}

void PriestBossBeamExplode::loadParams_() {
    BeamExplodeEitherHit::loadParams_();
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mMaxDistanceChangeableBorder_s, "MaxDistanceChangeableBorder");
    getStaticParam(&mMaxDistanceChangeableRevise_s, "MaxDistanceChangeableRevise");
}

}  // namespace uking::ai
