#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectMotorcycle : public GParamListObject {
public:
    GParamListObjectMotorcycle();
    const char* getName() const override { return "Motorcycle"; }

    agl::utl::Parameter<f32> mPitchDampingCoefficient;
    agl::utl::Parameter<f32> mDriftAllowSpeedKPH;
    agl::utl::Parameter<f32> mDriftAbortSpeedKPH;
    agl::utl::Parameter<f32> mDriftAllowSteerRate;
    agl::utl::Parameter<f32> mDriftAbortSteerRate;
    agl::utl::Parameter<f32> mDriftRearAngleRate;
    agl::utl::Parameter<f32> mDriftSpeedRate;
    agl::utl::Parameter<f32> mManualWheelieAllowAngleFront;
    agl::utl::Parameter<f32> mManualWheelieAllowAngleRear;
    agl::utl::Parameter<f32> mManualWheelieLastSec;
    agl::utl::Parameter<f32> mWheelieLastSecInMidAir;
    agl::utl::Parameter<f32> mManualControlProhibitSecAfterWheelie;
    agl::utl::Parameter<f32> mWheelieRevertPower;
    agl::utl::Parameter<f32> mWheelieRevertPowerSec;
    agl::utl::Parameter<f32> mManualWheelieRiseDegDelta;
    agl::utl::Parameter<f32> mWheelieLaunchRiseDegDelta;
    agl::utl::Parameter<f32> mEngineBrakeMaxPower;
    agl::utl::Parameter<f32> mBackwardEngineBrakePower;
    agl::utl::Parameter<f32> mSlipStartAngle;
    agl::utl::Parameter<f32> mSlipThresholdPower;
    agl::utl::Parameter<f32> mSlipPowerMax;
    agl::utl::Parameter<sead::Vector3f> mWristBindRotation;
    agl::utl::Parameter<sead::Vector3f> mWristBindTranslation;
    agl::utl::Parameter<f32> mPostureLimitAngle;
    agl::utl::Parameter<f32> mInvalidPostureLimitSec;
    agl::utl::Parameter<f32> mFallOverThresholdAngle;
    agl::utl::Parameter<f32> mJumpIntervalSec;
    agl::utl::Parameter<f32> mFullEnergyLastSec;
    agl::utl::Parameter<f32> mWheelieLaunchJumpProhibitSec;
    agl::utl::Parameter<f32> mSlowModeTargetSpeedKPH2;
    agl::utl::Parameter<f32> mSlowDriftTargetSpeedKPH2;
    agl::utl::Parameter<f32> mSlowModeTransitionSec;
    agl::utl::Parameter<f32> mSlowSlipThresholdKPH;
    agl::utl::Parameter<f32> mSlowSlipThresholdPower;
    agl::utl::Parameter<f32> mSlowSlipThresholdSec;
    agl::utl::Parameter<f32> mJumpRearWheelRotateRadPerSec;
    agl::utl::Parameter<f32> mWeaponThrowModeSpeedKPH2;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectMotorcycle, 0x4e8);

inline GParamListObjectMotorcycle::GParamListObjectMotorcycle() {
    auto* const obj = &mObj;

    mPitchDampingCoefficient.init(0.2, "PitchDampingCoefficient", "", obj);
    mDriftAllowSpeedKPH.init(45.0, "DriftAllowSpeedKPH", "", obj);
    mDriftAbortSpeedKPH.init(30.0, "DriftAbortSpeedKPH", "", obj);
    mDriftAllowSteerRate.init(0.6, "DriftAllowSteerRate", "", obj);
    mDriftAbortSteerRate.init(0.1, "DriftAbortSteerRate", "", obj);
    mDriftRearAngleRate.init(-2.5, "DriftRearAngleRate", "", obj);
    mDriftSpeedRate.init(0.75, "DriftSpeedRate", "", obj);
    mManualWheelieAllowAngleFront.init(15.0, "ManualWheelieAllowAngleFront", "", obj);
    mManualWheelieAllowAngleRear.init(30.0, "ManualWheelieAllowAngleRear", "", obj);
    mManualWheelieLastSec.init(2.5, "ManualWheelieLastSec", "", obj);
    mWheelieLastSecInMidAir.init(0.5, "WheelieLastSecInMidAir", "", obj);
    mManualControlProhibitSecAfterWheelie.init(1.0, "ManualControlProhibitSecAfterWheelie", "",
                                               obj);
    mWheelieRevertPower.init(4.0, "WheelieRevertPower", "", obj);
    mWheelieRevertPowerSec.init(0.5, "WheelieRevertPowerSec", "", obj);
    mManualWheelieRiseDegDelta.init(3.0, "ManualWheelieRiseDegDelta", "", obj);
    mWheelieLaunchRiseDegDelta.init(1.0, "WheelieLaunchRiseDegDelta", "", obj);
    mEngineBrakeMaxPower.init(100.0, "EngineBrakeMaxPower", "", obj);
    mBackwardEngineBrakePower.init(400.0, "BackwardEngineBrakePower", "", obj);
    mSlipStartAngle.init(50.0, "SlipStartAngle", "", obj);
    mSlipThresholdPower.init(2500.0, "SlipThresholdPower", "", obj);
    mSlipPowerMax.init(1800.0, "SlipPowerMax", "", obj);
    mWristBindRotation.init({-1.72, -1.84, -2.9}, "WristBindRotation", "", obj);
    mWristBindTranslation.init({0.355, 0.08, -0.145}, "WristBindTranslation", "", obj);
    mPostureLimitAngle.init(90.0, "PostureLimitAngle", "", obj);
    mInvalidPostureLimitSec.init(0.6, "InvalidPostureLimitSec", "", obj);
    mFallOverThresholdAngle.init(75.0, "FallOverThresholdAngle", "", obj);
    mJumpIntervalSec.init(1.0, "JumpIntervalSec", "", obj);
    mFullEnergyLastSec.init(240.0, "FullEnergyLastSec", "", obj);
    mWheelieLaunchJumpProhibitSec.init(0.1, "WheelieLaunchJumpProhibitSec", "", obj);
    mSlowModeTargetSpeedKPH2.init(400.0, "SlowModeTargetSpeedKPH2", "", obj);
    mSlowDriftTargetSpeedKPH2.init(3200.0, "SlowDriftTargetSpeedKPH2", "", obj);
    mSlowModeTransitionSec.init(2.0, "SlowModeTransitionSec", "", obj);
    mSlowSlipThresholdKPH.init(5.0, "SlowSlipThresholdKPH", "", obj);
    mSlowSlipThresholdPower.init(1200.0, "SlowSlipThresholdPower", "", obj);
    mSlowSlipThresholdSec.init(0.2, "SlowSlipThresholdSec", "", obj);
    mJumpRearWheelRotateRadPerSec.init(1.0, "JumpRearWheelRotateRadPerSec", "", obj);
    mWeaponThrowModeSpeedKPH2.init(800.0, "WeaponThrowModeSpeedKPH2", "", obj);
}

}  // namespace ksys::res
