#include "Game/AI/Action/actionFootStepCalcOn.h"

namespace uking::action {

FootStepCalcOn::FootStepCalcOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FootStepCalcOn::~FootStepCalcOn() = default;

bool FootStepCalcOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FootStepCalcOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FootStepCalcOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void FootStepCalcOn::loadParams_() {
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void FootStepCalcOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
