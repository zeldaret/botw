#include "Game/AI/Action/actionForkNoSlowTimer.h"

namespace uking::action {

ForkNoSlowTimer::ForkNoSlowTimer(const InitArg& arg) : ForkTimer(arg) {}

ForkNoSlowTimer::~ForkNoSlowTimer() = default;

bool ForkNoSlowTimer::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void ForkNoSlowTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkNoSlowTimer::leave_() {
    ForkTimer::leave_();
}

void ForkNoSlowTimer::loadParams_() {
    ForkTimer::loadParams_();
}

void ForkNoSlowTimer::calc_() {
    ForkTimer::calc_();
}

}  // namespace uking::action
