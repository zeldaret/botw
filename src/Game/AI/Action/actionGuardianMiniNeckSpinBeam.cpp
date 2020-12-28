#include "Game/AI/Action/actionGuardianMiniNeckSpinBeam.h"

namespace uking::action {

GuardianMiniNeckSpinBeam::GuardianMiniNeckSpinBeam(const InitArg& arg) : NeckSpinBeam(arg) {}

GuardianMiniNeckSpinBeam::~GuardianMiniNeckSpinBeam() = default;

void GuardianMiniNeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpinBeam::enter_(params);
}

void GuardianMiniNeckSpinBeam::loadParams_() {
    NeckSpinBeam::loadParams_();
    getStaticParam(&mSpinNum_s, "SpinNum");
    getStaticParam(&mMaxLengthTime_s, "MaxLengthTime");
    getStaticParam(&mIsStraight_s, "IsStraight");
}

void GuardianMiniNeckSpinBeam::calc_() {
    NeckSpinBeam::calc_();
}

}  // namespace uking::action
