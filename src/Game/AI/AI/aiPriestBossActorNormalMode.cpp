#include "Game/AI/AI/aiPriestBossActorNormalMode.h"

namespace uking::ai {

PriestBossActorNormalMode::PriestBossActorNormalMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossActorNormalMode::~PriestBossActorNormalMode() = default;

bool PriestBossActorNormalMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossActorNormalMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossActorNormalMode::leave_() {
    PriestBossMode::leave_();
}

void PriestBossActorNormalMode::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mApproachWarpRate_s, "ApproachWarpRate");
    getStaticParam(&mApproachStartDistance_s, "ApproachStartDistance");
    getStaticParam(&mLeaveStartDistance_s, "LeaveStartDistance");
    getStaticParam(&mLeaveStartTime_s, "LeaveStartTime");
    getStaticParam(&mWaitMinTime_s, "WaitMinTime");
    getStaticParam(&mWaitMaxTime_s, "WaitMaxTime");
    getStaticParam(&mSecondHalfLifePercent_s, "SecondHalfLifePercent");
    getStaticParam(&mFramesRestrictEarthRelease_s, "FramesRestrictEarthRelease");
    getStaticParam(&mWarpPosDistFromPlayer_s, "WarpPosDistFromPlayer");
    getStaticParam(&mStageMarginRateForEarthRelease_s, "StageMarginRateForEarthRelease");
    getStaticParam(&mIsManagedBtlMgr_s, "IsManagedBtlMgr");
    getDynamicParam(&mFromSyncMode_d, "FromSyncMode");
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
