#include "Game/AI/Action/actionDoubleAttack.h"

namespace uking::action {

DoubleAttack::DoubleAttack(const InitArg& arg) : StepDoubleAttack(arg) {}

DoubleAttack::~DoubleAttack() = default;

bool DoubleAttack::init_(sead::Heap* heap) {
    return StepDoubleAttack::init_(heap);
}

void DoubleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    StepDoubleAttack::enter_(params);
}

void DoubleAttack::leave_() {
    StepDoubleAttack::leave_();
}

void DoubleAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DoubleAttack::calc_() {
    StepDoubleAttack::calc_();
}

}  // namespace uking::action
