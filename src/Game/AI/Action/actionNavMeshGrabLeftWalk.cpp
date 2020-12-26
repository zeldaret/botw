#include "Game/AI/Action/actionNavMeshGrabLeftWalk.h"

namespace uking::action {

NavMeshGrabLeftWalk::NavMeshGrabLeftWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGrabLeftWalk::~NavMeshGrabLeftWalk() = default;

bool NavMeshGrabLeftWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshGrabLeftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshGrabLeftWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshGrabLeftWalk::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshGrabLeftWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
