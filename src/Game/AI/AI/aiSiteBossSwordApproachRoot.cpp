#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"

namespace uking::ai {

SiteBossSwordApproachRoot::SiteBossSwordApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordApproachRoot::~SiteBossSwordApproachRoot() = default;

bool SiteBossSwordApproachRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSwordApproachRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSwordApproachRoot::loadParams_() {
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveWidth_s, "MoveWidth");
    getStaticParam(&mBaseOffsetY_s, "BaseOffsetY");
    getStaticParam(&mPredictMoveFrame_s, "PredictMoveFrame");
    getStaticParam(&mIsCloseMove_s, "IsCloseMove");
    getStaticParam(&mIsPlayRunStartAS_s, "IsPlayRunStartAS");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mOldTargetPos_d, "OldTargetPos");
}

}  // namespace uking::ai
