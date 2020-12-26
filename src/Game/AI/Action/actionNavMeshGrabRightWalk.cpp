#include "Game/AI/Action/actionNavMeshGrabRightWalk.h"

namespace uking::action {

NavMeshGrabRightWalk::NavMeshGrabRightWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGrabRightWalk::~NavMeshGrabRightWalk() = default;

bool NavMeshGrabRightWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshGrabRightWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshGrabRightWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshGrabRightWalk::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshGrabRightWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
