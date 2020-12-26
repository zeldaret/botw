#include "Game/AI/Action/actionGuardianStopWait.h"

namespace uking::action {

GuardianStopWait::GuardianStopWait(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianStopWait::~GuardianStopWait() = default;

bool GuardianStopWait::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianStopWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
}

void GuardianStopWait::leave_() {
    GuardianMoveTo::leave_();
}

void GuardianStopWait::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void GuardianStopWait::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
