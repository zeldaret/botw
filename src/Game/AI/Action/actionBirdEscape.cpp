#include "Game/AI/Action/actionBirdEscape.h"

namespace uking::action {

BirdEscape::BirdEscape(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BirdEscape::~BirdEscape() = default;

bool BirdEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BirdEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BirdEscape::leave_() {
    ksys::act::ai::Action::leave_();
}

void BirdEscape::loadParams_() {
    getStaticParam(&mMoveSpeedMax_s, "MoveSpeedMax");
    getStaticParam(&mMoveSpeedMin_s, "MoveSpeedMin");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mInterpolateFrameForMaxSpeed_s, "InterpolateFrameForMaxSpeed");
    getStaticParam(&mTargetEscapeWidthMax_s, "TargetEscapeWidthMax");
    getStaticParam(&mTargetEscapeWidthMin_s, "TargetEscapeWidthMin");
    getStaticParam(&mTargetHeightMax_s, "TargetHeightMax");
    getStaticParam(&mTargetHeightMin_s, "TargetHeightMin");
    getStaticParam(&mTargetTurnAngle_s, "TargetTurnAngle");
    getStaticParam(&mContinueEscapeDistanceXZ_s, "ContinueEscapeDistanceXZ");
    getStaticParam(&mAdditionalWidth_s, "AdditionalWidth");
    getStaticParam(&mTargetUpperAngle_s, "TargetUpperAngle");
    getStaticParam(&mStartReduceHeightRate_s, "StartReduceHeightRate");
}

void BirdEscape::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
