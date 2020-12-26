#include "Game/AI/Action/actionEventPlayUiOPTextAction.h"

namespace uking::action {

EventPlayUiOPTextAction::EventPlayUiOPTextAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiOPTextAction::~EventPlayUiOPTextAction() = default;

bool EventPlayUiOPTextAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOPTextAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiOPTextAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiOPTextAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mTextType_d, "TextType");
}

void EventPlayUiOPTextAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
