#include "Game/AI/AI/aiPlayerNormal.h"

namespace uking::ai {

PlayerNormal::PlayerNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerNormal::~PlayerNormal() = default;

bool PlayerNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerNormal::loadParams_() {
    getStaticParam(&mEquipNoiseValue_s, "EquipNoiseValue");
    getStaticParam(&mAttackNoiseValue_s, "AttackNoiseValue");
    getStaticParam(&mArrowReadyNoiseValue_s, "ArrowReadyNoiseValue");
    getStaticParam(&mParashawlInvalidHeight_s, "ParashawlInvalidHeight");
    getStaticParam(&mParashawlInvalidHeightSurfing_s, "ParashawlInvalidHeightSurfing");
    getStaticParam(&mForceSlipSpeed_s, "ForceSlipSpeed");
    getStaticParam(&mDoForbidTime_s, "DoForbidTime");
    getStaticParam(&mNoRideJumpDiffY_s, "NoRideJumpDiffY");
    getStaticParam(&mDashUpEnableSpeed_s, "DashUpEnableSpeed");
    getStaticParam(&mEnergyPerChargeLv_s, "EnergyPerChargeLv");
    getStaticParam(&mEnergyChargeStart_s, "EnergyChargeStart");
    getStaticParam(&mWallSlipEnableSpeed_s, "WallSlipEnableSpeed");
    getStaticParam(&mCutAddSpeedRate_s, "CutAddSpeedRate");
    getStaticParam(&mCutAddSpeedMax_s, "CutAddSpeedMax");
    getStaticParam(&mCutAddSpeedDec_s, "CutAddSpeedDec");
    getStaticParam(&mHorseCallTime_s, "HorseCallTime");
    getStaticParam(&mSwordSearchAngle_s, "SwordSearchAngle");
    getStaticParam(&mDoClimbForbidTime_s, "DoClimbForbidTime");
    getStaticParam(&mDoClimbForbidAngVel_s, "DoClimbForbidAngVel");
    getStaticParam(&mInWaterTimeForRagdoll_s, "InWaterTimeForRagdoll");
    getStaticParam(&mToFallHeightForJustRush_s, "ToFallHeightForJustRush");
}

}  // namespace uking::ai
