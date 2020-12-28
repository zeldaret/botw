#include "Game/AI/Action/actionBackWalkBase.h"

namespace uking::action {

BackWalkBase::BackWalkBase(const InitArg& arg) : ActionEx(arg) {}

BackWalkBase::~BackWalkBase() = default;

void BackWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BackWalkBase::leave_() {
    ActionEx::leave_();
}

void BackWalkBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mDecelRatio_s, "DecelRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsCliffCheck_s, "IsCliffCheck");
}

void BackWalkBase::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
