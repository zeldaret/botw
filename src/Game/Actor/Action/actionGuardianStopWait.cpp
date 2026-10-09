#include "Game/Actor/Action/actionGuardianStopWait.h"

namespace uking::action {

GuardianStopWait::GuardianStopWait(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianStopWait::~GuardianStopWait() = default;

bool GuardianStopWait::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianStopWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
}

void GuardianStopWait::leave_() {
    GuardianActionBase::leave_();
}

void GuardianStopWait::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void GuardianStopWait::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
