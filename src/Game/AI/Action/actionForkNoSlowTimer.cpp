#include "Game/AI/Action/actionForkNoSlowTimer.h"

namespace uking::action {

ForkNoSlowTimer::ForkNoSlowTimer(const InitArg& arg) : ForkTimer(arg) {}

ForkNoSlowTimer::~ForkNoSlowTimer() = default;

bool ForkNoSlowTimer::init_(sead::Heap* heap) {
    return ForkTimerBase::init_(heap);  // NOLINT(bugprone-parent-virtual-call)
}

void ForkNoSlowTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkNoSlowTimer::leave_() {
    ForkTimerBase::leave_();  // NOLINT(bugprone-parent-virtual-call)
}

void ForkNoSlowTimer::loadParams_() {
    ForkTimer::loadParams_();
}

void ForkNoSlowTimer::calc_() {
    ForkTimer::calc_();
}

}  // namespace uking::action
