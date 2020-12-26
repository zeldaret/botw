#include "Game/AI/Action/actionForkAlwaysForceGetUpWithOffset.h"

namespace uking::action {

ForkAlwaysForceGetUpWithOffset::ForkAlwaysForceGetUpWithOffset(const InitArg& arg)
    : ForkAlwaysForceGetUp(arg) {}

ForkAlwaysForceGetUpWithOffset::~ForkAlwaysForceGetUpWithOffset() = default;

bool ForkAlwaysForceGetUpWithOffset::init_(sead::Heap* heap) {
    return ForkAlwaysForceGetUp::init_(heap);
}

void ForkAlwaysForceGetUpWithOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysForceGetUp::enter_(params);
}

void ForkAlwaysForceGetUpWithOffset::leave_() {
    ForkAlwaysForceGetUp::leave_();
}

void ForkAlwaysForceGetUpWithOffset::loadParams_() {
    ForkAlwaysForceGetUp::loadParams_();
    getStaticParam(&mRotCenterPos_s, "RotCenterPos");
}

void ForkAlwaysForceGetUpWithOffset::calc_() {
    ForkAlwaysForceGetUp::calc_();
}

}  // namespace uking::action
