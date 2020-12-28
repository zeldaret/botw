#include "Game/AI/Action/actionEventBgmCtrlAction.h"

namespace uking::action {

EventBgmCtrlAction::EventBgmCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmCtrlAction::~EventBgmCtrlAction() = default;

bool EventBgmCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmCtrlAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

}  // namespace uking::action
