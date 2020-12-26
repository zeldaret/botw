#include "Game/AI/Action/actionBoomerangMove.h"

namespace uking::action {

BoomerangMove::BoomerangMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BoomerangMove::~BoomerangMove() = default;

bool BoomerangMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BoomerangMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BoomerangMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void BoomerangMove::loadParams_() {
    getStaticParam(&mPreCurveTimer_s, "PreCurveTimer");
    getStaticParam(&mRadSpeed_s, "RadSpeed");
    getStaticParam(&mCurveSpeedRate_s, "CurveSpeedRate");
    getStaticParam(&mStraightSpeedRate_s, "StraightSpeedRate");
    getStaticParam(&mCurvePredictFrame_s, "CurvePredictFrame");
    getStaticParam(&mCurveCheckYDist_s, "CurveCheckYDist");
    getStaticParam(&mStraightPredictFrame_s, "StraightPredictFrame");
    getStaticParam(&mStraightCheckYDist_s, "StraightCheckYDist");
    getStaticParam(&mFlyLimitTime_s, "FlyLimitTime");
    getStaticParam(&mCatchAttentionName_s, "CatchAttentionName");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BoomerangMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
