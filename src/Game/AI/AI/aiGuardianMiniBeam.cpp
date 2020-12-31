#include "Game/AI/AI/aiGuardianMiniBeam.h"

namespace uking::ai {

GuardianMiniBeam::GuardianMiniBeam(const InitArg& arg) : BeamExplodeBase(arg) {}

GuardianMiniBeam::~GuardianMiniBeam() = default;

void GuardianMiniBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeBase::enter_(params);
}

void GuardianMiniBeam::leave_() {
    BeamExplodeBase::leave_();
}

void GuardianMiniBeam::loadParams_() {
    BeamExplodeBase::loadParams_();
}

}  // namespace uking::ai
