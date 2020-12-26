#include "Game/AI/Action/actionEventAutoSaveAction.h"

namespace uking::action {

EventAutoSaveAction::EventAutoSaveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAutoSaveAction::~EventAutoSaveAction() = default;

bool EventAutoSaveAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAutoSaveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAutoSaveAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAutoSaveAction::loadParams_() {}

void EventAutoSaveAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
