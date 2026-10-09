#include "Game/Actor/Action/actionSlippedMoveBase.h"

namespace uking::action {

SlippedMoveBase::SlippedMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedMoveBase::~SlippedMoveBase() = default;

bool SlippedMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SlippedMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedMoveBase::loadParams_() {
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

void SlippedMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
