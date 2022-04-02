#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectArmor : public GParamListObject {
public:
    GParamListObjectArmor();
    const char* getName() const override { return "Armor"; }

    agl::utl::Parameter<s32> mStarNum;
    agl::utl::Parameter<s32> mDefenceAddLevel;
    agl::utl::Parameter<sead::SafeString> mWindScaleMesh;
    agl::utl::Parameter<f32> mWindScale;
    agl::utl::Parameter<sead::SafeString> mNextRankName;
    agl::utl::Parameter<sead::Vector3f> mAffectTransOffsetShield;
    agl::utl::Parameter<sead::Vector3f> mAffectRotOffsetShield;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectArmor, 0x138);

inline GParamListObjectArmor::GParamListObjectArmor() {
    auto* const obj = &mObj;

    mStarNum.init(0, "StarNum", "", obj);
    mDefenceAddLevel.init(0, "DefenceAddLevel", "", obj);
    mWindScaleMesh.init("", "WindScaleMesh", "", obj);
    mWindScale.init(0.0, "WindScale", "", obj);
    mNextRankName.init("", "NextRankName", "", obj);
    mAffectTransOffsetShield.init({0.0, 0.0, 0.0}, "AffectTransOffsetShield", "", obj);
    mAffectRotOffsetShield.init({0.0, 0.0, 0.0}, "AffectRotOffsetShield", "", obj);
}

}  // namespace ksys::res
