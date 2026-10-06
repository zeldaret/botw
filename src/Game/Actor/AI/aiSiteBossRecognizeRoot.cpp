#include "Game/Actor/AI/aiSiteBossRecognizeRoot.h"

namespace uking::ai {

SiteBossRecognizeRoot::SiteBossRecognizeRoot(const InitArg& arg) : LastBossRecognizeRoot(arg) {}

SiteBossRecognizeRoot::~SiteBossRecognizeRoot() = default;

bool SiteBossRecognizeRoot::init_(sead::Heap* heap) {
    return LastBossRecognizeRoot::init_(heap);
}

void SiteBossRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossRecognizeRoot::enter_(params);
}

void SiteBossRecognizeRoot::leave_() {
    LastBossRecognizeRoot::leave_();
}

void SiteBossRecognizeRoot::loadParams_() {
    LastBossRecognizeRoot::loadParams_();
    getStaticParam(&mIgnoreWaprDistMax_s, "IgnoreWaprDistMax");
    getStaticParam(&mIsCheckChildDevice_s, "IsCheckChildDevice");
    getStaticParam(&mIgnoreWarpDistRetFromDamage_s, "IgnoreWarpDistRetFromDamage");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
}

}  // namespace uking::ai
