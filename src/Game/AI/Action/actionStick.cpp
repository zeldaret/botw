#include "Game/AI/Action/actionStick.h"

namespace uking::action {

Stick::Stick(const InitArg& arg) : ActionEx(arg) {}

Stick::~Stick() = default;

void Stick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Stick::leave_() {
    ActionEx::leave_();
}

void Stick::loadParams_() {}

void Stick::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
