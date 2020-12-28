#include "Game/AI/Action/actionEventMiniGameFinish.h"

namespace uking::action {

EventMiniGameFinish::EventMiniGameFinish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameFinish::~EventMiniGameFinish() = default;

bool EventMiniGameFinish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameFinish::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

}  // namespace uking::action
