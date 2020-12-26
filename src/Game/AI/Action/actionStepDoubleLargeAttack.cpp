#include "Game/AI/Action/actionStepDoubleLargeAttack.h"

namespace uking::action {

StepDoubleLargeAttack::StepDoubleLargeAttack(const InitArg& arg) : StepDoubleAttack(arg) {}

StepDoubleLargeAttack::~StepDoubleLargeAttack() = default;

bool StepDoubleLargeAttack::init_(sead::Heap* heap) {
    return StepDoubleAttack::init_(heap);
}

void StepDoubleLargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    StepDoubleAttack::enter_(params);
}

void StepDoubleLargeAttack::leave_() {
    StepDoubleAttack::leave_();
}

void StepDoubleLargeAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void StepDoubleLargeAttack::calc_() {
    StepDoubleAttack::calc_();
}

}  // namespace uking::action
