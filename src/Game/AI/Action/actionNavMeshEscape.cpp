#include "Game/AI/Action/actionNavMeshEscape.h"

namespace uking::action {

NavMeshEscape::NavMeshEscape(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshEscape::~NavMeshEscape() = default;

bool NavMeshEscape::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshEscape::leave_() {
    NavMeshAction::leave_();
}

void NavMeshEscape::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshEscape::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
