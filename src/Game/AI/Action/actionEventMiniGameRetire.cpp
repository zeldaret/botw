#include "Game/AI/Action/actionEventMiniGameRetire.h"

namespace uking::action {

EventMiniGameRetire::EventMiniGameRetire(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameRetire::~EventMiniGameRetire() = default;

bool EventMiniGameRetire::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameRetire::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

}  // namespace uking::action
