#include "Game/AI/Action/actionEventBgmStartAction.h"

namespace uking::action {

EventBgmStartAction::EventBgmStartAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStartAction::~EventBgmStartAction() = default;

bool EventBgmStartAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStartAction::loadParams_() {
    getDynamicParam(&mBgmName_d, "BgmName");
}

}  // namespace uking::action
