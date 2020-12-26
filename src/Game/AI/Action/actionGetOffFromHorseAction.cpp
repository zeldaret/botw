#include "Game/AI/Action/actionGetOffFromHorseAction.h"

namespace uking::action {

GetOffFromHorseAction::GetOffFromHorseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetOffFromHorseAction::~GetOffFromHorseAction() = default;

bool GetOffFromHorseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetOffFromHorseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GetOffFromHorseAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetOffFromHorseAction::loadParams_() {
    getDynamicParam(&mClearDemoMemberIfNotOwned_d, "ClearDemoMemberIfNotOwned");
}

void GetOffFromHorseAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
