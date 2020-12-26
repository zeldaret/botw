#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDistWithTgtBase.h"

namespace uking::action {

MultiVacuumRotScaleTimeByDistWithTgtBase::MultiVacuumRotScaleTimeByDistWithTgtBase(
    const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MultiVacuumRotScaleTimeByDistWithTgtBase::~MultiVacuumRotScaleTimeByDistWithTgtBase() = default;

bool MultiVacuumRotScaleTimeByDistWithTgtBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MultiVacuumRotScaleTimeByDistWithTgtBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MultiVacuumRotScaleTimeByDistWithTgtBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MultiVacuumRotScaleTimeByDistWithTgtBase::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAddTimeVacuuming_s, "AddTimeVacuuming");
    getStaticParam(&mAddTimeNearVacuuming_s, "AddTimeNearVacuuming");
    getStaticParam(&mVacuumNum_s, "VacuumNum");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mTargetAccRate_s, "TargetAccRate");
    getStaticParam(&mTargetSpeed_s, "TargetSpeed");
    getStaticParam(&mBaseWeight_s, "BaseWeight");
    getStaticParam(&mVacuumAngle_s, "VacuumAngle");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mEndAS_s, "EndAS");
    getStaticParam(&mVacuumPosOffset_s, "VacuumPosOffset");
}

void MultiVacuumRotScaleTimeByDistWithTgtBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
