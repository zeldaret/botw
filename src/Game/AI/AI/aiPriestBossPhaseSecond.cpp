#include "Game/AI/AI/aiPriestBossPhaseSecond.h"

namespace uking::ai {

PriestBossPhaseSecond::PriestBossPhaseSecond(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseSecond::~PriestBossPhaseSecond() = default;

bool PriestBossPhaseSecond::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseSecond::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseSecond::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseSecond::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mModeChangeLife_s, "ModeChangeLife");
    getStaticParam(&mSimAtkMax_s, "SimAtkMax");
    getStaticParam(&mBowEquipMax_s, "BowEquipMax");
    getStaticParam(&mSyncAtkMax_s, "SyncAtkMax");
    getStaticParam(&mModeChangeBlockTime_s, "ModeChangeBlockTime");
    getStaticParam(&mRespawnSpan_s, "RespawnSpan");
    getStaticParam(&mRespawnBaseSpace_s, "RespawnBaseSpace");
    getStaticParam(&mRespawnBaseMoveTime_s, "RespawnBaseMoveTime");
    getStaticParam(&mRespawnBaseInterval_s, "RespawnBaseInterval");
    getStaticParam(&mCircleFormRange_s, "CircleFormRange");
    getStaticParam(&mCircleFormRushWait_s, "CircleFormRushWait");
    getStaticParam(&mCircleFormRushInterval_s, "CircleFormRushInterval");
    getStaticParam(&mCircleFormShootWait_s, "CircleFormShootWait");
    getStaticParam(&mCircleFormShootInterval_s, "CircleFormShootInterval");
    getStaticParam(&mLineFormDistFromPlayer_s, "LineFormDistFromPlayer");
    getStaticParam(&mLineFormSpace_s, "LineFormSpace");
    getStaticParam(&mLineFormRushWait_s, "LineFormRushWait");
    getStaticParam(&mLineFormRushInterval_s, "LineFormRushInterval");
    getStaticParam(&mLineFormFallWait_s, "LineFormFallWait");
    getStaticParam(&mLineFormFallInterval_s, "LineFormFallInterval");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

}  // namespace uking::ai
