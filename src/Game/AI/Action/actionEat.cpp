#include "Game/AI/Action/actionEat.h"

namespace uking::action {

Eat::Eat(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Eat::~Eat() = default;

void Eat::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Eat::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Eat::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsHeal_s, "IsHeal");
}

void Eat::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
