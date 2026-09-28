#include "Game/Actor/Action/actionGuardianMiniNeckSpinBeam.h"

namespace uking::action {

GuardianMiniNeckSpinBeam::GuardianMiniNeckSpinBeam(const InitArg& arg) : BeamNeckSpin(arg) {}

GuardianMiniNeckSpinBeam::~GuardianMiniNeckSpinBeam() = default;

void GuardianMiniNeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamNeckSpin::enter_(params);
}

void GuardianMiniNeckSpinBeam::loadParams_() {
    BeamNeckSpin::loadParams_();
    getStaticParam(&mSpinNum_s, "SpinNum");
    getStaticParam(&mMaxLengthTime_s, "MaxLengthTime");
    getStaticParam(&mIsStraight_s, "IsStraight");
}

void GuardianMiniNeckSpinBeam::calc_() {
    BeamNeckSpin::calc_();
}

}  // namespace uking::action
