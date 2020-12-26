#include "Game/AI/Action/actionNavMeshWalk.h"

namespace uking::action {

NavMeshWalk::NavMeshWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshWalk::~NavMeshWalk() = default;

bool NavMeshWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshWalk::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
