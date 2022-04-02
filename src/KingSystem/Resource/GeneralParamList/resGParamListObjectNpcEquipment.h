#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectNpcEquipment : public GParamListObject {
public:
    GParamListObjectNpcEquipment();
    const char* getName() const override { return "NpcEquipment"; }

    agl::utl::Parameter<bool> mIsSetWeaponTypeWhenEquip;
    agl::utl::Parameter<sead::SafeString> mEquipName1;
    agl::utl::Parameter<f32> mScale1;
    agl::utl::Parameter<sead::Vector3f> mHoldTransOffset1;
    agl::utl::Parameter<sead::Vector3f> mHoldRotOffset1;
    agl::utl::Parameter<sead::Vector3f> mEquipTransOffset1;
    agl::utl::Parameter<sead::Vector3f> mEquipRotOffset1;
    agl::utl::Parameter<sead::SafeString> mEquipName2;
    agl::utl::Parameter<f32> mScale2;
    agl::utl::Parameter<sead::Vector3f> mHoldTransOffset2;
    agl::utl::Parameter<sead::Vector3f> mHoldRotOffset2;
    agl::utl::Parameter<sead::Vector3f> mEquipTransOffset2;
    agl::utl::Parameter<sead::Vector3f> mEquipRotOffset2;
    agl::utl::Parameter<sead::SafeString> mEquipName3;
    agl::utl::Parameter<f32> mScale3;
    agl::utl::Parameter<sead::Vector3f> mHoldTransOffset3;
    agl::utl::Parameter<sead::Vector3f> mHoldRotOffset3;
    agl::utl::Parameter<sead::Vector3f> mEquipTransOffset3;
    agl::utl::Parameter<sead::Vector3f> mEquipRotOffset3;
    agl::utl::Parameter<sead::SafeString> mEquipName4;
    agl::utl::Parameter<f32> mScale4;
    agl::utl::Parameter<sead::Vector3f> mHoldTransOffset4;
    agl::utl::Parameter<sead::Vector3f> mHoldRotOffset4;
    agl::utl::Parameter<sead::Vector3f> mEquipTransOffset4;
    agl::utl::Parameter<sead::Vector3f> mEquipRotOffset4;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectNpcEquipment, 0x3f8);

inline GParamListObjectNpcEquipment::GParamListObjectNpcEquipment() {
    auto* const obj = &mObj;

    mIsSetWeaponTypeWhenEquip.init(false, "IsSetWeaponTypeWhenEquip", "", obj);
    mEquipName1.init("", "EquipName1", "", obj);
    mScale1.init(1.0, "Scale1", "", obj);
    mHoldTransOffset1.init({0.0, 0.0, 0.0}, "HoldTransOffset1", "", obj);
    mHoldRotOffset1.init({0.0, 0.0, 0.0}, "HoldRotOffset1", "", obj);
    mEquipTransOffset1.init({0.0, 0.0, 0.0}, "EquipTransOffset1", "", obj);
    mEquipRotOffset1.init({0.0, 0.0, 0.0}, "EquipRotOffset1", "", obj);
    mEquipName2.init("", "EquipName2", "", obj);
    mScale2.init(1.0, "Scale2", "", obj);
    mHoldTransOffset2.init({0.0, 0.0, 0.0}, "HoldTransOffset2", "", obj);
    mHoldRotOffset2.init({0.0, 0.0, 0.0}, "HoldRotOffset2", "", obj);
    mEquipTransOffset2.init({0.0, 0.0, 0.0}, "EquipTransOffset2", "", obj);
    mEquipRotOffset2.init({0.0, 0.0, 0.0}, "EquipRotOffset2", "", obj);
    mEquipName3.init("", "EquipName3", "", obj);
    mScale3.init(1.0, "Scale3", "", obj);
    mHoldTransOffset3.init({0.0, 0.0, 0.0}, "HoldTransOffset3", "", obj);
    mHoldRotOffset3.init({0.0, 0.0, 0.0}, "HoldRotOffset3", "", obj);
    mEquipTransOffset3.init({0.0, 0.0, 0.0}, "EquipTransOffset3", "", obj);
    mEquipRotOffset3.init({0.0, 0.0, 0.0}, "EquipRotOffset3", "", obj);
    mEquipName4.init("", "EquipName4", "", obj);
    mScale4.init(1.0, "Scale4", "", obj);
    mHoldTransOffset4.init({0.0, 0.0, 0.0}, "HoldTransOffset4", "", obj);
    mHoldRotOffset4.init({0.0, 0.0, 0.0}, "HoldRotOffset4", "", obj);
    mEquipTransOffset4.init({0.0, 0.0, 0.0}, "EquipTransOffset4", "", obj);
    mEquipRotOffset4.init({0.0, 0.0, 0.0}, "EquipRotOffset4", "", obj);
}

}  // namespace ksys::res
