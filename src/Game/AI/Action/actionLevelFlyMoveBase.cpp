#include "Game/AI/Action/actionLevelFlyMoveBase.h"

namespace uking::action {

LevelFlyMoveBase::LevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyMoveBase::~LevelFlyMoveBase() = default;

bool LevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LevelFlyMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void LevelFlyMoveBase::loadParams_() {
    getStaticParam(&mXZSpeed_s, "XZSpeed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mDownSpeed_s, "DownSpeed");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mIsOverRise_s, "IsOverRise");
    getStaticParam(&mIsSlowDownNearGoal_s, "IsSlowDownNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    // FIXME: CALL sub_71006F3DF8 @ 0x71006f3df8
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void LevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
