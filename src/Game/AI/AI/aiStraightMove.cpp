#include "Game/AI/AI/aiStraightMove.h"

namespace uking::ai {

StraightMove::StraightMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StraightMove::~StraightMove() = default;

bool StraightMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StraightMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StraightMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StraightMove::loadParams_() {
    getStaticParam(&mAngleLimit_s, "AngleLimit");
    getStaticParam(&mDistanceMax_s, "DistanceMax");
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mRetryAngleMax_s, "RetryAngleMax");
    getStaticParam(&mRetryAngleMin_s, "RetryAngleMin");
    getStaticParam(&mIsRetryMove_s, "IsRetryMove");
}

}  // namespace uking::ai
