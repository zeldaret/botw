#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorse : public GParamListObject {
public:
    GParamListObjectHorse();
    const char* getName() const override { return "Horse"; }

    agl::utl::Parameter<bool> mIsDecoy;
    agl::utl::Parameter<bool> mHasMane;
    agl::utl::Parameter<sead::SafeString> mASVariation;
    agl::utl::Parameter<s32> mNature;
    agl::utl::Parameter<f32> mAttackPowerMultiplierGear2;
    agl::utl::Parameter<f32> mAttackPowerMultiplierGear3;
    agl::utl::Parameter<f32> mAttackPowerMultiplierGearTop;
    agl::utl::Parameter<f32> mRunnableFramesAtGearTop;
    agl::utl::Parameter<f32> mGearTopInterval;
    agl::utl::Parameter<s32> mGearTopChargeNum;
    agl::utl::Parameter<sead::SafeString> mEatActorNames;
    agl::utl::Parameter<sead::SafeString> mEatActorNamesForExtraCharge;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectHorse, 0x1d0);

inline GParamListObjectHorse::GParamListObjectHorse() {
    auto* const obj = &mObj;

    mIsDecoy.init(false, "IsDecoy", "", obj);
    mHasMane.init(true, "HasMane", "", obj);
    mASVariation.init("Normal", "ASVariation", "", obj);
    mNature.init(0, "Nature", "", obj);
    mAttackPowerMultiplierGear2.init(0.0, "AttackPowerMultiplierGear2", "", obj);
    mAttackPowerMultiplierGear3.init(0.0, "AttackPowerMultiplierGear3", "", obj);
    mAttackPowerMultiplierGearTop.init(6.0, "AttackPowerMultiplierGearTop", "", obj);
    mRunnableFramesAtGearTop.init(180.0, "RunnableFramesAtGearTop", "", obj);
    mGearTopInterval.init(240.0, "GearTopInterval", "", obj);
    mGearTopChargeNum.init(3, "GearTopChargeNum", "", obj);
    mEatActorNames.init("", "EatActorNames", "", obj);
    mEatActorNamesForExtraCharge.init("", "EatActorNamesForExtraCharge", "", obj);
}

}  // namespace ksys::res
