#include "Game/AI/Action/actionGetOffFromHorseAction.h"

namespace uking::action {

GetOffFromHorseAction::GetOffFromHorseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetOffFromHorseAction::~GetOffFromHorseAction() = default;

bool GetOffFromHorseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetOffFromHorseAction::loadParams_() {
    getDynamicParam(&mClearDemoMemberIfNotOwned_d, "ClearDemoMemberIfNotOwned");
}

}  // namespace uking::action
