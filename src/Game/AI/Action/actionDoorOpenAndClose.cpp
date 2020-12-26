#include "Game/AI/Action/actionDoorOpenAndClose.h"

namespace uking::action {

DoorOpenAndClose::DoorOpenAndClose(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DoorOpenAndClose::~DoorOpenAndClose() = default;

bool DoorOpenAndClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DoorOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DoorOpenAndClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void DoorOpenAndClose::loadParams_() {
    getDynamicParam(&mDynASKey_d, "DynASKey");
    getDynamicParam(&mDynOwner_d, "DynOwner");
}

void DoorOpenAndClose::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
