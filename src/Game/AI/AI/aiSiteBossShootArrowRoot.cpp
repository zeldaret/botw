#include "Game/AI/AI/aiSiteBossShootArrowRoot.h"

namespace uking::ai {

SiteBossShootArrowRoot::SiteBossShootArrowRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossShootArrowRoot::~SiteBossShootArrowRoot() = default;

bool SiteBossShootArrowRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossShootArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossShootArrowRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossShootArrowRoot::loadParams_() {
    getStaticParam(&mChildDeviceMax_s, "ChildDeviceMax");
    getStaticParam(&mChildDeviceSupplyNum_s, "ChildDeviceSupplyNum");
    getStaticParam(&mChildDeviceSupplyInterval_s, "ChildDeviceSupplyInterval");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mArrowRainBaseDamage_s, "ArrowRainBaseDamage");
    getStaticParam(&mArrowRainAddDamage_s, "ArrowRainAddDamage");
    getStaticParam(&mAvoidCountMax_s, "AvoidCountMax");
    getStaticParam(&mSeqAvoidRate_s, "SeqAvoidRate");
    getStaticParam(&mUpDownAvoidRate_s, "UpDownAvoidRate");
    getStaticParam(&mPatternShiftFirstLifeRate_s, "PatternShiftFirstLifeRate");
    getStaticParam(&mPatternShiftSecondLifeRate_s, "PatternShiftSecondLifeRate");
    getStaticParam(&mPatternShiftThirdLifeRate_s, "PatternShiftThirdLifeRate");
    getStaticParam(&mCancelCreateTornadoHeight_s, "CancelCreateTornadoHeight");
    getStaticParam(&mAvoidAngle_s, "AvoidAngle");
    getStaticParam(&mAvoidLifeRate_s, "AvoidLifeRate");
    getStaticParam(&mAvoidDist_s, "AvoidDist");
    getStaticParam(&mAvoidDistRand_s, "AvoidDistRand");
    getStaticParam(&mAvoidWaitCount_s, "AvoidWaitCount");
    getStaticParam(&mAvoidWaitCountRand_s, "AvoidWaitCountRand");
    getStaticParam(&mTornadoCreateHeight_s, "TornadoCreateHeight");
    getStaticParam(&mNoWaitWarpAttackKey_s, "NoWaitWarpAttackKey");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
