#include "Game/AI/Action/actionEventIncreasePorchItemAction.h"

namespace uking::action {

EventIncreasePorchItemAction::EventIncreasePorchItemAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreasePorchItemAction::~EventIncreasePorchItemAction() = default;

void EventIncreasePorchItemAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

}  // namespace uking::action
