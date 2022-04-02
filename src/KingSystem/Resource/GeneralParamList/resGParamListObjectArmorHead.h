#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectArmorHead : public GParamListObject {
public:
    GParamListObjectArmorHead();
    const char* getName() const override { return "ArmorHead"; }

    agl::utl::Parameter<sead::Vector3f> mEarRotate;
    agl::utl::Parameter<s32> mMantleType;
    agl::utl::Parameter<sead::SafeString> mMaskType;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectArmorHead, 0xa8);

inline GParamListObjectArmorHead::GParamListObjectArmorHead() {
    auto* const obj = &mObj;

    mEarRotate.init({0.0, 0.0, 0.0}, "EarRotate", "", obj);
    mMantleType.init(0, "MantleType", "", obj);
    mMaskType.init("", "MaskType", "", obj);
}

}  // namespace ksys::res
