#include "Game/AI/Action/actionGuardianAimBeam.h"

namespace uking::action {

GuardianAimBeam::GuardianAimBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianAimBeam::~GuardianAimBeam() = default;

bool GuardianAimBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianAimBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianAimBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianAimBeam::loadParams_() {
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationTime_s, "FluctuationTime");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mNodeOffset_s, "NodeOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GuardianAimBeam::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
