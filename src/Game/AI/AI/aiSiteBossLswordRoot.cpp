#include "Game/AI/AI/aiSiteBossLswordRoot.h"

namespace uking::ai {

SiteBossLswordRoot::SiteBossLswordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossLswordRoot::~SiteBossLswordRoot() = default;

bool SiteBossLswordRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossLswordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossLswordRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossLswordRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mFireBallAttackPower_s, "FireBallAttackPower");
    getStaticParam(&mFireBallMinDamage_s, "FireBallMinDamage");
    getStaticParam(&mBigFireBallAttackPower_s, "BigFireBallAttackPower");
    getStaticParam(&mBigFireBallMinDamage_s, "BigFireBallMinDamage");
    getStaticParam(&mWearFlameAttackPower_s, "WearFlameAttackPower");
    getStaticParam(&mWearFlameMinDamage_s, "WearFlameMinDamage");
    getStaticParam(&mBigFireBallScaleTime0_s, "BigFireBallScaleTime0");
    getStaticParam(&mBigFireBallScaleMax_s, "BigFireBallScaleMax");
    getStaticParam(&mBigFireBallScaleTime1_s, "BigFireBallScaleTime1");
    getStaticParam(&mBigFireBallMoveSpeed0_s, "BigFireBallMoveSpeed0");
    getStaticParam(&mBigFireBallMoveSpeed1_s, "BigFireBallMoveSpeed1");
    getStaticParam(&mBigFireBallPosOffset_s, "BigFireBallPosOffset");
    getStaticParam(&mBigFireBallRotOffset_s, "BigFireBallRotOffset");
}

}  // namespace uking::ai
