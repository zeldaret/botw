#include "Game/AI/Action/actionEventPlayUiBossHpAction.h"

namespace uking::action {

EventPlayUiBossHpAction::EventPlayUiBossHpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiBossHpAction::~EventPlayUiBossHpAction() = default;

bool EventPlayUiBossHpAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiBossHpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiBossHpAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiBossHpAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
}

void EventPlayUiBossHpAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
