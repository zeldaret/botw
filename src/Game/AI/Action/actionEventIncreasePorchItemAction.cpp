#include "Game/AI/Action/actionEventIncreasePorchItemAction.h"

namespace uking::action {

EventIncreasePorchItemAction::EventIncreasePorchItemAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreasePorchItemAction::~EventIncreasePorchItemAction() = default;

bool EventIncreasePorchItemAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventIncreasePorchItemAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventIncreasePorchItemAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventIncreasePorchItemAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void EventIncreasePorchItemAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
