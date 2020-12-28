#include "Game/AI/Action/actionBackStepAttack.h"

namespace uking::action {

BackStepAttack::BackStepAttack(const InitArg& arg) : BackStepBase(arg) {}

BackStepAttack::~BackStepAttack() = default;

void BackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepBase::enter_(params);
}

void BackStepAttack::leave_() {
    BackStepBase::leave_();
}

void BackStepAttack::loadParams_() {
    BackStepBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

void BackStepAttack::calc_() {
    BackStepBase::calc_();
}

}  // namespace uking::action
