#include "Game/AI/AI/aiDistanceKeepMove.h"

namespace uking::ai {

DistanceKeepMove::DistanceKeepMove(const InitArg& arg) : WaitNearTarget(arg) {}

DistanceKeepMove::~DistanceKeepMove() = default;

bool DistanceKeepMove::init_(sead::Heap* heap) {
    return WaitNearTarget::init_(heap);
}

void DistanceKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitNearTarget::enter_(params);
}

void DistanceKeepMove::leave_() {
    WaitNearTarget::leave_();
}

void DistanceKeepMove::loadParams_() {
    WaitNearTarget::loadParams_();
    getStaticParam(&mStartBackDistOffset_s, "StartBackDistOffset");
}

}  // namespace uking::ai
