#include "Game/AI/Action/actionDummyTriggerAction.h"

namespace uking::action {

DummyTriggerAction::DummyTriggerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DummyTriggerAction::~DummyTriggerAction() = default;

bool DummyTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DummyTriggerAction::loadParams_() {}

}  // namespace uking::action
