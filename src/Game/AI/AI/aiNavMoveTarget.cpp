#include "Game/AI/AI/aiNavMoveTarget.h"

namespace uking::ai {

NavMoveTarget::NavMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMoveTarget::~NavMoveTarget() = default;

bool NavMoveTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavMoveTarget::loadParams_() {
    getStaticParam(&mVibrateCheckTime_s, "VibrateCheckTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getStaticParam(&mUseCharacterRadius_s, "UseCharacterRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
    getStaticParam(&mIsLastLineReachCheck_s, "IsLastLineReachCheck");
    getStaticParam(&mRotVibrateCheckTime_s, "RotVibrateCheckTime");
}

}  // namespace uking::ai
