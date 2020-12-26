#include "Game/AI/Action/actionMotorcycleRiddenByPlayer.h"

namespace uking::action {

MotorcycleRiddenByPlayer::MotorcycleRiddenByPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MotorcycleRiddenByPlayer::~MotorcycleRiddenByPlayer() = default;

bool MotorcycleRiddenByPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleRiddenByPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleRiddenByPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleRiddenByPlayer::loadParams_() {
    getStaticParam(&mCrashVelocityThreshold_s, "CrashVelocityThreshold");
    getStaticParam(&mRideOnDelayFrames_s, "RideOnDelayFrames");
    getStaticParam(&mFallThresholdForThrowOff_s, "FallThresholdForThrowOff");
    getStaticParam(&mCrashVelocityDeltaThreshold_s, "CrashVelocityDeltaThreshold");
    getStaticParam(&mChargeVelocityThreshold_s, "ChargeVelocityThreshold");
    getStaticParam(&mDriftCutGrassRange_s, "DriftCutGrassRange");
    getStaticParam(&mDriftCutGrassIntensity_s, "DriftCutGrassIntensity");
    getStaticParam(&mCutLowTreeVelocityThreshold_s, "CutLowTreeVelocityThreshold");
    getStaticParam(&mCutLowTreeVelocitySize_s, "CutLowTreeVelocitySize");
    getStaticParam(&mTerrorVelocityThreshold1_s, "TerrorVelocityThreshold1");
    getStaticParam(&mTerrorVelocityThreshold2_s, "TerrorVelocityThreshold2");
    getStaticParam(&mTerrorVelocityThreshold3_s, "TerrorVelocityThreshold3");
    getStaticParam(&mTerrorVelocityThreshold4_s, "TerrorVelocityThreshold4");
    getStaticParam(&mTerrorRadius_s, "TerrorRadius");
    getStaticParam(&mTerrorOffsetDistanceSec_s, "TerrorOffsetDistanceSec");
    getStaticParam(&mForbidSpinturnAngleRange_s, "ForbidSpinturnAngleRange");
    getStaticParam(&mPermitManualWheelieAngleRange_s, "PermitManualWheelieAngleRange");
    getStaticParam(&mAttackChargeBoneOffset_s, "AttackChargeBoneOffset");
}

void MotorcycleRiddenByPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
