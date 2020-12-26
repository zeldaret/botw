#include "Game/AI/Action/actionUnarmedAttack.h"

namespace uking::action {

UnarmedAttack::UnarmedAttack(const InitArg& arg) : ActionEx(arg) {}

UnarmedAttack::~UnarmedAttack() = default;

bool UnarmedAttack::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

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
