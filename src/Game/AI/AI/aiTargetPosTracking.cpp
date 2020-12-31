#include "Game/AI/AI/aiTargetPosTracking.h"

namespace uking::ai {

TargetPosTracking::TargetPosTracking(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosTracking::~TargetPosTracking() = default;

bool TargetPosTracking::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosTracking::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetPosTracking::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosTracking::loadParams_() {
    getStaticParam(&mTrackSpeed_s, "TrackSpeed");
    getStaticParam(&mIsStoppedByJustAvoid_s, "IsStoppedByJustAvoid");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
