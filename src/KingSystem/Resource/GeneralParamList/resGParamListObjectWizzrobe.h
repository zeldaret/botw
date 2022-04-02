#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectWizzrobe : public GParamListObject {
public:
    GParamListObjectWizzrobe();
    const char* getName() const override { return "Wizzrobe"; }

    agl::utl::Parameter<s32> mMagicWeatherType;
    agl::utl::Parameter<sead::SafeString> mMagicFallActorName;
    agl::utl::Parameter<f32> mMagicFallIgniteRotSpd;
    agl::utl::Parameter<f32> mMagicFallOffsetY;
    agl::utl::Parameter<f32> mMagicFallCenterOffsetXZ;
    agl::utl::Parameter<f32> mMagicFallRandRadius;
    agl::utl::Parameter<f32> mMagicFallIntervalMax;
    agl::utl::Parameter<f32> mMagicFallIntervalMin;
    agl::utl::Parameter<sead::SafeString> mSummonActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectWizzrobe, 0x168);

inline GParamListObjectWizzrobe::GParamListObjectWizzrobe() {
    auto* const obj = &mObj;

    mMagicWeatherType.init(0, "MagicWeatherType", "", obj);
    mMagicFallActorName.init("", "MagicFallActorName", "", obj);
    mMagicFallIgniteRotSpd.init(0.0, "MagicFallIgniteRotSpd", "", obj);
    mMagicFallOffsetY.init(6.0, "MagicFallOffsetY", "", obj);
    mMagicFallCenterOffsetXZ.init(5.0, "MagicFallCenterOffsetXZ", "", obj);
    mMagicFallRandRadius.init(12.0, "MagicFallRandRadius", "", obj);
    mMagicFallIntervalMax.init(20.0, "MagicFallIntervalMax", "", obj);
    mMagicFallIntervalMin.init(15.0, "MagicFallIntervalMin", "", obj);
    mSummonActorName.init("", "SummonActorName", "", obj);
}

}  // namespace ksys::res
