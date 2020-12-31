#include "Game/AI/AI/aiSiteBossLswordAttackRoot.h"

namespace uking::ai {

SiteBossLswordAttackRoot::SiteBossLswordAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossLswordAttackRoot::~SiteBossLswordAttackRoot() = default;

bool SiteBossLswordAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossLswordAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossLswordAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossLswordAttackRoot::loadParams_() {
    getStaticParam(&mHighSlashRate_s, "HighSlashRate");
    getStaticParam(&mWhirlSlashRate_s, "WhirlSlashRate");
    getStaticParam(&mFireBallRate_s, "FireBallRate");
    getStaticParam(&mCrossSlashRate_s, "CrossSlashRate");
    getStaticParam(&mTornadoAttackRate_s, "TornadoAttackRate");
    getStaticParam(&mChemicalPlusHPRate_s, "ChemicalPlusHPRate");
    getStaticParam(&mIsFarDist_s, "IsFarDist");
    getStaticParam(&mPatternShiftFirstLifeRate_s, "PatternShiftFirstLifeRate");
    getStaticParam(&mReturnWaitCount_s, "ReturnWaitCount");
    getStaticParam(&mForceApproachCount_s, "ForceApproachCount");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
}

}  // namespace uking::ai
