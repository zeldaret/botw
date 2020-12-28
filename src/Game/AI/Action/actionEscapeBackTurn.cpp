#include "Game/AI/Action/actionEscapeBackTurn.h"

namespace uking::action {

EscapeBackTurn::EscapeBackTurn(const InitArg& arg) : ActionEx(arg) {}

EscapeBackTurn::~EscapeBackTurn() = default;

void EscapeBackTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void EscapeBackTurn::leave_() {
    ActionEx::leave_();
}

void EscapeBackTurn::loadParams_() {}

void EscapeBackTurn::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
