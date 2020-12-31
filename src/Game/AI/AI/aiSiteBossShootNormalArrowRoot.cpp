#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"

namespace uking::ai {

SiteBossShootNormalArrowRoot::SiteBossShootNormalArrowRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossShootNormalArrowRoot::~SiteBossShootNormalArrowRoot() = default;

bool SiteBossShootNormalArrowRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossShootNormalArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossShootNormalArrowRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossShootNormalArrowRoot::loadParams_() {
    getStaticParam(&mArrowNum_s, "ArrowNum");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mAvoidCountMax_s, "AvoidCountMax");
    getStaticParam(&mSeqAvoidRate_s, "SeqAvoidRate");
    getStaticParam(&mUpDownAvoidRate_s, "UpDownAvoidRate");
    getStaticParam(&mHoldTime_s, "HoldTime");
    getStaticParam(&mInitHoldTime_s, "InitHoldTime");
    getStaticParam(&mAvoidLifeRate_s, "AvoidLifeRate");
    getStaticParam(&mAvoidAngle_s, "AvoidAngle");
    getStaticParam(&mAvoidDist_s, "AvoidDist");
    getStaticParam(&mAvoidDistRand_s, "AvoidDistRand");
    getStaticParam(&mAvoidWaitCount_s, "AvoidWaitCount");
    getStaticParam(&mAvoidWaitCountRand_s, "AvoidWaitCountRand");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mTrigEventAtHold_s, "TrigEventAtHold");
    getStaticParam(&mSpineControlOffsetAngleLR_s, "SpineControlOffsetAngleLR");
    getStaticParam(&mSpineControlOffsetAngleUD_s, "SpineControlOffsetAngleUD");
    getStaticParam(&mIsFinishAtNoDevice_s, "IsFinishAtNoDevice");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mIsKeepDistance_s, "IsKeepDistance");
    getStaticParam(&mArrowName_s, "ArrowName");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
