#include "Game/AI/Action/actionNavMeshRun.h"

namespace uking::action {

NavMeshRun::NavMeshRun(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshRun::~NavMeshRun() = default;

bool NavMeshRun::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshRun::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshRun::leave_() {
    NavMeshAction::leave_();
}

void NavMeshRun::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshRun::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
