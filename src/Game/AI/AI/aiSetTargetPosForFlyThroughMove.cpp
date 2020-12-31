#include "Game/AI/AI/aiSetTargetPosForFlyThroughMove.h"

namespace uking::ai {

SetTargetPosForFlyThroughMove::SetTargetPosForFlyThroughMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SetTargetPosForFlyThroughMove::~SetTargetPosForFlyThroughMove() = default;

bool SetTargetPosForFlyThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForFlyThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SetTargetPosForFlyThroughMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForFlyThroughMove::loadParams_() {
    getStaticParam(&mTargetPosFixDist_s, "TargetPosFixDist");
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
