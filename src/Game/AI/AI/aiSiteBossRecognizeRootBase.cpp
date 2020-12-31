#include "Game/AI/AI/aiSiteBossRecognizeRootBase.h"

namespace uking::ai {

SiteBossRecognizeRootBase::SiteBossRecognizeRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRecognizeRootBase::~SiteBossRecognizeRootBase() = default;

bool SiteBossRecognizeRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossRecognizeRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossRecognizeRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossRecognizeRootBase::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mAttackRandNum_s, "AttackRandNum");
    getStaticParam(&mWarpStartDist_s, "WarpStartDist");
    getStaticParam(&mForceWarpRetryDist_s, "ForceWarpRetryDist");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

}  // namespace uking::ai
