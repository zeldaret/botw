#include "Game/AI/Action/actionEventPlayUiScreenAction.h"

namespace uking::action {

EventPlayUiScreenAction::EventPlayUiScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiScreenAction::~EventPlayUiScreenAction() = default;

bool EventPlayUiScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiScreenAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiScreenAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiScreenAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mScreenName_d, "ScreenName");
}

void EventPlayUiScreenAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
