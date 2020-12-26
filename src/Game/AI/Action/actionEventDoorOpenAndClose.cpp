#include "Game/AI/Action/actionEventDoorOpenAndClose.h"

namespace uking::action {

EventDoorOpenAndClose::EventDoorOpenAndClose(const InitArg& arg) : DoorOpenAndClose(arg) {}

EventDoorOpenAndClose::~EventDoorOpenAndClose() = default;

bool EventDoorOpenAndClose::init_(sead::Heap* heap) {
    return DoorOpenAndClose::init_(heap);
}

void EventDoorOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    DoorOpenAndClose::enter_(params);
}

void EventDoorOpenAndClose::leave_() {
    DoorOpenAndClose::leave_();
}

void EventDoorOpenAndClose::loadParams_() {
    DoorOpenAndClose::loadParams_();
    getDynamicParam(&mDynIsOpenToInside_d, "DynIsOpenToInside");
    getDynamicParam(&mDynIsOpen_d, "DynIsOpen");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

void EventDoorOpenAndClose::calc_() {
    DoorOpenAndClose::calc_();
}

}  // namespace uking::action
