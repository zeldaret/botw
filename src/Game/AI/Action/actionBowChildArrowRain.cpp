#include "Game/AI/Action/actionBowChildArrowRain.h"

namespace uking::action {

BowChildArrowRain::BowChildArrowRain(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildArrowRain::~BowChildArrowRain() = default;

bool BowChildArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildArrowRain::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildArrowRain::loadParams_() {
    getStaticParam(&mRainMax_s, "RainMax");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveHeight_s, "MoveHeight");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mMoveCountNum_s, "MoveCountNum");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mMoveOffsetBase_s, "MoveOffsetBase");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mRotateStepMax_s, "RotateStepMax");
    getStaticParam(&mAngleToTarget_s, "AngleToTarget");
    getStaticParam(&mTargetOffsetBase_s, "TargetOffsetBase");
    getStaticParam(&mRainScale_s, "RainScale");
    getStaticParam(&mToTargetTime_s, "ToTargetTime");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsIgnoreHightOffset_d, "IsIgnoreHightOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildArrowRain::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
