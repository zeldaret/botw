#include "Game/AI/Action/actionDummyTriggerAction.h"

namespace uking::action {

DummyTriggerAction::DummyTriggerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DummyTriggerAction::~DummyTriggerAction() = default;

bool DummyTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DummyTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DummyTriggerAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void DummyTriggerAction::loadParams_() {}

void DummyTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
