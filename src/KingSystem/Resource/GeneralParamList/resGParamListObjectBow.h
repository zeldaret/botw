#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectBow : public GParamListObject {
public:
    GParamListObjectBow();
    const char* getName() const override { return "Bow"; }

    agl::utl::Parameter<sead::SafeString> mQuiverName;
    agl::utl::Parameter<sead::SafeString> mArrowName;
    agl::utl::Parameter<bool> mIsGuardPierce;
    agl::utl::Parameter<f32> mExtraDamageRatio;
    agl::utl::Parameter<f32> mBaseAttackPowerRatio;
    agl::utl::Parameter<bool> mIsLeadShot;
    agl::utl::Parameter<s32> mLeadShotNum;
    agl::utl::Parameter<f32> mLeadShotAng;
    agl::utl::Parameter<s32> mLeadShotInterval;
    agl::utl::Parameter<bool> mIsRapidFire;
    agl::utl::Parameter<s32> mRapidFireNum;
    agl::utl::Parameter<s32> mRapidFireInterval;
    agl::utl::Parameter<bool> mIsLongRange;
    agl::utl::Parameter<f32> mArrowFirstSpeed;
    agl::utl::Parameter<f32> mArrowAcceleration;
    agl::utl::Parameter<f32> mArrowStabilitySpeed;
    agl::utl::Parameter<f32> mArrowFallAcceleration;
    agl::utl::Parameter<f32> mArrowFallStabilitySpeed;
    agl::utl::Parameter<f32> mArrowGravity;
    agl::utl::Parameter<sead::Vector3f> mPlayerHoldTransOffset;
    agl::utl::Parameter<sead::Vector3f> mPlayerHoldRotOffset;
    agl::utl::Parameter<sead::Vector3f> mPlayerEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mPlayerEquipRotOffset;
    agl::utl::Parameter<sead::Vector3f> mSquatPlayerHoldTransAddOffset;
    agl::utl::Parameter<sead::Vector3f> mSquatPlayerHoldRotAddOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCHoldTransOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCHoldRotOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCEquipRotOffset;
    agl::utl::Parameter<sead::Vector3f> mEnemyEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mEnemyEquipRotOffset;
    agl::utl::Parameter<sead::Vector3f> mStandEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mStandEquipRotOffset;
    agl::utl::Parameter<f32> mArrowChargeRate;
    agl::utl::Parameter<f32> mArrowReloadRate;
    agl::utl::Parameter<sead::SafeString> mWeaponSubType;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectBow, 0x540);

inline GParamListObjectBow::GParamListObjectBow() {
    auto* const obj = &mObj;

    mQuiverName.init("", "QuiverName", "", obj);
    mArrowName.init("", "ArrowName", "", obj);
    mIsGuardPierce.init(false, "IsGuardPierce", "", obj);
    mExtraDamageRatio.init(1.0, "ExtraDamageRatio", "", obj);
    mBaseAttackPowerRatio.init(1.0, "BaseAttackPowerRatio", "", obj);
    mIsLeadShot.init(false, "IsLeadShot", "", obj);
    mLeadShotNum.init(0, "LeadShotNum", "", obj);
    mLeadShotAng.init(45.0, "LeadShotAng", "", obj);
    mLeadShotInterval.init(0, "LeadShotInterval", "", obj);
    mIsRapidFire.init(false, "IsRapidFire", "", obj);
    mRapidFireNum.init(0, "RapidFireNum", "", obj);
    mRapidFireInterval.init(0, "RapidFireInterval", "", obj);
    mIsLongRange.init(false, "IsLongRange", "", obj);
    mArrowFirstSpeed.init(4.5, "ArrowFirstSpeed", "", obj);
    mArrowAcceleration.init(-0.1, "ArrowAcceleration", "", obj);
    mArrowStabilitySpeed.init(3.0, "ArrowStabilitySpeed", "", obj);
    mArrowFallAcceleration.init(-0.2, "ArrowFallAcceleration", "", obj);
    mArrowFallStabilitySpeed.init(1.0, "ArrowFallStabilitySpeed", "", obj);
    mArrowGravity.init(-9.8, "ArrowGravity", "", obj);
    mPlayerHoldTransOffset.init({-0.2, -0.01, 0.0}, "PlayerHoldTransOffset", "", obj);
    mPlayerHoldRotOffset.init({12.0, -60.0, -22.0}, "PlayerHoldRotOffset", "", obj);
    mPlayerEquipTransOffset.init({0.0, 0.0, 0.0}, "PlayerEquipTransOffset", "", obj);
    mPlayerEquipRotOffset.init({0.0, 0.0, 0.0}, "PlayerEquipRotOffset", "", obj);
    mSquatPlayerHoldTransAddOffset.init({0.0, 0.0, 0.0}, "SquatPlayerHoldTransAddOffset", "", obj);
    mSquatPlayerHoldRotAddOffset.init({0.0, 0.0, 0.0}, "SquatPlayerHoldRotAddOffset", "", obj);
    mNPCHoldTransOffset.init({0.0, 0.0, 0.0}, "NPCHoldTransOffset", "", obj);
    mNPCHoldRotOffset.init({0.0, 0.0, 0.0}, "NPCHoldRotOffset", "", obj);
    mNPCEquipTransOffset.init({0.0, 0.0, 0.0}, "NPCEquipTransOffset", "", obj);
    mNPCEquipRotOffset.init({0.0, 0.0, 0.0}, "NPCEquipRotOffset", "", obj);
    mEnemyEquipTransOffset.init({0.0, 0.0, 0.0}, "EnemyEquipTransOffset", "", obj);
    mEnemyEquipRotOffset.init({0.0, 0.0, 0.0}, "EnemyEquipRotOffset", "", obj);
    mStandEquipTransOffset.init({0.0, 0.0, 0.0}, "StandEquipTransOffset", "", obj);
    mStandEquipRotOffset.init({0.0, 0.0, 0.0}, "StandEquipRotOffset", "", obj);
    mArrowChargeRate.init(1.0, "ArrowChargeRate", "", obj);
    mArrowReloadRate.init(1.0, "ArrowReloadRate", "", obj);
    mWeaponSubType.init("", "WeaponSubType", "", obj);
}

}  // namespace ksys::res
