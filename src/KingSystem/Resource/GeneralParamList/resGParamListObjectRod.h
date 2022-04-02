#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectRod : public GParamListObject {
public:
    GParamListObjectRod();
    const char* getName() const override { return "Rod"; }

    agl::utl::Parameter<sead::SafeString> mMagicName;
    agl::utl::Parameter<s32> mChargeMagicNum;
    agl::utl::Parameter<s32> mChargeMagicInterval;
    agl::utl::Parameter<s32> mMagicPower;
    agl::utl::Parameter<f32> mMagicSpeed;
    agl::utl::Parameter<f32> mMagicSpeedByThrow;
    agl::utl::Parameter<f32> mMagicGravity;
    agl::utl::Parameter<f32> mMagicRadius;
    agl::utl::Parameter<s32> mScaleTime;
    agl::utl::Parameter<f32> mMagicRange;
    agl::utl::Parameter<f32> mMagicSpeedByEnemy;
    agl::utl::Parameter<f32> mMagicGravityByEnemy;
    agl::utl::Parameter<f32> mMagicRadiusByEnemy;
    agl::utl::Parameter<s32> mScaleTimeByEnemy;
    agl::utl::Parameter<f32> mMagicRangeByEnemy;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectRod, 0x220);

inline GParamListObjectRod::GParamListObjectRod() {
    auto* const obj = &mObj;

    mMagicName.init("", "MagicName", "", obj);
    mChargeMagicNum.init(4, "ChargeMagicNum", "", obj);
    mChargeMagicInterval.init(5, "ChargeMagicInterval", "", obj);
    mMagicPower.init(0, "MagicPower", "", obj);
    mMagicSpeed.init(0.0, "MagicSpeed", "", obj);
    mMagicSpeedByThrow.init(0.0, "MagicSpeedByThrow", "", obj);
    mMagicGravity.init(0.5, "MagicGravity", "", obj);
    mMagicRadius.init(1.0, "MagicRadius", "", obj);
    mScaleTime.init(1, "ScaleTime", "", obj);
    mMagicRange.init(1.0, "MagicRange", "", obj);
    mMagicSpeedByEnemy.init(0.0, "MagicSpeedByEnemy", "", obj);
    mMagicGravityByEnemy.init(0.5, "MagicGravityByEnemy", "", obj);
    mMagicRadiusByEnemy.init(1.0, "MagicRadiusByEnemy", "", obj);
    mScaleTimeByEnemy.init(1, "ScaleTimeByEnemy", "", obj);
    mMagicRangeByEnemy.init(1.0, "MagicRangeByEnemy", "", obj);
}

}  // namespace ksys::res
