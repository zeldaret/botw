#include "Game/AI/Action/actionEventMiniGameFinish.h"

namespace uking::action {

EventMiniGameFinish::EventMiniGameFinish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameFinish::~EventMiniGameFinish() = default;

bool EventMiniGameFinish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameFinish::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameFinish::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameFinish::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

void EventMiniGameFinish::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
