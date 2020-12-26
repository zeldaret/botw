#include "Game/AI/Action/actionUnarmedLargeAttack.h"

namespace uking::action {

UnarmedLargeAttack::UnarmedLargeAttack(const InitArg& arg) : UnarmedAttack(arg) {}

UnarmedLargeAttack::~UnarmedLargeAttack() = default;

bool UnarmedLargeAttack::init_(sead::Heap* heap) {
    return UnarmedAttack::init_(heap);
}

void UnarmedLargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedAttack::enter_(params);
}

void UnarmedLargeAttack::leave_() {
    UnarmedAttack::leave_();
}

void UnarmedLargeAttack::loadParams_() {}

void UnarmedLargeAttack::calc_() {
    UnarmedAttack::calc_();
}

}  // namespace uking::action
