#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectArmorUpper : public GParamListObject {
public:
    GParamListObjectArmorUpper();
    const char* getName() const override { return "ArmorUpper"; }

    agl::utl::Parameter<bool> mIsDispOffPorch;
    agl::utl::Parameter<sead::Vector3f> mShiekerStoneTransOffset;
    agl::utl::Parameter<sead::Vector3f> mShiekerStoneRotOffset;
    agl::utl::Parameter<bool> mDisableSelfMantle;
    agl::utl::Parameter<s32> mUseMantleType;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectArmorUpper, 0xe8);

inline GParamListObjectArmorUpper::GParamListObjectArmorUpper() {
    auto* const obj = &mObj;

    mIsDispOffPorch.init(false, "IsDispOffPorch", "", obj);
    mShiekerStoneTransOffset.init({0.0, 0.0, 0.0}, "ShiekerStoneTransOffset", "", obj);
    mShiekerStoneRotOffset.init({0.0, 0.0, 0.0}, "ShiekerStoneRotOffset", "", obj);
    mDisableSelfMantle.init(false, "DisableSelfMantle", "", obj);
    mUseMantleType.init(0, "UseMantleType", "", obj);
}

}  // namespace ksys::res
