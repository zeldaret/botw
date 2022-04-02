#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectWeaponOption : public GParamListObject {
public:
    GParamListObjectWeaponOption();
    const char* getName() const override { return "WeaponOption"; }

    agl::utl::Parameter<sead::Vector3f> mPlayerHoldTransOffset;
    agl::utl::Parameter<sead::Vector3f> mPlayerHoldRotOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCHoldTransOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCHoldRotOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCEquipTransOffset;
    agl::utl::Parameter<sead::Vector3f> mNPCEquipRotOffset;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectWeaponOption, 0x128);

inline GParamListObjectWeaponOption::GParamListObjectWeaponOption() {
    auto* const obj = &mObj;

    mPlayerHoldTransOffset.init({-0.02, -0.01, 0.12}, "PlayerHoldTransOffset", "", obj);
    mPlayerHoldRotOffset.init({-8.0, -5.0, 75.0}, "PlayerHoldRotOffset", "", obj);
    mNPCHoldTransOffset.init({0.0, 0.0, 0.0}, "NPCHoldTransOffset", "", obj);
    mNPCHoldRotOffset.init({0.0, 0.0, 0.0}, "NPCHoldRotOffset", "", obj);
    mNPCEquipTransOffset.init({0.0, 0.0, 0.0}, "NPCEquipTransOffset", "", obj);
    mNPCEquipRotOffset.init({0.0, 0.0, 0.0}, "NPCEquipRotOffset", "", obj);
}

}  // namespace ksys::res
