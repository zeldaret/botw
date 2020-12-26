#include "Game/AI/Action/actionThrowLeft.h"

namespace uking::action {

ThrowLeft::ThrowLeft(const InitArg& arg) : Throw(arg) {}

ThrowLeft::~ThrowLeft() = default;

bool ThrowLeft::init_(sead::Heap* heap) {
    return Throw::init_(heap);
}

void ThrowLeft::enter_(ksys::act::ai::InlineParamPack* params) {
    Throw::enter_(params);
}

void ThrowLeft::leave_() {
    Throw::leave_();
}

void ThrowLeft::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void ThrowLeft::calc_() {
    Throw::calc_();
}

}  // namespace uking::action
