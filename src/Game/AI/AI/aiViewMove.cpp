#include "Game/AI/AI/aiViewMove.h"

namespace uking::ai {

ViewMove::ViewMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewMove::~ViewMove() = default;

bool ViewMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ViewMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewMove::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
