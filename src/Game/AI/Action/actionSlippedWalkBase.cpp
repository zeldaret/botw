#include "Game/AI/Action/actionSlippedWalkBase.h"

namespace uking::action {

SlippedWalkBase::SlippedWalkBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedWalkBase::~SlippedWalkBase() = default;

bool SlippedWalkBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SlippedWalkBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedWalkBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SlippedWalkBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
