#include "Game/AI/AI/aiNavMoveTargetWithJumpWater.h"

namespace uking::ai {

NavMoveTargetWithJumpWater::NavMoveTargetWithJumpWater(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveTargetWithJumpWater::~NavMoveTargetWithJumpWater() = default;

bool NavMoveTargetWithJumpWater::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveTargetWithJumpWater::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
}

void NavMoveTargetWithJumpWater::leave_() {
    NavMoveTarget::leave_();
}

void NavMoveTargetWithJumpWater::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mWaterCheckDist_s, "WaterCheckDist");
    getStaticParam(&mIsCheckDamage_s, "IsCheckDamage");
}

}  // namespace uking::ai
