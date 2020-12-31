#include "Game/AI/AI/aiDistanceLostCheck.h"

namespace uking::ai {

DistanceLostCheck::DistanceLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DistanceLostCheck::~DistanceLostCheck() = default;

bool DistanceLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DistanceLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DistanceLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DistanceLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mAddAwarenessRangeType_s, "AddAwarenessRangeType");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
