#include "Game/AI/Action/actionForkDisableContactForAttack.h"

namespace uking::action {

ForkDisableContactForAttack::ForkDisableContactForAttack(const InitArg& arg)
    : ForkDisableContact(arg) {}

ForkDisableContactForAttack::~ForkDisableContactForAttack() = default;

bool ForkDisableContactForAttack::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactForAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactForAttack::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactForAttack::loadParams_() {
    ForkDisableContact::loadParams_();
}

void ForkDisableContactForAttack::calc_() {
    ForkDisableContact::calc_();
}

}  // namespace uking::action
