#include "Game/AI/AI/aiLynelNavMoveNoStop.h"

namespace uking::ai {

LynelNavMoveNoStop::LynelNavMoveNoStop(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelNavMoveNoStop::~LynelNavMoveNoStop() = default;

bool LynelNavMoveNoStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelNavMoveNoStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelNavMoveNoStop::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelNavMoveNoStop::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
