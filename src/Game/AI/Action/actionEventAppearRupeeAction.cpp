#include "Game/AI/Action/actionEventAppearRupeeAction.h"

namespace uking::action {

EventAppearRupeeAction::EventAppearRupeeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void EventAppearRupeeAction::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
}

}  // namespace uking::action
