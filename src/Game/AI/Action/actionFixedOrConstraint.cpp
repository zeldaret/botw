#include "Game/AI/Action/actionFixedOrConstraint.h"

namespace uking::action {

FixedOrConstraint::FixedOrConstraint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FixedOrConstraint::~FixedOrConstraint() = default;

bool FixedOrConstraint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FixedOrConstraint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FixedOrConstraint::leave_() {
    ksys::act::ai::Action::leave_();
}

void FixedOrConstraint::loadParams_() {}

void FixedOrConstraint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
