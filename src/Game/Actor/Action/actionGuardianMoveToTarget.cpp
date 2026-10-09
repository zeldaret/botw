#include "Game/Actor/Action/actionGuardianMoveToTarget.h"

namespace uking::action {

GuardianMoveToTarget::GuardianMoveToTarget(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianMoveToTarget::~GuardianMoveToTarget() = default;

bool GuardianMoveToTarget::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
}

void GuardianMoveToTarget::leave_() {
    GuardianActionBase::leave_();
}

void GuardianMoveToTarget::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
}

void GuardianMoveToTarget::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
