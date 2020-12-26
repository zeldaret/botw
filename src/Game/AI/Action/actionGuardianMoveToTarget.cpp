#include "Game/AI/Action/actionGuardianMoveToTarget.h"

namespace uking::action {

GuardianMoveToTarget::GuardianMoveToTarget(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianMoveToTarget::~GuardianMoveToTarget() = default;

bool GuardianMoveToTarget::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
}

void GuardianMoveToTarget::leave_() {
    GuardianMoveTo::leave_();
}

void GuardianMoveToTarget::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
}

void GuardianMoveToTarget::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
