#include "Game/AI/Action/actionUnarmedAttack.h"

namespace uking::action {

UnarmedAttack::UnarmedAttack(const InitArg& arg) : ActionEx(arg) {}

UnarmedAttack::~UnarmedAttack() = default;

void UnarmedAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void UnarmedAttack::leave_() {
    ActionEx::leave_();
}

void UnarmedAttack::loadParams_() {}

void UnarmedAttack::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
