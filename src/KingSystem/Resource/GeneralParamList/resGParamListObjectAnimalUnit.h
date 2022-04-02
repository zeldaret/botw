#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAnimalUnit : public GParamListObject {
public:
    GParamListObjectAnimalUnit();
    const char* getName() const override { return "AnimalUnit"; }

    agl::utl::Parameter<sead::SafeString> mSpeedActorName;
    agl::utl::Parameter<f32> mBasePlayRate;
    agl::utl::Parameter<s32> mGearMaxNum;
    agl::utl::Parameter<bool> mIsSetWaitASAtGear0;
    agl::utl::Parameter<f32> mStressFramesMin;
    agl::utl::Parameter<f32> mStressFramesMax;
    agl::utl::Parameter<f32> mSteeringOutputKp;
    agl::utl::Parameter<f32> mSteeringOutputKi;
    agl::utl::Parameter<f32> mSteeringOutputKd;
    agl::utl::Parameter<f32> mSteeringOutputIClamp;
    agl::utl::Parameter<f32> mSteeringOutputIReduceRatio;
    agl::utl::Parameter<f32> mSteeringOutputDLerpRatio;
    agl::utl::Parameter<f32> mSteeringOutputAvoidanceLerpRatio;
    agl::utl::Parameter<f32> mSteeringOutputIIRLerpRatio;
    agl::utl::Parameter<f32> mOverrideSteeringOutputKp;
    agl::utl::Parameter<f32> mOverrideSteeringOutputKi;
    agl::utl::Parameter<f32> mOverrideSteeringOutputKd;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAnimalUnit, 0x260);

inline GParamListObjectAnimalUnit::GParamListObjectAnimalUnit() {
    auto* const obj = &mObj;

    mSpeedActorName.init("", "SpeedActorName", "", obj);
    mBasePlayRate.init(1.0, "BasePlayRate", "", obj);
    mGearMaxNum.init(4, "GearMaxNum", "", obj);
    mIsSetWaitASAtGear0.init(true, "IsSetWaitASAtGear0", "", obj);
    mStressFramesMin.init(0.0, "StressFramesMin", "", obj);
    mStressFramesMax.init(0.0, "StressFramesMax", "", obj);
    mSteeringOutputKp.init(0.6, "SteeringOutputKp", "", obj);
    mSteeringOutputKi.init(0.15, "SteeringOutputKi", "", obj);
    mSteeringOutputKd.init(0.002, "SteeringOutputKd", "", obj);
    mSteeringOutputIClamp.init(1.0, "SteeringOutputIClamp", "", obj);
    mSteeringOutputIReduceRatio.init(0.0, "SteeringOutputIReduceRatio", "", obj);
    mSteeringOutputDLerpRatio.init(0.2, "SteeringOutputDLerpRatio", "", obj);
    mSteeringOutputAvoidanceLerpRatio.init(0.08, "SteeringOutputAvoidanceLerpRatio", "", obj);
    mSteeringOutputIIRLerpRatio.init(0.4, "SteeringOutputIIRLerpRatio", "", obj);
    mOverrideSteeringOutputKp.init(-1.0, "OverrideSteeringOutputKp", "", obj);
    mOverrideSteeringOutputKi.init(-1.0, "OverrideSteeringOutputKi", "", obj);
    mOverrideSteeringOutputKd.init(-1.0, "OverrideSteeringOutputKd", "", obj);
}

}  // namespace ksys::res
