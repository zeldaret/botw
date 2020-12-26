#include "Game/AI/Action/actionForkFlyToTargetDirect.h"

namespace uking::action {

ForkFlyToTargetDirect::ForkFlyToTargetDirect(const InitArg& arg) : FreeMovingAction(arg) {}

ForkFlyToTargetDirect::~ForkFlyToTargetDirect() = default;

bool ForkFlyToTargetDirect::init_(sead::Heap* heap) {
    return FreeMovingAction::init_(heap);
}

void ForkFlyToTargetDirect::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMovingAction::enter_(params);
}

void ForkFlyToTargetDirect::leave_() {
    FreeMovingAction::leave_();
}

void ForkFlyToTargetDirect::loadParams_() {
    FreeMovingAction::loadParams_();
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mMoveSpd_s, "MoveSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mOnEndForceStop_s, "OnEndForceStop");
    getStaticParam(&mOnGround_s, "OnGround");
}

void ForkFlyToTargetDirect::calc_() {
    FreeMovingAction::calc_();
}

}  // namespace uking::action
