#include "Game/AI/Action/actionStopForLimitedTime.h"

namespace uking::action {

StopForLimitedTime::StopForLimitedTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopForLimitedTime::~StopForLimitedTime() = default;

bool StopForLimitedTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopForLimitedTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StopForLimitedTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopForLimitedTime::loadParams_() {
    getStaticParam(&mKeepActRotation_s, "KeepActRotation");
    getStaticParam(&mEnableStaticCompoundRotate_s, "EnableStaticCompoundRotate");
    getStaticParam(&mIsSetEndByTime_s, "IsSetEndByTime");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void StopForLimitedTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
