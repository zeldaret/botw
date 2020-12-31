#include "Game/AI/AI/aiLynelLineMoveAttack.h"

namespace uking::ai {

LynelLineMoveAttack::LynelLineMoveAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelLineMoveAttack::~LynelLineMoveAttack() = default;

bool LynelLineMoveAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelLineMoveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelLineMoveAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelLineMoveAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mGoalRadius_s, "GoalRadius");
    getDynamicParam(&mIsSkipPrepare_d, "IsSkipPrepare");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
