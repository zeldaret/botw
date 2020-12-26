#include "Game/AI/Action/actionJumpTo.h"

namespace uking::action {

JumpTo::JumpTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpTo::~JumpTo() = default;

bool JumpTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpTo::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpTo::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpGravity_s, "JumpGravity");
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void JumpTo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
