#include "Game/AI/Action/actionNavMeshJump.h"

namespace uking::action {

NavMeshJump::NavMeshJump(const InitArg& arg) : JumpTo(arg) {}

NavMeshJump::~NavMeshJump() = default;

bool NavMeshJump::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void NavMeshJump::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTo::enter_(params);
}

void NavMeshJump::leave_() {
    JumpTo::leave_();
}

void NavMeshJump::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpGravity_s, "JumpGravity");
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshJump::calc_() {
    JumpTo::calc_();
}

}  // namespace uking::action
