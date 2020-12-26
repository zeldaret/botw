#include "Game/AI/Action/actionEventAddGameDataIntAction.h"

namespace uking::action {

EventAddGameDataIntAction::EventAddGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAddGameDataIntAction::~EventAddGameDataIntAction() = default;

bool EventAddGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAddGameDataIntAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAddGameDataIntAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAddGameDataIntAction::loadParams_() {
    getDynamicParam(&mIsSignInversion_d, "IsSignInversion");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
}

void EventAddGameDataIntAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
