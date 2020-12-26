#include "Game/AI/Action/actionEventMiniGameTimeMove.h"

namespace uking::action {

EventMiniGameTimeMove::EventMiniGameTimeMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTimeMove::~EventMiniGameTimeMove() = default;

bool EventMiniGameTimeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTimeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameTimeMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameTimeMove::loadParams_() {}

void EventMiniGameTimeMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
