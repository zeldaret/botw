#include "Game/AI/Action/actionWarn.h"

namespace uking::action {

Warn::Warn(const InitArg& arg) : StopASPlay(arg) {}

Warn::~Warn() = default;

bool Warn::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void Warn::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
}

void Warn::leave_() {
    StopASPlay::leave_();
}

void Warn::loadParams_() {
    StopASPlay::loadParams_();
}

void Warn::calc_() {
    StopASPlay::calc_();
}

}  // namespace uking::action
