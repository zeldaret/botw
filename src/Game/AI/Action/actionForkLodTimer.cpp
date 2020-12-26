#include "Game/AI/Action/actionForkLodTimer.h"

namespace uking::action {

ForkLodTimer::ForkLodTimer(const InitArg& arg) : Fork(arg) {}

ForkLodTimer::~ForkLodTimer() = default;

bool ForkLodTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkLodTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkLodTimer::leave_() {
    Fork::leave_();
}

void ForkLodTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
}

void ForkLodTimer::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
