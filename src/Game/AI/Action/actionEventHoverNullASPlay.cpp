#include "Game/AI/Action/actionEventHoverNullASPlay.h"

namespace uking::action {

EventHoverNullASPlay::EventHoverNullASPlay(const InitArg& arg) : EventHoverNullASPlayBase(arg) {}

EventHoverNullASPlay::~EventHoverNullASPlay() = default;

bool EventHoverNullASPlay::init_(sead::Heap* heap) {
    return EventHoverNullASPlayBase::init_(heap);
}

void EventHoverNullASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    EventHoverNullASPlayBase::enter_(params);
}

void EventHoverNullASPlay::leave_() {
    EventHoverNullASPlayBase::leave_();
}

void EventHoverNullASPlay::loadParams_() {
    EventHoverNullASPlayBase::loadParams_();
}

void EventHoverNullASPlay::calc_() {
    EventHoverNullASPlayBase::calc_();
}

}  // namespace uking::action
