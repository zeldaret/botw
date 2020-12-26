#include "Game/AI/Action/actionEventSetItemDataToPouch.h"

namespace uking::action {

EventSetItemDataToPouch::EventSetItemDataToPouch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetItemDataToPouch::~EventSetItemDataToPouch() = default;

bool EventSetItemDataToPouch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetItemDataToPouch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetItemDataToPouch::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetItemDataToPouch::loadParams_() {
    getDynamicParam(&mSharpWeaponAddValue_d, "SharpWeaponAddValue");
    getDynamicParam(&mSharpWeaponAddType_d, "SharpWeaponAddType");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

void EventSetItemDataToPouch::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
