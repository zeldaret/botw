#include "Game/AI/Action/actionDummyAction.h"

namespace uking::action {

DummyAction::DummyAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void DummyAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DummyAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void DummyAction::loadParams_() {}

void DummyAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
