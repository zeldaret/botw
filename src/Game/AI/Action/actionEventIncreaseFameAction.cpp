#include "Game/AI/Action/actionEventIncreaseFameAction.h"

namespace uking::action {

EventIncreaseFameAction::EventIncreaseFameAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void EventIncreaseFameAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
