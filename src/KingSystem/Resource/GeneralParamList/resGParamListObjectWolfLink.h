#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectWolfLink : public GParamListObject {
public:
    GParamListObjectWolfLink();
    const char* getName() const override { return "WolfLink"; }

    agl::utl::Parameter<f32> mNeckSpeedWait;
    agl::utl::Parameter<f32> mNeckRateWait;
    agl::utl::Parameter<f32> mNeckSpeedShiekSensor;
    agl::utl::Parameter<f32> mNeckRateShiekSensor;
    agl::utl::Parameter<f32> mNeckSpeedFollow;
    agl::utl::Parameter<f32> mNeckRateFollow;
    agl::utl::Parameter<f32> mNeckSpeedBattle;
    agl::utl::Parameter<f32> mNeckRateBattle;
    agl::utl::Parameter<f32> mNeckSpeedHeal;
    agl::utl::Parameter<f32> mNeckRateHeal;
    agl::utl::Parameter<f32> mBattleRange;
    agl::utl::Parameter<f32> mHealRange;
    agl::utl::Parameter<f32> mHuntRange;
    agl::utl::Parameter<f32> mHowlRange;
    agl::utl::Parameter<f32> mMaxHeightAttackable;
    agl::utl::Parameter<f32> mMaxHeightHealable;
    agl::utl::Parameter<f32> mNavMeshSearchRadius;
    agl::utl::Parameter<f32> mCanReachPlayerNavMeshSearchRadius;
    agl::utl::Parameter<f32> mSubmergedDepth;
    agl::utl::Parameter<f32> mUtilityLifeToHunt;
    agl::utl::Parameter<f32> mUtilityDangerDistMin;
    agl::utl::Parameter<f32> mUtilityDangerDistMax;
    agl::utl::Parameter<f32> mUtilityConstant;
    agl::utl::Parameter<f32> mChainAttackChargeMin;
    agl::utl::Parameter<f32> mChainAttackChargeMax;
    agl::utl::Parameter<f32> mLookAtCooldownWait;
    agl::utl::Parameter<f32> mLookAtCooldownWaitRand;
    agl::utl::Parameter<f32> mLookAtCounterWait;
    agl::utl::Parameter<f32> mLookAtCounterWaitRand;
    agl::utl::Parameter<f32> mLookAtCooldownRun;
    agl::utl::Parameter<f32> mLookAtCooldownRunRand;
    agl::utl::Parameter<f32> mLookAtCounterRun;
    agl::utl::Parameter<f32> mLookAtCounterRunRand;
    agl::utl::Parameter<f32> mAttackCounterLength;
    agl::utl::Parameter<f32> mAttackCounterRand;
    agl::utl::Parameter<f32> mHowlCooldownCounterLength;
    agl::utl::Parameter<f32> mHowlCooldownCounterRand;
    agl::utl::Parameter<f32> mHealCooldownCounterLength;
    agl::utl::Parameter<f32> mHealCooldownCounterRand;
    agl::utl::Parameter<f32> mFailPathCooldownCounterLength;
    agl::utl::Parameter<f32> mFailPathCooldownCounterRand;
    agl::utl::Parameter<f32> mRetargetCooldownCounterLength;
    agl::utl::Parameter<f32> mRetargetCooldownCounterRand;
    agl::utl::Parameter<f32> mAfterTargetDeathCounterLength;
    agl::utl::Parameter<f32> mAfterTargetDeathCounterRand;
    agl::utl::Parameter<f32> mLostTargetCounterLength;
    agl::utl::Parameter<f32> mLostTargetCounterRand;
    agl::utl::Parameter<f32> mInvinceableCounterLength;
    agl::utl::Parameter<f32> mInvinceableCounterRand;
    agl::utl::Parameter<f32> mCallDelayMinLength;
    agl::utl::Parameter<f32> mCallOverrideCounterLength;
    agl::utl::Parameter<f32> mGiveUpShiekSensorLength;
    agl::utl::Parameter<f32> mRetryShiekSensorLength;
    agl::utl::Parameter<f32> mBattleWallHitLength;
    agl::utl::Parameter<f32> mFollowRetryLength;
    agl::utl::Parameter<f32> mPowerUpFoodLength;
    agl::utl::Parameter<f32> mSafePosFailCounter;
    agl::utl::Parameter<f32> mRestrictedTargetTimeNormal;
    agl::utl::Parameter<f32> mRestrictedTargetTimeSpecial;
    agl::utl::Parameter<s32> mPowerUpFoodAttackMod;
    agl::utl::Parameter<f32> mPowerUpFoodChainAttackCharge;
    agl::utl::Parameter<s32> mVSStalfosCritChance;
    agl::utl::Parameter<f32> mAttackBase;
    agl::utl::Parameter<f32> mAttackHeartMod;
    agl::utl::Parameter<f32> mDefenseBase;
    agl::utl::Parameter<f32> mDefenseHeartMod;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectWolfLink, 0x878);

inline GParamListObjectWolfLink::GParamListObjectWolfLink() {
    auto* const obj = &mObj;

    mNeckSpeedWait.init(0.025, "NeckSpeedWait", "", obj);
    mNeckRateWait.init(0.7, "NeckRateWait", "", obj);
    mNeckSpeedShiekSensor.init(0.1, "NeckSpeedShiekSensor", "", obj);
    mNeckRateShiekSensor.init(0.45, "NeckRateShiekSensor", "", obj);
    mNeckSpeedFollow.init(0.4, "NeckSpeedFollow", "", obj);
    mNeckRateFollow.init(0.45, "NeckRateFollow", "", obj);
    mNeckSpeedBattle.init(0.3, "NeckSpeedBattle", "", obj);
    mNeckRateBattle.init(0.45, "NeckRateBattle", "", obj);
    mNeckSpeedHeal.init(0.0, "NeckSpeedHeal", "", obj);
    mNeckRateHeal.init(0.1, "NeckRateHeal", "", obj);
    mBattleRange.init(30.0, "BattleRange", "", obj);
    mHealRange.init(30.0, "HealRange", "", obj);
    mHuntRange.init(30.0, "HuntRange", "", obj);
    mHowlRange.init(60.0, "HowlRange", "", obj);
    mMaxHeightAttackable.init(1.6, "MaxHeightAttackable", "", obj);
    mMaxHeightHealable.init(1.5, "MaxHeightHealable", "", obj);
    mNavMeshSearchRadius.init(6.0, "NavMeshSearchRadius", "", obj);
    mCanReachPlayerNavMeshSearchRadius.init(2.0, "CanReachPlayerNavMeshSearchRadius", "", obj);
    mSubmergedDepth.init(1.0, "SubmergedDepth", "", obj);
    mUtilityLifeToHunt.init(0.3, "UtilityLifeToHunt", "", obj);
    mUtilityDangerDistMin.init(5.0, "UtilityDangerDistMin", "", obj);
    mUtilityDangerDistMax.init(20.0, "UtilityDangerDistMax", "", obj);
    mUtilityConstant.init(0.1, "UtilityConstant", "", obj);
    mChainAttackChargeMin.init(7.0, "ChainAttackChargeMin", "", obj);
    mChainAttackChargeMax.init(10.0, "ChainAttackChargeMax", "", obj);
    mLookAtCooldownWait.init(150.0, "LookAtCooldownWait", "", obj);
    mLookAtCooldownWaitRand.init(60.0, "LookAtCooldownWaitRand", "", obj);
    mLookAtCounterWait.init(10.0, "LookAtCounterWait", "", obj);
    mLookAtCounterWaitRand.init(40.0, "LookAtCounterWaitRand", "", obj);
    mLookAtCooldownRun.init(150.0, "LookAtCooldownRun", "", obj);
    mLookAtCooldownRunRand.init(60.0, "LookAtCooldownRunRand", "", obj);
    mLookAtCounterRun.init(10.0, "LookAtCounterRun", "", obj);
    mLookAtCounterRunRand.init(40.0, "LookAtCounterRunRand", "", obj);
    mAttackCounterLength.init(30.0, "AttackCounterLength", "", obj);
    mAttackCounterRand.init(30.0, "AttackCounterRand", "", obj);
    mHowlCooldownCounterLength.init(1600.0, "HowlCooldownCounterLength", "", obj);
    mHowlCooldownCounterRand.init(600.0, "HowlCooldownCounterRand", "", obj);
    mHealCooldownCounterLength.init(0.0, "HealCooldownCounterLength", "", obj);
    mHealCooldownCounterRand.init(0.0, "HealCooldownCounterRand", "", obj);
    mFailPathCooldownCounterLength.init(120.0, "FailPathCooldownCounterLength", "", obj);
    mFailPathCooldownCounterRand.init(0.0, "FailPathCooldownCounterRand", "", obj);
    mRetargetCooldownCounterLength.init(30.0, "RetargetCooldownCounterLength", "", obj);
    mRetargetCooldownCounterRand.init(0.0, "RetargetCooldownCounterRand", "", obj);
    mAfterTargetDeathCounterLength.init(30.0, "AfterTargetDeathCounterLength", "", obj);
    mAfterTargetDeathCounterRand.init(30.0, "AfterTargetDeathCounterRand", "", obj);
    mLostTargetCounterLength.init(25.0, "LostTargetCounterLength", "", obj);
    mLostTargetCounterRand.init(0.0, "LostTargetCounterRand", "", obj);
    mInvinceableCounterLength.init(90.0, "InvinceableCounterLength", "", obj);
    mInvinceableCounterRand.init(30.0, "InvinceableCounterRand", "", obj);
    mCallDelayMinLength.init(10.0, "CallDelayMinLength", "", obj);
    mCallOverrideCounterLength.init(900.0, "CallOverrideCounterLength", "", obj);
    mGiveUpShiekSensorLength.init(300.0, "GiveUpShiekSensorLength", "", obj);
    mRetryShiekSensorLength.init(900.0, "RetryShiekSensorLength", "", obj);
    mBattleWallHitLength.init(10.0, "BattleWallHitLength", "", obj);
    mFollowRetryLength.init(30.0, "FollowRetryLength", "", obj);
    mPowerUpFoodLength.init(3600.0, "PowerUpFoodLength", "", obj);
    mSafePosFailCounter.init(3600.0, "SafePosFailCounter", "", obj);
    mRestrictedTargetTimeNormal.init(300.0, "RestrictedTargetTimeNormal", "", obj);
    mRestrictedTargetTimeSpecial.init(500.0, "RestrictedTargetTimeSpecial", "", obj);
    mPowerUpFoodAttackMod.init(5, "PowerUpFoodAttackMod", "", obj);
    mPowerUpFoodChainAttackCharge.init(25.0, "PowerUpFoodChainAttackCharge", "", obj);
    mVSStalfosCritChance.init(10, "VSStalfosCritChance", "", obj);
    mAttackBase.init(10.0, "AttackBase", "", obj);
    mAttackHeartMod.init(0.5, "AttackHeartMod", "", obj);
    mDefenseBase.init(3.0, "DefenseBase", "", obj);
    mDefenseHeartMod.init(0.5, "DefenseHeartMod", "", obj);
}

}  // namespace ksys::res
