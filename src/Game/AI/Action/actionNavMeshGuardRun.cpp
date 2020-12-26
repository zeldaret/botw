#include "Game/AI/Action/actionNavMeshGuardRun.h"

namespace uking::action {

NavMeshGuardRun::NavMeshGuardRun(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGuardRun::~NavMeshGuardRun() = default;

bool NavMeshGuardRun::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshGuardRun::leave_() {
    NavMeshAction::leave_();
}

void NavMeshGuardRun::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshGuardRun::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
