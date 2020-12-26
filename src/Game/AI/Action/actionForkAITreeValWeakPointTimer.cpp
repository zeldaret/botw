#include "Game/AI/Action/actionForkAITreeValWeakPointTimer.h"

namespace uking::action {

ForkAITreeValWeakPointTimer::ForkAITreeValWeakPointTimer(const InitArg& arg) : Fork(arg) {}

ForkAITreeValWeakPointTimer::~ForkAITreeValWeakPointTimer() = default;

bool ForkAITreeValWeakPointTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkAITreeValWeakPointTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkAITreeValWeakPointTimer::leave_() {
    Fork::leave_();
}

void ForkAITreeValWeakPointTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mTimer_s, "Timer");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
}

void ForkAITreeValWeakPointTimer::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
