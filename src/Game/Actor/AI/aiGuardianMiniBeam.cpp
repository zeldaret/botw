#include "Game/Actor/AI/aiGuardianMiniBeam.h"

namespace uking::ai {

GuardianMiniBeam::GuardianMiniBeam(const InitArg& arg) : SimpleBeamExplode(arg) {}

GuardianMiniBeam::~GuardianMiniBeam() = default;

void GuardianMiniBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleBeamExplode::enter_(params);
}

void GuardianMiniBeam::leave_() {
    SimpleBeamExplode::leave_();
}

void GuardianMiniBeam::loadParams_() {
    SimpleBeamExplode::loadParams_();
}

}  // namespace uking::ai
