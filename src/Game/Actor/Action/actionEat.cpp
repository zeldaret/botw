#include "Game/Actor/Action/actionEat.h"

namespace uking::action {

Eat::Eat(const InitArg& arg) : StopBase(arg) {}

Eat::~Eat() = default;

void Eat::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Eat::leave_() {
    StopBase::leave_();
}

void Eat::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mIsHeal_s, "IsHeal");
}

void Eat::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
