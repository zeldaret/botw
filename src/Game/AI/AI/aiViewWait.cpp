#include "Game/AI/AI/aiViewWait.h"

namespace uking::ai {

ViewWait::ViewWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewWait::~ViewWait() = default;

void ViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ViewWait::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
