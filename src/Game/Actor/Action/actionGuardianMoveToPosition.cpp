#include "Game/Actor/Action/actionGuardianMoveToPosition.h"

namespace uking::action {

GuardianMoveToPosition::GuardianMoveToPosition(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianMoveToPosition::~GuardianMoveToPosition() = default;

bool GuardianMoveToPosition::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianMoveToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
}

void GuardianMoveToPosition::leave_() {
    GuardianActionBase::leave_();
}

void GuardianMoveToPosition::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDecelerate_s, "Decelerate");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

void GuardianMoveToPosition::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
