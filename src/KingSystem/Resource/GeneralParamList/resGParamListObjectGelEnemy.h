#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGelEnemy : public GParamListObject {
public:
    GParamListObjectGelEnemy();
    const char* getName() const override { return "GelEnemy"; }

    agl::utl::Parameter<sead::SafeString> mMoveBoneName;
    agl::utl::Parameter<f32> mBodyRadius;
    agl::utl::Parameter<s32> mClothBoneNumForEyeCalc;
    agl::utl::Parameter<sead::SafeString> mBodyRootBoneName;
    agl::utl::Parameter<sead::SafeString> mLeftEyeBoneName;
    agl::utl::Parameter<sead::SafeString> mRightEyeBoneName;
    agl::utl::Parameter<f32> mEyeSpaceHalf;
    agl::utl::Parameter<sead::Vector3f> mEyeDir;
    agl::utl::Parameter<sead::Vector3f> mEyeOffset;
    agl::utl::Parameter<f32> mEyeUpMoveRate;
    agl::utl::Parameter<f32> mEyeDownMoveRate;
    agl::utl::Parameter<bool> mIsAverageEyePos;
    agl::utl::Parameter<f32> mEyeDelayAccRate;
    agl::utl::Parameter<f32> mEyeYMoveTheta;
    agl::utl::Parameter<f32> mEyeYMoveFrequency;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGelEnemy, 0x248);

inline GParamListObjectGelEnemy::GParamListObjectGelEnemy() {
    auto* const obj = &mObj;

    mMoveBoneName.init("Body_Move", "MoveBoneName", "", obj);
    mBodyRadius.init(1.0, "BodyRadius", "", obj);
    mClothBoneNumForEyeCalc.init(12, "ClothBoneNumForEyeCalc", "", obj);
    mBodyRootBoneName.init("Skl_Root", "BodyRootBoneName", "", obj);
    mLeftEyeBoneName.init("", "LeftEyeBoneName", "", obj);
    mRightEyeBoneName.init("", "RightEyeBoneName", "", obj);
    mEyeSpaceHalf.init(0.0, "EyeSpaceHalf", "", obj);
    mEyeDir.init({0.75, 1.0, 1.0}, "EyeDir", "", obj);
    mEyeOffset.init({0.0, 0.0, 0.0}, "EyeOffset", "", obj);
    mEyeUpMoveRate.init(0.2, "EyeUpMoveRate", "", obj);
    mEyeDownMoveRate.init(0.05, "EyeDownMoveRate", "", obj);
    mIsAverageEyePos.init(true, "IsAverageEyePos", "", obj);
    mEyeDelayAccRate.init(0.6, "EyeDelayAccRate", "", obj);
    mEyeYMoveTheta.init(1.0, "EyeYMoveTheta", "", obj);
    mEyeYMoveFrequency.init(0.033, "EyeYMoveFrequency", "", obj);
}

}  // namespace ksys::res
