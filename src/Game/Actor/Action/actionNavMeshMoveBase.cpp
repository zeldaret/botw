#include "Game/Actor/Action/actionNavMeshMoveBase.h"

namespace uking::action {

NavMeshMoveBase::NavMeshMoveBase(const InitArg& arg) : ActionEx(arg) {}

NavMeshMoveBase::~NavMeshMoveBase() = default;

void NavMeshMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void NavMeshMoveBase::leave_() {
    ActionEx::leave_();
}

void NavMeshMoveBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshMoveBase::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
