#include "Game/AI/Action/actionEventMiniGameRetire.h"

namespace uking::action {

EventMiniGameRetire::EventMiniGameRetire(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameRetire::~EventMiniGameRetire() = default;

bool EventMiniGameRetire::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameRetire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameRetire::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameRetire::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

void EventMiniGameRetire::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
