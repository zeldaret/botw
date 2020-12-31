#include "Game/AI/AI/aiGuardianBeam.h"

namespace uking::ai {

GuardianBeam::GuardianBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianBeam::~GuardianBeam() = default;

bool GuardianBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeam::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
}

}  // namespace uking::ai
