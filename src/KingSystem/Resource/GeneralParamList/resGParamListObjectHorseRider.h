#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorseRider : public GParamListObject {
public:
    GParamListObjectHorseRider();
    const char* getName() const override { return "HorseRider"; }

    agl::utl::Parameter<sead::SafeString> mRootNode;
    agl::utl::Parameter<sead::SafeString> mSpineNode;
    agl::utl::Parameter<sead::SafeString> mRotBaseNode;
    agl::utl::Parameter<sead::Vector3f> mRotAxis;
    agl::utl::Parameter<f32> mRotLimit;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetSmallSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetLargeSword;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetSpear;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetBow;
    agl::utl::Parameter<sead::Vector3f> mWeaponTransOffsetShield;
    agl::utl::Parameter<sead::SafeString> mLeftFootNode;
    agl::utl::Parameter<sead::Vector3f> mLeftFootRotAxis;
    agl::utl::Parameter<sead::SafeString> mRightFootNode;
    agl::utl::Parameter<sead::Vector3f> mRightFootRotAxis;
    agl::utl::Parameter<f32> mFootRotRatio;
    agl::utl::Parameter<f32> mFootRetRotRatio;
    agl::utl::Parameter<f32> mFootRotAngleForKuma;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectHorseRider, 0x2c0);

inline GParamListObjectHorseRider::GParamListObjectHorseRider() {
    auto* const obj = &mObj;

    mRootNode.init("", "RootNode", "", obj);
    mSpineNode.init("", "SpineNode", "", obj);
    mRotBaseNode.init("", "RotBaseNode", "", obj);
    mRotAxis.init({0.0, 1.0, 0.0}, "RotAxis", "", obj);
    mRotLimit.init(0.0, "RotLimit", "", obj);
    mWeaponTransOffsetSmallSword.init({0.0, 0.0, 0.0}, "WeaponTransOffsetSmallSword", "", obj);
    mWeaponTransOffsetLargeSword.init({0.0, 0.0, 0.0}, "WeaponTransOffsetLargeSword", "", obj);
    mWeaponTransOffsetSpear.init({0.0, 0.0, 0.0}, "WeaponTransOffsetSpear", "", obj);
    mWeaponTransOffsetBow.init({0.0, 0.0, 0.0}, "WeaponTransOffsetBow", "", obj);
    mWeaponTransOffsetShield.init({0.0, 0.0, 0.0}, "WeaponTransOffsetShield", "", obj);
    mLeftFootNode.init("", "LeftFootNode", "", obj);
    mLeftFootRotAxis.init({0.0, 0.0, 0.0}, "LeftFootRotAxis", "", obj);
    mRightFootNode.init("", "RightFootNode", "", obj);
    mRightFootRotAxis.init({0.0, 0.0, 0.0}, "RightFootRotAxis", "", obj);
    mFootRotRatio.init(0.4, "FootRotRatio", "", obj);
    mFootRetRotRatio.init(0.8, "FootRetRotRatio", "", obj);
    mFootRotAngleForKuma.init(0.0, "FootRotAngleForKuma", "", obj);
}

}  // namespace ksys::res
