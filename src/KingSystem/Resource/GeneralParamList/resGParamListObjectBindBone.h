#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectBindBone : public GParamListObject {
public:
    GParamListObjectBindBone();
    const char* getName() const override { return "BindBone"; }

    agl::utl::Parameter<sead::SafeString> mBoneName;
    agl::utl::Parameter<sead::Vector3f> mBoneOffset;
    agl::utl::Parameter<sead::Vector3f> mBoneRotate;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectBindBone, 0xb0);

inline GParamListObjectBindBone::GParamListObjectBindBone() {
    auto* const obj = &mObj;

    mBoneName.init("", "BoneName", "", obj);
    mBoneOffset.init({0.0, 0.0, 0.0}, "BoneOffset", "", obj);
    mBoneRotate.init({0.0, 0.0, 0.0}, "BoneRotate", "", obj);
}

}  // namespace ksys::res
