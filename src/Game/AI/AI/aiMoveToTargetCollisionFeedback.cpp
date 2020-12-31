#include "Game/AI/AI/aiMoveToTargetCollisionFeedback.h"

namespace uking::ai {

MoveToTargetCollisionFeedback::MoveToTargetCollisionFeedback(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MoveToTargetCollisionFeedback::~MoveToTargetCollisionFeedback() = default;

bool MoveToTargetCollisionFeedback::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveToTargetCollisionFeedback::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoveToTargetCollisionFeedback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveToTargetCollisionFeedback::loadParams_() {
    getStaticParam(&mCooldownFramesTargetAdjust_s, "CooldownFramesTargetAdjust");
    getStaticParam(&mFramesUntilRetryOriginalPos_s, "FramesUntilRetryOriginalPos");
    getStaticParam(&mIdealDepthMin_s, "IdealDepthMin");
    getStaticParam(&mIdealDepthMax_s, "IdealDepthMax");
    getStaticParam(&mIgnoreYComponentThreshold_s, "IgnoreYComponentThreshold");
    getStaticParam(&mUseMoveAwayFromPos_s, "UseMoveAwayFromPos");
    getStaticParam(&mRetryOriginalPos_s, "RetryOriginalPos");
    getStaticParam(&mIsAdjustDepthOnCollision_s, "IsAdjustDepthOnCollision");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveAwayFromPos_d, "MoveAwayFromPos");
}

}  // namespace uking::ai
