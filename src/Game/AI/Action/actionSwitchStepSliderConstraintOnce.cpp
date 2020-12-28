#include "Game/AI/Action/actionSwitchStepSliderConstraintOnce.h"

namespace uking::action {

SwitchStepSliderConstraintOnce::SwitchStepSliderConstraintOnce(const InitArg& arg)
    : SwitchStepSliderConstraint(arg) {}

bool SwitchStepSliderConstraintOnce::init_(sead::Heap* heap) {
    return SwitchStepSliderConstraint::init_(heap);
}

void SwitchStepSliderConstraintOnce::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchStepSliderConstraint::enter_(params);
}

void SwitchStepSliderConstraintOnce::leave_() {
    SwitchStepSliderConstraint::leave_();
}

void SwitchStepSliderConstraintOnce::loadParams_() {
    SwitchStepSliderConstraint::loadParams_();
}

void SwitchStepSliderConstraintOnce::calc_() {
    SwitchStepSliderConstraint::calc_();
}

}  // namespace uking::action
