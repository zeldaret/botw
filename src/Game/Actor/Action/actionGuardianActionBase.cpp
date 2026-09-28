#include "Game/Actor/Action/actionGuardianActionBase.h"

namespace uking::action {

GuardianActionBase::GuardianActionBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianActionBase::~GuardianActionBase() = default;

bool GuardianActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianActionBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianActionBase::loadParams_() {}

void GuardianActionBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
