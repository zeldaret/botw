#include "Game/AI/Action/actionEventSetItemDataToPouch.h"

namespace uking::action {

EventSetItemDataToPouch::EventSetItemDataToPouch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetItemDataToPouch::~EventSetItemDataToPouch() = default;

bool EventSetItemDataToPouch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetItemDataToPouch::loadParams_() {
    getDynamicParam(&mSharpWeaponAddValue_d, "SharpWeaponAddValue");
    getDynamicParam(&mSharpWeaponAddType_d, "SharpWeaponAddType");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

}  // namespace uking::action
