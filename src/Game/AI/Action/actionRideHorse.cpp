#include "Game/AI/Action/actionRideHorse.h"

namespace uking::action {

RideHorse::RideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorse::~RideHorse() = default;

bool RideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RideHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void RideHorse::loadParams_() {
    getStaticParam(&mJumpHeightOffset_s, "JumpHeightOffset");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mFarRotSpeed_s, "FarRotSpeed");
    getStaticParam(&mNearRotSpeed_s, "NearRotSpeed");
    getStaticParam(&mRideRotSpeed_s, "RideRotSpeed");
    getStaticParam(&mLoopASInterpolateTime_s, "LoopASInterpolateTime");
    getStaticParam(&mPredictedRidePosOffset_s, "PredictedRidePosOffset");
    getStaticParam(&mPreRideSklRootOffset_s, "PreRideSklRootOffset");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void RideHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
