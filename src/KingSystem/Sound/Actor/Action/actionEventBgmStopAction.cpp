#include "KingSystem/Sound/Actor/Action/actionEventBgmStopAction.h"

namespace ksys::snd {

EventBgmStopAction::EventBgmStopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStopAction::~EventBgmStopAction() = default;

bool EventBgmStopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStopAction::loadParams_() {
    getDynamicParam(&mFadeSec_d, "FadeSec");
    getDynamicParam(&mBgmName_d, "BgmName");
}

}  // namespace ksys::snd
