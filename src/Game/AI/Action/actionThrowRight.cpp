#include "Game/AI/Action/actionThrowRight.h"

namespace uking::action {

ThrowRight::ThrowRight(const InitArg& arg) : Throw(arg) {}

ThrowRight::~ThrowRight() = default;

bool ThrowRight::init_(sead::Heap* heap) {
    return Throw::init_(heap);
}

void ThrowRight::enter_(ksys::act::ai::InlineParamPack* params) {
    Throw::enter_(params);
}

void ThrowRight::leave_() {
    Throw::leave_();
}

void ThrowRight::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void ThrowRight::calc_() {
    Throw::calc_();
}

}  // namespace uking::action
