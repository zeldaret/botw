#include "Game/AI/Action/actionActionEx.h"

namespace uking::action {

ActionEx::ActionEx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActionEx::~ActionEx() = default;

bool ActionEx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActionEx::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ActionEx::leave_() {
    ksys::act::ai::Action::leave_();
}

void ActionEx::loadParams_() {}

void ActionEx::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
