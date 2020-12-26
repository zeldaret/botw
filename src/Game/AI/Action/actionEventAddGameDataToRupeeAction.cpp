#include "Game/AI/Action/actionEventAddGameDataToRupeeAction.h"

namespace uking::action {

EventAddGameDataToRupeeAction::EventAddGameDataToRupeeAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAddGameDataToRupeeAction::~EventAddGameDataToRupeeAction() = default;

bool EventAddGameDataToRupeeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAddGameDataToRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAddGameDataToRupeeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAddGameDataToRupeeAction::loadParams_() {
    getDynamicParam(&mIsSignInversion_d, "IsSignInversion");
    getDynamicParam(&mGameDataIntAddValueName_d, "GameDataIntAddValueName");
}

void EventAddGameDataToRupeeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
