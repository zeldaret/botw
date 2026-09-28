#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"

namespace uking::action {

AvoidingCloseMoveBase::AvoidingCloseMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AvoidingCloseMoveBase::~AvoidingCloseMoveBase() = default;

bool AvoidingCloseMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AvoidingCloseMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AvoidingCloseMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AvoidingCloseMoveBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AvoidingCloseMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
