#include "Game/AI/AI/aiForestGiantChanceWait.h"

namespace uking::ai {

ForestGiantChanceWait::ForestGiantChanceWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForestGiantChanceWait::~ForestGiantChanceWait() = default;

bool ForestGiantChanceWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantChanceWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForestGiantChanceWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForestGiantChanceWait::loadParams_() {
    getStaticParam(&mChanceRate_s, "ChanceRate");
    getStaticParam(&mCorrectRate_s, "CorrectRate");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
