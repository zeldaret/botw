#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectShield : public GParamListObject {
public:
    GParamListObjectShield();
    const char* getName() const override { return "Shield"; }

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
    agl::utl::Parameter<f32> mRideBreakRatio;
    agl::utl::Parameter<s32> mMirrorLevel;
    agl::utl::Parameter<sead::SafeString> mWeaponSubType;
    agl::utl::Parameter<f32> mSurfingFriction;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectShield, 0x2f0);

inline GParamListObjectShield::GParamListObjectShield() {
    auto* const obj = &mObj;

    mPlayerHoldTransOffset.init({-0.1, -0.01, 0.2}, "PlayerHoldTransOffset", "", obj);
    mPlayerHoldRotOffset.init({8.0, 120.0, 5.0}, "PlayerHoldRotOffset", "", obj);
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
    mRideBreakRatio.init(1.0, "RideBreakRatio", "", obj);
    mMirrorLevel.init(0, "MirrorLevel", "", obj);
    mWeaponSubType.init("", "WeaponSubType", "", obj);
    mSurfingFriction.init(1.0, "SurfingFriction", "", obj);
}

}  // namespace ksys::res
