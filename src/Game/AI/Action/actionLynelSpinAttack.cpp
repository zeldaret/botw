#include "Game/AI/Action/actionLynelSpinAttack.h"

namespace uking::action {

LynelSpinAttack::LynelSpinAttack(const InitArg& arg) : ForkWeaponAttack(arg) {}

LynelSpinAttack::~LynelSpinAttack() = default;

bool LynelSpinAttack::init_(sead::Heap* heap) {
    return ForkWeaponAttack::init_(heap);
}

void LynelSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttack::enter_(params);
}

void LynelSpinAttack::leave_() {
    ForkWeaponAttack::leave_();
}

void LynelSpinAttack::loadParams_() {
    ForkWeaponAttack::loadParams_();
    getStaticParam(&mMinLoopTime_s, "MinLoopTime");
    getStaticParam(&mLoopEndAngle_s, "LoopEndAngle");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mLoopASName_s, "LoopASName");
    getStaticParam(&mEndASName_s, "EndASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelSpinAttack::calc_() {
    ForkWeaponAttack::calc_();
}

}  // namespace uking::action
