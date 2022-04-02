#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectFish : public GParamListObject {
public:
    GParamListObjectFish();
    const char* getName() const override { return "Fish"; }

    agl::utl::Parameter<f32> mRestoreSpeedRate;
    agl::utl::Parameter<f32> mRestoreSpeedRateAdd;
    agl::utl::Parameter<f32> mLimitAngle;
    agl::utl::Parameter<f32> mLimitAngleAdd;
    agl::utl::Parameter<f32> mPrevSpeedRate;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectFish, 0xd8);

inline GParamListObjectFish::GParamListObjectFish() {
    auto* const obj = &mObj;

    mRestoreSpeedRate.init(0.3, "RestoreSpeedRate", "", obj);
    mRestoreSpeedRateAdd.init(-0.05, "RestoreSpeedRateAdd", "", obj);
    mLimitAngle.init(60.0, "LimitAngle", "", obj);
    mLimitAngleAdd.init(10.0, "LimitAngleAdd", "", obj);
    mPrevSpeedRate.init(0.3, "PrevSpeedRate", "", obj);
}

}  // namespace ksys::res
