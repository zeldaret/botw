#include "Game/AI/Action/actionAttackJumpToTarget.h"

namespace uking::action {

AttackJumpToTarget::AttackJumpToTarget(const InitArg& arg) : JumpToTarget(arg) {}

AttackJumpToTarget::~AttackJumpToTarget() = default;

void AttackJumpToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpToTarget::enter_(params);
}

void AttackJumpToTarget::leave_() {
    JumpToTarget::leave_();
}

void AttackJumpToTarget::loadParams_() {
    JumpToTarget::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mPosOffsetDist_s, "PosOffsetDist");
    getStaticParam(&mIsCheckNoChangeAS_s, "IsCheckNoChangeAS");
}

void AttackJumpToTarget::calc_() {
    JumpToTarget::calc_();
}

}  // namespace uking::action
