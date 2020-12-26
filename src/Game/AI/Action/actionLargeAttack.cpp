#include "Game/AI/Action/actionLargeAttack.h"

namespace uking::action {

LargeAttack::LargeAttack(const InitArg& arg) : ActionEx(arg) {}

LargeAttack::~LargeAttack() = default;

bool LargeAttack::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void LargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void LargeAttack::leave_() {
    ActionEx::leave_();
}

void LargeAttack::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

void LargeAttack::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
