#include "Game/AI/AI/aiSiteBossLswordFireBallRoot.h"

namespace uking::ai {

SiteBossLswordFireBallRoot::SiteBossLswordFireBallRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossLswordFireBallRoot::~SiteBossLswordFireBallRoot() = default;

bool SiteBossLswordFireBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossLswordFireBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossLswordFireBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossLswordFireBallRoot::loadParams_() {
    getStaticParam(&mPredictPosRate_s, "PredictPosRate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mYOffset_s, "YOffset");
    getStaticParam(&mIsThrowChildDevice_s, "IsThrowChildDevice");
    getStaticParam(&mIsNeedCreateChildDevice_s, "IsNeedCreateChildDevice");
    getStaticParam(&mBindPosOffset_s, "BindPosOffset");
    getDynamicParam(&mThrowActorName_d, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
