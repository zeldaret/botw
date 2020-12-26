#include "Game/AI/Action/actionFreeMoveToTargetInWataer.h"

namespace uking::action {

FreeMoveToTargetInWataer::FreeMoveToTargetInWataer(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToTargetInWataer::~FreeMoveToTargetInWataer() = default;

bool FreeMoveToTargetInWataer::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToTargetInWataer::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
}

void FreeMoveToTargetInWataer::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToTargetInWataer::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mAllowMoveWaterDepth_s, "AllowMoveWaterDepth");
    getStaticParam(&mForceTurnLimitSpeedStream_s, "ForceTurnLimitSpeedStream");
    getStaticParam(&mIsForceTurnAgainstStream_s, "IsForceTurnAgainstStream");
    getStaticParam(&mForceUseFrontDir_s, "ForceUseFrontDir");
}

void FreeMoveToTargetInWataer::calc_() {
    FreeMoveToTarget::calc_();
}

}  // namespace uking::action
