#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGlobal : public GParamListObject {
public:
    GParamListObjectGlobal();
    const char* getName() const override { return "Global"; }

    agl::utl::Parameter<f32> mEnemyLifeGageDist;
    agl::utl::Parameter<f32> mEnemyNoSkitDist;
    agl::utl::Parameter<f32> mEnemyWeaponPickAllowDist;
    agl::utl::Parameter<s32> mEnemyWeaponPickForbidTime;
    agl::utl::Parameter<f32> mEnemyAnimalNoDamageDist;
    agl::utl::Parameter<f32> mEnemyNearCraeteIDDelay;
    agl::utl::Parameter<s32> mEnemyForceTiredLODCount;
    agl::utl::Parameter<s32> mEnemyForceTiredNoSightLODCount;
    agl::utl::Parameter<s32> mEnemyForceWarpReturnLODCount;
    agl::utl::Parameter<f32> mSilentAttackAng;
    agl::utl::Parameter<f32> mSilentAttackRatio;
    agl::utl::Parameter<s32> mBlownOffPlayerAtkDelay;
    agl::utl::Parameter<f32> mJustAvoidAcceptWpRangeSS;
    agl::utl::Parameter<f32> mJustAvoidAcceptWpRangeLS;
    agl::utl::Parameter<f32> mJustAvoidAcceptWpRangeSP;
    agl::utl::Parameter<s32> mForceNoticeEnemyCount;
    agl::utl::Parameter<f32> mForceNoticeEnemyDist;
    agl::utl::Parameter<s32> mWeaponRickeyLife;
    agl::utl::Parameter<f32> mWeaponDropRotSpd;
    agl::utl::Parameter<s32> mShieldRideBaseFrame;
    agl::utl::Parameter<s32> mShieldRideHitBaseDamage;
    agl::utl::Parameter<f32> mShieldDamageratio;
    agl::utl::Parameter<f32> mShieldSurfMasterFrictionRatio;
    agl::utl::Parameter<f32> mLoudNoiseRadius;
    agl::utl::Parameter<f32> mImpulse2DamageRatio;
    agl::utl::Parameter<f32> mIceMeltSpeedOnContactFire;
    agl::utl::Parameter<f32> mCriticalAttackRatio;
    agl::utl::Parameter<f32> mBooerangAttackRatio;
    agl::utl::Parameter<f32> mHitImpulseClampMax;
    agl::utl::Parameter<f32> mDropItemVelXZFromBomb;
    agl::utl::Parameter<f32> mDropItemVelYFromBomb;
    agl::utl::Parameter<f32> mDropItemVelRandomFromBomb;
    agl::utl::Parameter<f32> mDropItemAngVelFromBomb;
    agl::utl::Parameter<f32> mDropItemAngVelRandomFromBomb;
    agl::utl::Parameter<f32> mDropItemVelXZSmall;
    agl::utl::Parameter<f32> mDropItemVelYSmall;
    agl::utl::Parameter<f32> mDropItemVelRandomSmall;
    agl::utl::Parameter<f32> mDropItemAngVelSmall;
    agl::utl::Parameter<f32> mDropItemAngVelRandomSmall;
    agl::utl::Parameter<f32> mDropItemVelXZLarge;
    agl::utl::Parameter<f32> mDropItemVelYLarge;
    agl::utl::Parameter<f32> mDropItemVelRandomLarge;
    agl::utl::Parameter<f32> mDropItemAngVelLarge;
    agl::utl::Parameter<f32> mDropItemAngVelRandomLarge;
    agl::utl::Parameter<f32> mDropItemVelXZRupeeRabbit;
    agl::utl::Parameter<f32> mDropItemVelYRupeeRabbit;
    agl::utl::Parameter<f32> mDropItemVelRandomRupeeRabbit;
    agl::utl::Parameter<f32> mDropItemVelXZItemRupeeOnly;
    agl::utl::Parameter<f32> mDropItemVelYItemRupeeOnly;
    agl::utl::Parameter<f32> mDropItemVelRandomItemRupeeOnly;
    agl::utl::Parameter<f32> mDropItemInvincibleTime;
    agl::utl::Parameter<sead::Vector3f> mTreeWeaponEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mTreeWeaponEquipRotOffset;
    agl::utl::Parameter<f32> mWetRatioToDie;
    agl::utl::Parameter<f32> mEnvWetRatioToDie;
    agl::utl::Parameter<f32> mNPCTurnAngleDiff;
    agl::utl::Parameter<s32> mNPCWaitFrameAfterEvent;
    agl::utl::Parameter<f32> mNPCIgnorePlayerTime;
    agl::utl::Parameter<f32> mNPCCancelIgnorePlayerTime;
    agl::utl::Parameter<f32> mNPCOpenDoorDistance;
    agl::utl::Parameter<f32> mNPCWalkRateOnSandAndSnow;
    agl::utl::Parameter<f32> mNPCDownVerticallyAngle;
    agl::utl::Parameter<f32> mGerudoQueenSafetyAreaRadius;
    agl::utl::Parameter<s32> mCreateFairyLimitCount;
    agl::utl::Parameter<f32> mTerrorRegistSpeed;
    agl::utl::Parameter<f32> mTerrorUnregistSpeed;
    agl::utl::Parameter<s32> mTerrorRegistTimer;
    agl::utl::Parameter<f32> mTerrorRadiusOffset;
    agl::utl::Parameter<s32> mSpeedTerrorLevel;
    agl::utl::Parameter<s32> mSpeedTerrorLevelHuge;
    agl::utl::Parameter<f32> mSpeedTerrorLevelCheckRadius;
    agl::utl::Parameter<f32> mAtDirTypeAffectRatio;
    agl::utl::Parameter<f32> mRainyAwnHearingLevel;
    agl::utl::Parameter<f32> mHorseBindOffsetYOfMaleUMii;
    agl::utl::Parameter<f32> mHorseBindOffsetYOfFemaleUMii;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreasePerFrame;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseSootheAtFirstRun;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseSootheAfterRun;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseSootheAfterGearTop;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseSootheAfterJump;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseSootheWhileResisting;
    agl::utl::Parameter<sead::Vector3f> mHorseFamiliarityIncreaseEat;
    agl::utl::Parameter<sead::Vector3f> mHorseAlertProbability;
    agl::utl::Parameter<sead::Vector3f> mHorseAlertFramesMin;
    agl::utl::Parameter<sead::Vector3f> mHorseAlertFramesMax;
    agl::utl::Parameter<s32> mHorseExtraChargeNum;
    agl::utl::Parameter<f32> mPlayerGrabThrowDiffRate;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGlobal, 0xb78);

inline GParamListObjectGlobal::GParamListObjectGlobal() {
    auto* const obj = &mObj;

    mEnemyLifeGageDist.init(60.0, "EnemyLifeGageDist", "", obj);
    mEnemyNoSkitDist.init(0.0, "EnemyNoSkitDist", "", obj);
    mEnemyWeaponPickAllowDist.init(5.0, "EnemyWeaponPickAllowDist", "", obj);
    mEnemyWeaponPickForbidTime.init(30, "EnemyWeaponPickForbidTime", "", obj);
    mEnemyAnimalNoDamageDist.init(70.0, "EnemyAnimalNoDamageDist", "", obj);
    mEnemyNearCraeteIDDelay.init(30.0, "EnemyNearCraeteIDDelay", "", obj);
    mEnemyForceTiredLODCount.init(60, "EnemyForceTiredLODCount", "", obj);
    mEnemyForceTiredNoSightLODCount.init(240, "EnemyForceTiredNoSightLODCount", "", obj);
    mEnemyForceWarpReturnLODCount.init(240, "EnemyForceWarpReturnLODCount", "", obj);
    mSilentAttackAng.init(0.0, "SilentAttackAng", "", obj);
    mSilentAttackRatio.init(2.0, "SilentAttackRatio", "", obj);
    mBlownOffPlayerAtkDelay.init(30, "BlownOffPlayerAtkDelay", "", obj);
    mJustAvoidAcceptWpRangeSS.init(1.6, "JustAvoidAcceptWpRangeSS", "", obj);
    mJustAvoidAcceptWpRangeLS.init(1.8, "JustAvoidAcceptWpRangeLS", "", obj);
    mJustAvoidAcceptWpRangeSP.init(5.0, "JustAvoidAcceptWpRangeSP", "", obj);
    mForceNoticeEnemyCount.init(3, "ForceNoticeEnemyCount", "", obj);
    mForceNoticeEnemyDist.init(50.0, "ForceNoticeEnemyDist", "", obj);
    mWeaponRickeyLife.init(3, "WeaponRickeyLife", "", obj);
    mWeaponDropRotSpd.init(30.0, "WeaponDropRotSpd", "", obj);
    mShieldRideBaseFrame.init(60, "ShieldRideBaseFrame", "", obj);
    mShieldRideHitBaseDamage.init(1, "ShieldRideHitBaseDamage", "", obj);
    mShieldDamageratio.init(0.2, "ShieldDamageratio", "", obj);
    mShieldSurfMasterFrictionRatio.init(0.2, "ShieldSurfMasterFrictionRatio", "", obj);
    mLoudNoiseRadius.init(80.0, "LoudNoiseRadius", "", obj);
    mImpulse2DamageRatio.init(0.004, "Impulse2DamageRatio", "", obj);
    mIceMeltSpeedOnContactFire.init(2.0, "IceMeltSpeedOnContactFire", "", obj);
    mCriticalAttackRatio.init(4.0, "CriticalAttackRatio", "", obj);
    mBooerangAttackRatio.init(1.5, "BooerangAttackRatio", "", obj);
    mHitImpulseClampMax.init(20.0, "HitImpulseClampMax", "", obj);
    mDropItemVelXZFromBomb.init(0.4, "DropItemVelXZFromBomb", "", obj);
    mDropItemVelYFromBomb.init(0.05, "DropItemVelYFromBomb", "", obj);
    mDropItemVelRandomFromBomb.init(0.1, "DropItemVelRandomFromBomb", "", obj);
    mDropItemAngVelFromBomb.init(5.0, "DropItemAngVelFromBomb", "", obj);
    mDropItemAngVelRandomFromBomb.init(0.5, "DropItemAngVelRandomFromBomb", "", obj);
    mDropItemVelXZSmall.init(0.075, "DropItemVelXZSmall", "", obj);
    mDropItemVelYSmall.init(0.05, "DropItemVelYSmall", "", obj);
    mDropItemVelRandomSmall.init(0.1, "DropItemVelRandomSmall", "", obj);
    mDropItemAngVelSmall.init(5.0, "DropItemAngVelSmall", "", obj);
    mDropItemAngVelRandomSmall.init(0.5, "DropItemAngVelRandomSmall", "", obj);
    mDropItemVelXZLarge.init(0.2, "DropItemVelXZLarge", "", obj);
    mDropItemVelYLarge.init(0.05, "DropItemVelYLarge", "", obj);
    mDropItemVelRandomLarge.init(0.1, "DropItemVelRandomLarge", "", obj);
    mDropItemAngVelLarge.init(5.0, "DropItemAngVelLarge", "", obj);
    mDropItemAngVelRandomLarge.init(0.5, "DropItemAngVelRandomLarge", "", obj);
    mDropItemVelXZRupeeRabbit.init(0.25, "DropItemVelXZRupeeRabbit", "", obj);
    mDropItemVelYRupeeRabbit.init(0.1, "DropItemVelYRupeeRabbit", "", obj);
    mDropItemVelRandomRupeeRabbit.init(0.05, "DropItemVelRandomRupeeRabbit", "", obj);
    mDropItemVelXZItemRupeeOnly.init(0.1, "DropItemVelXZItemRupeeOnly", "", obj);
    mDropItemVelYItemRupeeOnly.init(0.1, "DropItemVelYItemRupeeOnly", "", obj);
    mDropItemVelRandomItemRupeeOnly.init(0.05, "DropItemVelRandomItemRupeeOnly", "", obj);
    mDropItemInvincibleTime.init(30.0, "DropItemInvincibleTime", "", obj);
    mTreeWeaponEquipTransOffset.init({0.0, 0.0, 0.0}, "TreeWeaponEquipTransOffset", "", obj);
    mTreeWeaponEquipRotOffset.init({0.0, 0.0, 0.0}, "TreeWeaponEquipRotOffset", "", obj);
    mWetRatioToDie.init(0.5, "WetRatioToDie", "", obj);
    mEnvWetRatioToDie.init(0.95, "EnvWetRatioToDie", "", obj);
    mNPCTurnAngleDiff.init(30.0, "NPCTurnAngleDiff", "", obj);
    mNPCWaitFrameAfterEvent.init(60, "NPCWaitFrameAfterEvent", "", obj);
    mNPCIgnorePlayerTime.init(10.0, "NPCIgnorePlayerTime", "", obj);
    mNPCCancelIgnorePlayerTime.init(1800.0, "NPCCancelIgnorePlayerTime", "", obj);
    mNPCOpenDoorDistance.init(5.0, "NPCOpenDoorDistance", "", obj);
    mNPCWalkRateOnSandAndSnow.init(0.8, "NPCWalkRateOnSandAndSnow", "", obj);
    mNPCDownVerticallyAngle.init(20.0, "NPCDownVerticallyAngle", "", obj);
    mGerudoQueenSafetyAreaRadius.init(12.0, "GerudoQueenSafetyAreaRadius", "", obj);
    mCreateFairyLimitCount.init(10, "CreateFairyLimitCount", "", obj);
    mTerrorRegistSpeed.init(190.0, "TerrorRegistSpeed", "", obj);
    mTerrorUnregistSpeed.init(60.0, "TerrorUnregistSpeed", "", obj);
    mTerrorRegistTimer.init(30, "TerrorRegistTimer", "", obj);
    mTerrorRadiusOffset.init(1.5, "TerrorRadiusOffset", "", obj);
    mSpeedTerrorLevel.init(2, "SpeedTerrorLevel", "", obj);
    mSpeedTerrorLevelHuge.init(4, "SpeedTerrorLevelHuge", "", obj);
    mSpeedTerrorLevelCheckRadius.init(3.0, "SpeedTerrorLevelCheckRadius", "", obj);
    mAtDirTypeAffectRatio.init(1.0, "AtDirTypeAffectRatio", "", obj);
    mRainyAwnHearingLevel.init(0.7, "RainyAwnHearingLevel", "", obj);
    mHorseBindOffsetYOfMaleUMii.init(0.0, "HorseBindOffsetYOfMaleUMii", "", obj);
    mHorseBindOffsetYOfFemaleUMii.init(0.0, "HorseBindOffsetYOfFemaleUMii", "", obj);
    mHorseFamiliarityIncreasePerFrame.init({0.0, 0.0, 0.0}, "HorseFamiliarityIncreasePerFrame", "",
                                           obj);
    mHorseFamiliarityIncreaseSootheAtFirstRun.init(
        {0.3, 0.08, 0.06}, "HorseFamiliarityIncreaseSootheAtFirstRun", "", obj);
    mHorseFamiliarityIncreaseSootheAfterRun.init({0.3, 0.08, 0.06},
                                                 "HorseFamiliarityIncreaseSootheAfterRun", "", obj);
    mHorseFamiliarityIncreaseSootheAfterGearTop.init(
        {0.3, 0.08, 0.06}, "HorseFamiliarityIncreaseSootheAfterGearTop", "", obj);
    mHorseFamiliarityIncreaseSootheAfterJump.init(
        {0.3, 0.08, 0.06}, "HorseFamiliarityIncreaseSootheAfterJump", "", obj);
    mHorseFamiliarityIncreaseSootheWhileResisting.init(
        {0.3, 0.08, 0.06}, "HorseFamiliarityIncreaseSootheWhileResisting", "", obj);
    mHorseFamiliarityIncreaseEat.init({0.7, 0.2, 0.1}, "HorseFamiliarityIncreaseEat", "", obj);
    mHorseAlertProbability.init({0.001, 0.003, 0.001}, "HorseAlertProbability", "", obj);
    mHorseAlertFramesMin.init({120.0, 120.0, 120.0}, "HorseAlertFramesMin", "", obj);
    mHorseAlertFramesMax.init({240.0, 240.0, 240.0}, "HorseAlertFramesMax", "", obj);
    mHorseExtraChargeNum.init(3, "HorseExtraChargeNum", "", obj);
    mPlayerGrabThrowDiffRate.init(0.2, "PlayerGrabThrowDiffRate", "", obj);
}

}  // namespace ksys::res
