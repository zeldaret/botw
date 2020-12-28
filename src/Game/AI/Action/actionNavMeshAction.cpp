#include "Game/AI/Action/actionNavMeshAction.h"

namespace uking::action {

NavMeshAction::NavMeshAction(const InitArg& arg) : ActionEx(arg) {}

NavMeshAction::~NavMeshAction() = default;

void NavMeshAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void NavMeshAction::leave_() {
    ActionEx::leave_();
}

void NavMeshAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshAction::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
