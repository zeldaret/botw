#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectEnemyRace : public GParamListObject {
public:
    GParamListObjectEnemyRace();
    const char* getName() const override { return "EnemyRace"; }

    agl::utl::Parameter<sead::SafeString> mEquipableWeapon;
    agl::utl::Parameter<bool> mIsFitGroundByAnimalUnit;
    agl::utl::Parameter<bool> mIsUpdateSupportNormalInAir;
    agl::utl::Parameter<f32> mBowAttackRangeRatio;
    agl::utl::Parameter<f32> mWeaponScaleSmallSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetSmallSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponRotOffsetSmallSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldTransOffsetSmallSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldRotOffsetSmallSword;
    agl::utl::Parameter<f32> mWeaponScaleLargeSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetLargeSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponRotOffsetLargeSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldTransOffsetLargeSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldRotOffsetLargeSword;
    agl::utl::Parameter<f32> mWeaponScaleSpear;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetSpear;
    agl::utl::Parameter<sead::Vector3f> mWeaponRotOffsetSpear;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldTransOffsetSpear;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldRotOffsetSpear;
    agl::utl::Parameter<f32> mWeaponScaleBow;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetBow;
    agl::utl::Parameter<sead::Vector3f> mWeaponRotOffsetBow;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldTransOffsetBow;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldRotOffsetBow;
    agl::utl::Parameter<f32> mWeaponScaleShield;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetShield;
    agl::utl::Parameter<sead::Vector3f> mWeaponRotOffsetShield;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldTransOffsetShield;
    agl::utl::Parameter<sead::Vector3f> mWeaponHoldRotOffsetShield;
    agl::utl::Parameter<bool> mIsUseTargetTag;
    agl::utl::Parameter<sead::SafeString> mTargetActorType;
    agl::utl::Parameter<sead::SafeString> mEscapeAttackedActorType;
    agl::utl::Parameter<bool> mReactionBalloon;
    agl::utl::Parameter<s32> mSmallRagdollTime;
    agl::utl::Parameter<s32> mSmallRagdollRecoverTime;
    agl::utl::Parameter<s32> mSmallLargeRagdollTime;
    agl::utl::Parameter<s32> mSmallLargeRagdollRecoverTime;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectEnemyRace, 0x590);

inline GParamListObjectEnemyRace::GParamListObjectEnemyRace() {
    auto* const obj = &mObj;

    mEquipableWeapon.init("", "EquipableWeapon", "", obj);
    mIsFitGroundByAnimalUnit.init(true, "IsFitGroundByAnimalUnit", "", obj);
    mIsUpdateSupportNormalInAir.init(false, "IsUpdateSupportNormalInAir", "", obj);
    mBowAttackRangeRatio.init(1.0, "BowAttackRangeRatio", "", obj);
    mWeaponScaleSmallSword.init(1.0, "WeaponScaleSmallSword", "", obj);
    mWeaponTransOffsetSmallSword.init({0.0, 0.0, 0.0}, "WeaponTransOffsetSmallSword", "", obj);
    mWeaponRotOffsetSmallSword.init({0.0, 0.0, 0.0}, "WeaponRotOffsetSmallSword", "", obj);
    mWeaponHoldTransOffsetSmallSword.init({0.0, 0.0, 0.0}, "WeaponHoldTransOffsetSmallSword", "",
                                          obj);
    mWeaponHoldRotOffsetSmallSword.init({0.0, 0.0, 0.0}, "WeaponHoldRotOffsetSmallSword", "", obj);
    mWeaponScaleLargeSword.init(1.0, "WeaponScaleLargeSword", "", obj);
    mWeaponTransOffsetLargeSword.init({0.0, 0.0, 0.0}, "WeaponTransOffsetLargeSword", "", obj);
    mWeaponRotOffsetLargeSword.init({0.0, 0.0, 0.0}, "WeaponRotOffsetLargeSword", "", obj);
    mWeaponHoldTransOffsetLargeSword.init({0.0, 0.0, 0.0}, "WeaponHoldTransOffsetLargeSword", "",
                                          obj);
    mWeaponHoldRotOffsetLargeSword.init({0.0, 0.0, 0.0}, "WeaponHoldRotOffsetLargeSword", "", obj);
    mWeaponScaleSpear.init(1.0, "WeaponScaleSpear", "", obj);
    mWeaponTransOffsetSpear.init({0.0, 0.0, 0.0}, "WeaponTransOffsetSpear", "", obj);
    mWeaponRotOffsetSpear.init({0.0, 0.0, 0.0}, "WeaponRotOffsetSpear", "", obj);
    mWeaponHoldTransOffsetSpear.init({0.0, 0.0, 0.0}, "WeaponHoldTransOffsetSpear", "", obj);
    mWeaponHoldRotOffsetSpear.init({0.0, 0.0, 0.0}, "WeaponHoldRotOffsetSpear", "", obj);
    mWeaponScaleBow.init(1.0, "WeaponScaleBow", "", obj);
    mWeaponTransOffsetBow.init({0.0, 0.0, 0.0}, "WeaponTransOffsetBow", "", obj);
    mWeaponRotOffsetBow.init({0.0, 0.0, 0.0}, "WeaponRotOffsetBow", "", obj);
    mWeaponHoldTransOffsetBow.init({0.0, 0.0, 0.0}, "WeaponHoldTransOffsetBow", "", obj);
    mWeaponHoldRotOffsetBow.init({0.0, 0.0, 0.0}, "WeaponHoldRotOffsetBow", "", obj);
    mWeaponScaleShield.init(1.0, "WeaponScaleShield", "", obj);
    mWeaponTransOffsetShield.init({0.0, 0.0, 0.0}, "WeaponTransOffsetShield", "", obj);
    mWeaponRotOffsetShield.init({0.0, 0.0, 0.0}, "WeaponRotOffsetShield", "", obj);
    mWeaponHoldTransOffsetShield.init({0.0, 0.0, 0.0}, "WeaponHoldTransOffsetShield", "", obj);
    mWeaponHoldRotOffsetShield.init({0.0, 0.0, 0.0}, "WeaponHoldRotOffsetShield", "", obj);
    mIsUseTargetTag.init(false, "IsUseTargetTag", "", obj);
    mTargetActorType.init("Player", "TargetActorType", "", obj);
    mEscapeAttackedActorType.init("", "EscapeAttackedActorType", "", obj);
    mReactionBalloon.init(false, "ReactionBalloon", "", obj);
    mSmallRagdollTime.init(8, "SmallRagdollTime", "", obj);
    mSmallRagdollRecoverTime.init(15, "SmallRagdollRecoverTime", "", obj);
    mSmallLargeRagdollTime.init(60, "SmallLargeRagdollTime", "", obj);
    mSmallLargeRagdollRecoverTime.init(20, "SmallLargeRagdollRecoverTime", "", obj);
}

}  // namespace ksys::res
