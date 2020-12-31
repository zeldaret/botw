#include "Game/AI/AI/aiSiteBossRecognizeRoot.h"

namespace uking::ai {

SiteBossRecognizeRoot::SiteBossRecognizeRoot(const InitArg& arg) : SiteBossRecognizeRootBase(arg) {}

SiteBossRecognizeRoot::~SiteBossRecognizeRoot() = default;

bool SiteBossRecognizeRoot::init_(sead::Heap* heap) {
    return SiteBossRecognizeRootBase::init_(heap);
}

void SiteBossRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRecognizeRootBase::enter_(params);
}

void SiteBossRecognizeRoot::leave_() {
    SiteBossRecognizeRootBase::leave_();
}

void SiteBossRecognizeRoot::loadParams_() {
    SiteBossRecognizeRootBase::loadParams_();
    getStaticParam(&mIgnoreWaprDistMax_s, "IgnoreWaprDistMax");
    getStaticParam(&mIsCheckChildDevice_s, "IsCheckChildDevice");
    getStaticParam(&mIgnoreWarpDistRetFromDamage_s, "IgnoreWarpDistRetFromDamage");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
}

}  // namespace uking::ai
