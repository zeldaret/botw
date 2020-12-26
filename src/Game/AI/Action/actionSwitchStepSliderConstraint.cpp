#include "Game/AI/Action/actionSwitchStepSliderConstraint.h"

namespace uking::action {

SwitchStepSliderConstraint::SwitchStepSliderConstraint(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SwitchStepSliderConstraint::~SwitchStepSliderConstraint() = default;

bool SwitchStepSliderConstraint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchStepSliderConstraint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchStepSliderConstraint::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchStepSliderConstraint::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mImpulse_s, "Impulse");
    getStaticParam(&mMinLimit_s, "MinLimit");
    getStaticParam(&mMaxLimit_s, "MaxLimit");
    getStaticParam(&mSwTh_s, "SwTh");
    getStaticParam(&mFriction_s, "Friction");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mOnASName_s, "OnASName");
    getStaticParam(&mOffASName_s, "OffASName");
}

void SwitchStepSliderConstraint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
