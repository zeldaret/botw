#include "Game/AI/AI/aiGuardianMiniBeamToExplosives.h"

namespace uking::ai {

GuardianMiniBeamToExplosives::GuardianMiniBeamToExplosives(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamToExplosives::~GuardianMiniBeamToExplosives() = default;

void GuardianMiniBeamToExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBeamAttack::enter_(params);
}

void GuardianMiniBeamToExplosives::loadParams_() {
    GuardianMiniBeamAttack::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
