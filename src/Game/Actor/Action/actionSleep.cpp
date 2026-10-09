#include "Game/Actor/Action/actionSleep.h"

namespace uking::action {

Sleep::Sleep(const InitArg& arg) : StopBase(arg) {}

Sleep::~Sleep() = default;

bool Sleep::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Sleep::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Sleep::leave_() {
    StopBase::leave_();
}

void Sleep::loadParams_() {
    StopBase::loadParams_();
}

void Sleep::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
