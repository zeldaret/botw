#include "Game/AI/Action/actionJumpAttack.h"

namespace uking::action {

JumpAttack::JumpAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpAttack::~JumpAttack() = default;

void JumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpAttack::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
}

void JumpAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
