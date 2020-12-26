#include "Game/AI/Action/actionEventCheckAndCreateEquip.h"

namespace uking::action {

EventCheckAndCreateEquip::EventCheckAndCreateEquip(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCheckAndCreateEquip::~EventCheckAndCreateEquip() = default;

bool EventCheckAndCreateEquip::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCheckAndCreateEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventCheckAndCreateEquip::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCheckAndCreateEquip::loadParams_() {
    getDynamicParam(&mSharpWeaponAddValue_d, "SharpWeaponAddValue");
    getDynamicParam(&mSharpWeaponAddType_d, "SharpWeaponAddType");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

void EventCheckAndCreateEquip::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
