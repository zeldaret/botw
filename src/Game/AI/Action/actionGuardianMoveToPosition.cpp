#include "Game/AI/Action/actionGuardianMoveToPosition.h"

namespace uking::action {

GuardianMoveToPosition::GuardianMoveToPosition(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianMoveToPosition::~GuardianMoveToPosition() = default;

bool GuardianMoveToPosition::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianMoveToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
}

void GuardianMoveToPosition::leave_() {
    GuardianMoveTo::leave_();
}

void GuardianMoveToPosition::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDecelerate_s, "Decelerate");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

void GuardianMoveToPosition::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
