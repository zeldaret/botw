#include "Game/AI/Action/actionGuardianChargeBeam.h"

namespace uking::action {

GuardianChargeBeam::GuardianChargeBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianChargeBeam::~GuardianChargeBeam() = default;

bool GuardianChargeBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianChargeBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianChargeBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianChargeBeam::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mChargeRadius_s, "ChargeRadius");
    getStaticParam(&mColor_s, "Color");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GuardianChargeBeam::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
