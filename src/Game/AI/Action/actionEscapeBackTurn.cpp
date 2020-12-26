#include "Game/AI/Action/actionEscapeBackTurn.h"

namespace uking::action {

EscapeBackTurn::EscapeBackTurn(const InitArg& arg) : ActionEx(arg) {}

EscapeBackTurn::~EscapeBackTurn() = default;

bool EscapeBackTurn::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

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
