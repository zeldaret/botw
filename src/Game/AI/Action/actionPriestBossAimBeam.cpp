#include "Game/AI/Action/actionPriestBossAimBeam.h"

namespace uking::action {

PriestBossAimBeam::PriestBossAimBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossAimBeam::~PriestBossAimBeam() = default;

bool PriestBossAimBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossAimBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossAimBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossAimBeam::loadParams_() {
    getStaticParam(&mAimLockFrame_s, "AimLockFrame");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationTime_s, "FluctuationTime");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mAimMaxLength_s, "AimMaxLength");
    getStaticParam(&mAimOffToTarget_s, "AimOffToTarget");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mNodeOffset_s, "NodeOffset");
    getDynamicParam(&mAimTargetPos_d, "AimTargetPos");
}

void PriestBossAimBeam::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
