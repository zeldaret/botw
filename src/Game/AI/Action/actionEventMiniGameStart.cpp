#include "Game/AI/Action/actionEventMiniGameStart.h"

namespace uking::action {

EventMiniGameStart::EventMiniGameStart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameStart::~EventMiniGameStart() = default;

bool EventMiniGameStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameStart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameStart::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameStart::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

void EventMiniGameStart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
