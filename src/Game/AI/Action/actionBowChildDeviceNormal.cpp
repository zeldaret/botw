#include "Game/AI/Action/actionBowChildDeviceNormal.h"

namespace uking::action {

BowChildDeviceNormal::BowChildDeviceNormal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceNormal::~BowChildDeviceNormal() = default;

bool BowChildDeviceNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildDeviceNormal::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildDeviceNormal::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mAccelRate_s, "AccelRate");
    getStaticParam(&mBrakeStartDist_s, "BrakeStartDist");
    getStaticParam(&mVibrationSpeed_s, "VibrationSpeed");
    getStaticParam(&mStopDist_s, "StopDist");
    getStaticParam(&mVibrationLength_s, "VibrationLength");
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mIsMoveAccel_s, "IsMoveAccel");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildDeviceNormal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
