#include "Game/AI/Action/actionEventBgmStopAction.h"

namespace uking::action {

EventBgmStopAction::EventBgmStopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStopAction::~EventBgmStopAction() = default;

bool EventBgmStopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStopAction::loadParams_() {
    getDynamicParam(&mFadeSec_d, "FadeSec");
    getDynamicParam(&mBgmName_d, "BgmName");
}

}  // namespace uking::action
