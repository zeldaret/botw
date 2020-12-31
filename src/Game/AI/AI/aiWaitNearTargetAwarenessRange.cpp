#include "Game/AI/AI/aiWaitNearTargetAwarenessRange.h"

namespace uking::ai {

WaitNearTargetAwarenessRange::WaitNearTargetAwarenessRange(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

WaitNearTargetAwarenessRange::~WaitNearTargetAwarenessRange() = default;

bool WaitNearTargetAwarenessRange::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitNearTargetAwarenessRange::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaitNearTargetAwarenessRange::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitNearTargetAwarenessRange::loadParams_() {
    getStaticParam(&mAddAwarenessRangeType_s, "AddAwarenessRangeType");
    getStaticParam(&mStartCloseDist_s, "StartCloseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mEndCloseDist_s, "EndCloseDist");
    getStaticParam(&mUseNavMeshRequest_s, "UseNavMeshRequest");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
