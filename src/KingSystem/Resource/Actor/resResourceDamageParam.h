#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadEnum.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class DamageParam : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(DamageParam, Resource)

public:
    DamageParam() : ParamIO("dmgparam", 0) {}
    ~DamageParam() override = default;

    bool needsParse() const override { return true; }
    bool ParamIO_m0(char* data) override { return false; }

    f32 getDamageRate(const sead::SafeString& damage_source);
    const sead::SafeString& getDamageReaction(const sead::SafeString& damage_source,
                                              const sead::SafeString& damage_size);

    // clang-format off
    SEAD_ENUM(DamageSize,Small,Middle,Large,Huge)
    SEAD_ENUM(DamageSource,Sword,LargeSword,Spear,Arrow,Bomb,Body,Ancient,ShockWave,Impulse,GanonBeam)
    // clang-format on

private:
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::ParameterList mParamList;
    agl::utl::ParameterObj mReactionTableObj;
    agl::utl::ParameterObj mDamageRateObj;
    agl::utl::ParameterObj mParametersObj;
    agl::utl::ParameterObj mDamageTypeObj;

    sead::Buffer<agl::utl::Parameter<f32>> mDamageRateBuffer;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mDamageTypeBuffer;

public:
    agl::utl::Parameter<sead::SafeString> mKeyString;
    agl::utl::Parameter<bool> mBreakable;
    agl::utl::Parameter<bool> mHammerAffect;
    agl::utl::Parameter<bool> mWeakBreakerAffect;
    agl::utl::Parameter<bool> mChemicalAttackAffect;
    agl::utl::Parameter<f32> mSpAffectRatio;
    agl::utl::Parameter<s32> mSpAffectDamage;
    agl::utl::Parameter<bool> mVanishAffect;
    agl::utl::Parameter<bool> mIsCriticalBlowOff;
    agl::utl::Parameter<bool> mIsAcceptAtkImpulse;
    agl::utl::Parameter<bool> mIsCommonCalcImpuleDamage;
    agl::utl::Parameter<bool> mIsHeavyBreak;
    agl::utl::Parameter<f32> mImpulseThresholdLv0;
    agl::utl::Parameter<f32> mImpulseDamageLv0;
    agl::utl::Parameter<f32> mImpulseThresholdLv1;
    agl::utl::Parameter<f32> mImpulseDamageLv1;
    agl::utl::Parameter<f32> mImpulseThresholdLv2;
    agl::utl::Parameter<f32> mImpulseDamageLv2;
    agl::utl::Parameter<f32> mImpulseThresholdLv3;
    agl::utl::Parameter<f32> mImpulseDamageLv3;
    agl::utl::Parameter<f32> mImpulseThresholdLv4;
    agl::utl::Parameter<f32> mFallDamageStartHeight;
    agl::utl::Parameter<s32> mFallDamageMin;
    agl::utl::Parameter<f32> mFallDamagePerMeter;
    agl::utl::Parameter<f32> mFallDamageHighStart;
    agl::utl::Parameter<s32> mFallDamageHighPerMeter;
    agl::utl::Parameter<f32> mFallDamageNoWaterDepth;
    agl::utl::Parameter<sead::SafeString> mWeakPointBone;
    agl::utl::Parameter<f32> mWeakPointCalcArea;
    agl::utl::Parameter<sead::Vector3f> mWeakPointCalcOffset;
    agl::utl::Parameter<f32> mWeakPointArea;
    agl::utl::Parameter<sead::Vector3f> mWeakPointOffset;
    agl::utl::Parameter<f32> mWeakPointRatio;
    agl::utl::Parameter<bool> mWeakPointNoUIFlag;
    agl::utl::Parameter<sead::SafeString> mWeakPointBone2;
    agl::utl::Parameter<f32> mWeakPointCalcArea2;
    agl::utl::Parameter<sead::Vector3f> mWeakPointCalcOffset2;
    agl::utl::Parameter<f32> mWeakPointArea2;
    agl::utl::Parameter<sead::Vector3f> mWeakPointOffset2;
    agl::utl::Parameter<f32> mWeakPointRatio2;
    agl::utl::Parameter<bool> mWeakPointNoUIFlag2;
    agl::utl::Parameter<f32> mSillentKillMultRatio;
    agl::utl::Parameter<s32> mSillentKillAddDamage;
    agl::utl::Parameter<bool> mIsDeadBurnout;
    agl::utl::Parameter<bool> mIsMetamorBurnout;
    agl::utl::Parameter<bool> mIsMatamorFromTg;
    agl::utl::Parameter<bool> mBurnable;
    agl::utl::Parameter<s32> mBurnDamage;
    agl::utl::Parameter<s32> mBurnDamage2;
    agl::utl::Parameter<s32> mBurnDamage3;
    agl::utl::Parameter<s32> mBurnDamage4;
    agl::utl::Parameter<s32> mBurnDamage5;
    agl::utl::Parameter<s32> mBurnTime;
    agl::utl::Parameter<s32> mBurnDamageInterval;
    agl::utl::Parameter<s32> mBurnContinuousDamage;
    agl::utl::Parameter<bool> mBurnCritical;
    agl::utl::Parameter<bool> mProofBurnAtSmallDamage;
    agl::utl::Parameter<bool> mIsDeadIce;
    agl::utl::Parameter<bool> mIsMetamorIce;
    agl::utl::Parameter<bool> mIceable;
    agl::utl::Parameter<s32> mIceDamage;
    agl::utl::Parameter<s32> mIceTime;
    agl::utl::Parameter<bool> mIceBreakableByAtk;
    agl::utl::Parameter<f32> mIceBreakDamageRatio;
    agl::utl::Parameter<bool> mIceCritical;
    agl::utl::Parameter<bool> mProofIceAtSmallDamage;
    agl::utl::Parameter<bool> mIsDeadElectric;
    agl::utl::Parameter<bool> mIsMetamorElectric;
    agl::utl::Parameter<bool> mElectricable;
    agl::utl::Parameter<s32> mElectricDamage;
    agl::utl::Parameter<s32> mElectricTime;
    agl::utl::Parameter<bool> mElecCancelableByAtk;
    agl::utl::Parameter<bool> mProofElecAtSmallDamage;
    agl::utl::Parameter<bool> mWetAffect;
    agl::utl::Parameter<bool> mLightningAffect;
    agl::utl::Parameter<s32> mLightningDamage;
    agl::utl::Parameter<bool> mGerudoHeroAffect;
    agl::utl::Parameter<s32> mGerudoHeroDamage;
    agl::utl::Parameter<s32> mGerudoHeroTime;
    agl::utl::Parameter<bool> mGustAffect;
    agl::utl::Parameter<f32> mDrownHeight;
    agl::utl::Parameter<s32> mDrownDamage;
    agl::utl::Parameter<s32> mColdWaterFrozenTime;
    agl::utl::Parameter<bool> mColdWaterAffect;
    agl::utl::Parameter<s32> mColdWaterDamage;
    agl::utl::Parameter<s32> mColdWaterDamageInterval;
    agl::utl::Parameter<f32> mColdWaterDamageStartDepth;
    agl::utl::Parameter<s32> mColdWaterDamageIntervalDeep;
    agl::utl::Parameter<f32> mColdWaterDamageDeepDepth;
    agl::utl::Parameter<s32> mHotWaterBoiledTime;
    agl::utl::Parameter<bool> mHotWaterHealAffect;
    agl::utl::Parameter<s32> mHotWaterHeal;
    agl::utl::Parameter<s32> mHotWaterHealInterval;
    agl::utl::Parameter<f32> mHotWaterHealStartDepth;
    agl::utl::Parameter<s32> mHotWaterHealIntervalDeep;
    agl::utl::Parameter<f32> mHotWaterHealDeepDepth;
    agl::utl::Parameter<bool> mHotWaterChemCrit;
    agl::utl::Parameter<bool> mPoisonBogAffect;
    agl::utl::Parameter<s32> mPoisonBogDamage;
    agl::utl::Parameter<s32> mPoisonBogDamageInterval;
    agl::utl::Parameter<bool> mLavaAffect;
    agl::utl::Parameter<s32> mLavaDamage;
    agl::utl::Parameter<s32> mLavaDamageInterval;
    agl::utl::Parameter<f32> mLavaDeepDepth;
    agl::utl::Parameter<s32> mLavaDeepDamage;
    agl::utl::Parameter<bool> mCurseAffect;
    agl::utl::Parameter<s32> mCurseDamage;
    agl::utl::Parameter<s32> mCurseInterval;
    agl::utl::Parameter<s32> mCurseContinuousDamage;
    agl::utl::Parameter<s32> mHeavySnowColdTime;
};

}  // namespace ksys::res
