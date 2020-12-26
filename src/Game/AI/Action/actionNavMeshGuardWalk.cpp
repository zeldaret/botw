#include "Game/AI/Action/actionNavMeshGuardWalk.h"

namespace uking::action {

NavMeshGuardWalk::NavMeshGuardWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGuardWalk::~NavMeshGuardWalk() = default;

bool NavMeshGuardWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshGuardWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshGuardWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshGuardWalk::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshGuardWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
