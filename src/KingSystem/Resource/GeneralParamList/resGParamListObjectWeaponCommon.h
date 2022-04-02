#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectWeaponCommon : public GParamListObject {
public:
    GParamListObjectWeaponCommon();
    const char* getName() const override { return "WeaponCommon"; }

    agl::utl::Parameter<f32> mPlayerEqScale;
    agl::utl::Parameter<f32> mEnemyEqScale;
    agl::utl::Parameter<s32> mGuardPower;
    agl::utl::Parameter<s32> mRank;
    agl::utl::Parameter<bool> mIsHammer;
    agl::utl::Parameter<bool> mIsWeakBreaker;
    agl::utl::Parameter<bool> mIsBoomerang;
    agl::utl::Parameter<bool> mIsBlunt;
    agl::utl::Parameter<bool> mIsLuckyWeapon;
    agl::utl::Parameter<bool> mIsPikohan;
    agl::utl::Parameter<bool> mIsThrowingWeapon;
    agl::utl::Parameter<bool> mIsThrowingBreakWeapon;
    agl::utl::Parameter<f32> mThrowRange;
    agl::utl::Parameter<sead::SafeString> mDreadActor;
    agl::utl::Parameter<sead::SafeString> mThroughActor;
    agl::utl::Parameter<sead::SafeString> mNPCWeaponType;
    agl::utl::Parameter<bool> mIsNotOnTerrorHold;
    agl::utl::Parameter<bool> mIsAsOffUnEquiped;
    agl::utl::Parameter<s32> mChemicalEnergyMax;
    agl::utl::Parameter<s32> mChemicalEnergyAmountUsed;
    agl::utl::Parameter<f32> mChemicalEnergyRecoverRate;
    agl::utl::Parameter<s32> mChemicalEnergyRecoverInterval;
    agl::utl::Parameter<s32> mStickDamage;
    agl::utl::Parameter<sead::SafeString> mShootBeam;
    agl::utl::Parameter<sead::Vector3f> mDropFromPorchRot;
    agl::utl::Parameter<f32> mSharpWeaponPer;
    agl::utl::Parameter<s32> mSharpWeaponAddAtkMin;
    agl::utl::Parameter<s32> mSharpWeaponAddAtkMax;
    agl::utl::Parameter<s32> mSharpWeaponAddLifeMin;
    agl::utl::Parameter<s32> mSharpWeaponAddLifeMax;
    agl::utl::Parameter<bool> mSharpWeaponAddCrit;
    agl::utl::Parameter<s32> mSharpWeaponAddGuardMin;
    agl::utl::Parameter<s32> mSharpWeaponAddGuardMax;
    agl::utl::Parameter<s32> mPoweredSharpAddAtkMin;
    agl::utl::Parameter<s32> mPoweredSharpAddAtkMax;
    agl::utl::Parameter<s32> mPoweredSharpAddLifeMin;
    agl::utl::Parameter<s32> mPoweredSharpAddLifeMax;
    agl::utl::Parameter<s32> mPoweredSharpWeaponAddGuardMin;
    agl::utl::Parameter<s32> mPoweredSharpWeaponAddGuardMax;
    agl::utl::Parameter<f32> mPoweredSharpAddThrowMin;
    agl::utl::Parameter<f32> mPoweredSharpAddThrowMax;
    agl::utl::Parameter<bool> mPoweredSharpAddSpreadFire;
    agl::utl::Parameter<bool> mPoweredSharpAddZoomRapid;
    agl::utl::Parameter<f32> mPoweredSharpAddRapidFireMin;
    agl::utl::Parameter<f32> mPoweredSharpAddRapidFireMax;
    agl::utl::Parameter<bool> mPoweredSharpAddSurfMaster;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectWeaponCommon, 0x620);

inline GParamListObjectWeaponCommon::GParamListObjectWeaponCommon() {
    auto* const obj = &mObj;

    mPlayerEqScale.init(1.0, "PlayerEqScale", "", obj);
    mEnemyEqScale.init(1.0, "EnemyEqScale", "", obj);
    mGuardPower.init(0, "GuardPower", "", obj);
    mRank.init(0, "Rank", "", obj);
    mIsHammer.init(false, "IsHammer", "", obj);
    mIsWeakBreaker.init(false, "IsWeakBreaker", "", obj);
    mIsBoomerang.init(false, "IsBoomerang", "", obj);
    mIsBlunt.init(false, "IsBlunt", "", obj);
    mIsLuckyWeapon.init(false, "IsLuckyWeapon", "", obj);
    mIsPikohan.init(false, "IsPikohan", "", obj);
    mIsThrowingWeapon.init(true, "IsThrowingWeapon", "", obj);
    mIsThrowingBreakWeapon.init(true, "IsThrowingBreakWeapon", "", obj);
    mThrowRange.init(20.0, "ThrowRange", "", obj);
    mDreadActor.init("", "DreadActor", "", obj);
    mThroughActor.init("", "ThroughActor", "", obj);
    mNPCWeaponType.init("", "NPCWeaponType", "", obj);
    mIsNotOnTerrorHold.init(false, "IsNotOnTerrorHold", "", obj);
    mIsAsOffUnEquiped.init(false, "IsAsOffUnEquiped", "", obj);
    mChemicalEnergyMax.init(0, "ChemicalEnergyMax", "", obj);
    mChemicalEnergyAmountUsed.init(0, "ChemicalEnergyAmountUsed", "", obj);
    mChemicalEnergyRecoverRate.init(0.0, "ChemicalEnergyRecoverRate", "", obj);
    mChemicalEnergyRecoverInterval.init(60, "ChemicalEnergyRecoverInterval", "", obj);
    mStickDamage.init(0, "StickDamage", "", obj);
    mShootBeam.init("", "ShootBeam", "", obj);
    mDropFromPorchRot.init({0.0, 0.0, 0.0}, "DropFromPorchRot", "", obj);
    mSharpWeaponPer.init(10.0, "SharpWeaponPer", "", obj);
    mSharpWeaponAddAtkMin.init(0, "SharpWeaponAddAtkMin", "", obj);
    mSharpWeaponAddAtkMax.init(0, "SharpWeaponAddAtkMax", "", obj);
    mSharpWeaponAddLifeMin.init(0, "SharpWeaponAddLifeMin", "", obj);
    mSharpWeaponAddLifeMax.init(0, "SharpWeaponAddLifeMax", "", obj);
    mSharpWeaponAddCrit.init(false, "SharpWeaponAddCrit", "", obj);
    mSharpWeaponAddGuardMin.init(0, "SharpWeaponAddGuardMin", "", obj);
    mSharpWeaponAddGuardMax.init(0, "SharpWeaponAddGuardMax", "", obj);
    mPoweredSharpAddAtkMin.init(0, "PoweredSharpAddAtkMin", "", obj);
    mPoweredSharpAddAtkMax.init(0, "PoweredSharpAddAtkMax", "", obj);
    mPoweredSharpAddLifeMin.init(0, "PoweredSharpAddLifeMin", "", obj);
    mPoweredSharpAddLifeMax.init(0, "PoweredSharpAddLifeMax", "", obj);
    mPoweredSharpWeaponAddGuardMin.init(0, "PoweredSharpWeaponAddGuardMin", "", obj);
    mPoweredSharpWeaponAddGuardMax.init(0, "PoweredSharpWeaponAddGuardMax", "", obj);
    mPoweredSharpAddThrowMin.init(1.0, "PoweredSharpAddThrowMin", "", obj);
    mPoweredSharpAddThrowMax.init(1.0, "PoweredSharpAddThrowMax", "", obj);
    mPoweredSharpAddSpreadFire.init(false, "PoweredSharpAddSpreadFire", "", obj);
    mPoweredSharpAddZoomRapid.init(false, "PoweredSharpAddZoomRapid", "", obj);
    mPoweredSharpAddRapidFireMin.init(1.0, "PoweredSharpAddRapidFireMin", "", obj);
    mPoweredSharpAddRapidFireMax.init(1.0, "PoweredSharpAddRapidFireMax", "", obj);
    mPoweredSharpAddSurfMaster.init(false, "PoweredSharpAddSurfMaster", "", obj);
}

}  // namespace ksys::res
