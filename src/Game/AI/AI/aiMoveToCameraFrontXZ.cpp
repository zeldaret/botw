#include "Game/AI/AI/aiMoveToCameraFrontXZ.h"

namespace uking::ai {

MoveToCameraFrontXZ::MoveToCameraFrontXZ(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveToCameraFrontXZ::~MoveToCameraFrontXZ() = default;

bool MoveToCameraFrontXZ::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveToCameraFrontXZ::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoveToCameraFrontXZ::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveToCameraFrontXZ::loadParams_() {
    getStaticParam(&mReverseTimer_s, "ReverseTimer");
    getStaticParam(&mReverseCount_s, "ReverseCount");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mDistFromPlayer_s, "DistFromPlayer");
    getStaticParam(&mMinDistFromPlayer_s, "MinDistFromPlayer");
    getStaticParam(&mAvoidPlayerDist_s, "AvoidPlayerDist");
    getStaticParam(&mAddLineCheckNavRadius_s, "AddLineCheckNavRadius");
    getStaticParam(&mReachableRadius_s, "ReachableRadius");
    getStaticParam(&mIsSuccessByLineReachable_s, "IsSuccessByLineReachable");
}

}  // namespace uking::ai
