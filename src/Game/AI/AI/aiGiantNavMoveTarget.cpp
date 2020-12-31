#include "Game/AI/AI/aiGiantNavMoveTarget.h"

namespace uking::ai {

GiantNavMoveTarget::GiantNavMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantNavMoveTarget::~GiantNavMoveTarget() = default;

bool GiantNavMoveTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantNavMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantNavMoveTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getStaticParam(&mTargetVMax_s, "TargetVMax");
    getStaticParam(&mTargetVMin_s, "TargetVMin");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
