#include "Game/AI/Action/actionEventPlayUiOneTimeAnimAction.h"

namespace uking::action {

EventPlayUiOneTimeAnimAction::EventPlayUiOneTimeAnimAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventPlayUiOneTimeAnimAction::~EventPlayUiOneTimeAnimAction() = default;

bool EventPlayUiOneTimeAnimAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOneTimeAnimAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiOneTimeAnimAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiOneTimeAnimAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mScreenName_d, "ScreenName");
    getDynamicParam(&mAnimName_d, "AnimName");
}

void EventPlayUiOneTimeAnimAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
