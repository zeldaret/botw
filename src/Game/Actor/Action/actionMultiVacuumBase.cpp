#include "Game/Actor/Action/actionMultiVacuumBase.h"

namespace uking::action {

MultiVacuumBase::MultiVacuumBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MultiVacuumBase::~MultiVacuumBase() = default;

bool MultiVacuumBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MultiVacuumBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MultiVacuumBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MultiVacuumBase::loadParams_() {
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

void MultiVacuumBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
