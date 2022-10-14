#include "Game/AI/Action/actionEventHoverNullASPlay.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

EventHoverNullASPlay::EventHoverNullASPlay(const InitArg& arg) : EventHoverNullASPlayBase(arg) {}

EventHoverNullASPlay::~EventHoverNullASPlay() = default;

bool EventHoverNullASPlay::init_(sead::Heap* heap) {
    return EventHoverNullASPlayBase::init_(heap);
}

void EventHoverNullASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    EventHoverNullASPlayBase::enter_(params);

    mCCAccessor.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::Hover);
}

void EventHoverNullASPlay::leave_() {
    resetAllMotion(mActor);

    EventHoverNullASPlayBase::leave_();
}

void EventHoverNullASPlay::loadParams_() {
    EventHoverNullASPlayBase::loadParams_();
}

void EventHoverNullASPlay::calc_() {
    EventHoverNullASPlayBase::calc_();
}

}  // namespace uking::action
