#include "Game/AI/AI/aiPlayerRideHorse.h"

namespace uking::ai {

PlayerRideHorse::PlayerRideHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerRideHorse::~PlayerRideHorse() = default;

bool PlayerRideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerRideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerRideHorse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerRideHorse::loadParams_() {
    getStaticParam(&mDoForbidTime_s, "DoForbidTime");
    getStaticParam(&mThrowPowerY_s, "ThrowPowerY");
    getStaticParam(&mThrowPowerF_s, "ThrowPowerF");
    getStaticParam(&mBackDismountSpeed_s, "BackDismountSpeed");
    getStaticParam(&mWaistAngleApplyRateFoward_s, "WaistAngleApplyRateFoward");
    getStaticParam(&mWaistAngleApplyRateBack_s, "WaistAngleApplyRateBack");
    getStaticParam(&mMoveNoise_s, "MoveNoise");
    getStaticParam(&mSwordAttackNoise_s, "SwordAttackNoise");
    getStaticParam(&mAimAngleAddApplyAngle_s, "AimAngleAddApplyAngle");
    getStaticParam(&mAimAngleAdd_s, "AimAngleAdd");
    getStaticParam(&mAimAngleAddApplySpeed_s, "AimAngleAddApplySpeed");
    getStaticParam(&mLowerAngleWaitTime_s, "LowerAngleWaitTime");
    getDynamicParam(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
    getStaticParam(&mLynelRodeoCutNum_s, "LynelRodeoCutNum");
}

}  // namespace uking::ai
