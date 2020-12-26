#include "Game/AI/Action/actionFreeMoveToTarget.h"

namespace uking::action {

FreeMoveToTarget::FreeMoveToTarget(const InitArg& arg) : FreeMove(arg) {}

FreeMoveToTarget::~FreeMoveToTarget() = default;

bool FreeMoveToTarget::init_(sead::Heap* heap) {
    return FreeMove::init_(heap);
}

void FreeMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMove::enter_(params);
}

void FreeMoveToTarget::leave_() {
    FreeMove::leave_();
}

void FreeMoveToTarget::loadParams_() {
    FreeMove::loadParams_();
    getStaticParam(&mTargetUpdateInterval_s, "TargetUpdateInterval");
    getStaticParam(&mFinishRadius_s, "FinishRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void FreeMoveToTarget::calc_() {
    FreeMove::calc_();
}

}  // namespace uking::action
