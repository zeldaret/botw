#include "Game/AI/Action/actionForkGanonBeastWeakPoint.h"

namespace uking::action {

ForkGanonBeastWeakPoint::ForkGanonBeastWeakPoint(const InitArg& arg) : Fork(arg) {}

ForkGanonBeastWeakPoint::~ForkGanonBeastWeakPoint() = default;

bool ForkGanonBeastWeakPoint::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkGanonBeastWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkGanonBeastWeakPoint::leave_() {
    Fork::leave_();
}

void ForkGanonBeastWeakPoint::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mTargetSlotIdx_s, "TargetSlotIdx");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
}

void ForkGanonBeastWeakPoint::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
