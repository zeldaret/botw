#include "Game/AI/Action/actionJumpToTargetFromWater.h"

namespace uking::action {

JumpToTargetFromWater::JumpToTargetFromWater(const InitArg& arg) : JumpTo(arg) {}

JumpToTargetFromWater::~JumpToTargetFromWater() = default;

bool JumpToTargetFromWater::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void JumpToTargetFromWater::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTo::enter_(params);
}

void JumpToTargetFromWater::leave_() {
    JumpTo::leave_();
}

void JumpToTargetFromWater::loadParams_() {
    JumpTo::loadParams_();
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mPreJumpAS_s, "PreJumpAS");
    getStaticParam(&mJumpAS_s, "JumpAS");
    getStaticParam(&mLandAS_s, "LandAS");
}

void JumpToTargetFromWater::calc_() {
    JumpTo::calc_();
}

}  // namespace uking::action
