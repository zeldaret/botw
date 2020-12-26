#include "Game/AI/Action/actionBalloonBase.h"

namespace uking::action {

BalloonBase::BalloonBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BalloonBase::~BalloonBase() = default;

bool BalloonBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BalloonBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BalloonBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void BalloonBase::loadParams_() {
    getStaticParam(&mUpLimitSpeed_s, "UpLimitSpeed");
    getStaticParam(&mMaxAccel_s, "MaxAccel");
    getStaticParam(&mMassScale_s, "MassScale");
    getStaticParam(&mHeightLimit_s, "HeightLimit");
    getStaticParam(&mBreakTimer_s, "BreakTimer");
    getStaticParam(&mWindAccScale_s, "WindAccScale");
    getStaticParam(&mWindSpdScale_s, "WindSpdScale");
    getStaticParam(&mStayAccScale_s, "StayAccScale");
    getStaticParam(&mReturnStrengthFactor_s, "ReturnStrengthFactor");
    getStaticParam(&mRemainsHeightLimit_s, "RemainsHeightLimit");
    getStaticParam(&mIsChaseInitHeight_s, "IsChaseInitHeight");
    getStaticParam(&mReturnToOriginalPos_s, "ReturnToOriginalPos");
    getAITreeVariable(&mBalloonHungActorBaseProcID_a, "BalloonHungActorBaseProcID");
    getAITreeVariable(&mIsFlyingBalloon_a, "IsFlyingBalloon");
}

void BalloonBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
