#include "Game/Actor/Action/actionEventHoverNullASPlay.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

EventHoverNullASPlay::EventHoverNullASPlay(const InitArg& arg) : EventNullASPlayBase(arg) {}

EventHoverNullASPlay::~EventHoverNullASPlay() = default;

bool EventHoverNullASPlay::init_(sead::Heap* heap) {
    return EventNullASPlayBase::init_(heap);
}

void EventHoverNullASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    EventNullASPlayBase::enter_(params);

    mCCAccessor.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::Hover);
}

void EventHoverNullASPlay::leave_() {
    resetAllMotion(mActor);

    EventNullASPlayBase::leave_();
}

void EventHoverNullASPlay::loadParams_() {
    EventNullASPlayBase::loadParams_();
}

void EventHoverNullASPlay::calc_() {
    EventNullASPlayBase::calc_();
}

}  // namespace uking::action
