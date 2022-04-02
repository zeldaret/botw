#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGuardian : public GParamListObject {
public:
    GParamListObjectGuardian();
    const char* getName() const override { return "Guardian"; }

    agl::utl::Parameter<s32> mGuardianModelType;
    agl::utl::Parameter<s32> mGuardianControllerType;
    agl::utl::Parameter<f32> mHeadLimitMax;
    agl::utl::Parameter<f32> mHeadLimitMin;
    agl::utl::Parameter<f32> mSightLimitMax;
    agl::utl::Parameter<f32> mSightLimitMin;
    agl::utl::Parameter<f32> mMaxSpeed;
    agl::utl::Parameter<sead::SafeString> mCannonBoneName;
    agl::utl::Parameter<f32> mRapidFireDistance;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGuardian, 0x160);

inline GParamListObjectGuardian::GParamListObjectGuardian() {
    auto* const obj = &mObj;

    mGuardianModelType.init(0, "GuardianModelType", "", obj);
    mGuardianControllerType.init(0, "GuardianControllerType", "", obj);
    mHeadLimitMax.init(90.0, "HeadLimitMax", "", obj);
    mHeadLimitMin.init(-90.0, "HeadLimitMin", "", obj);
    mSightLimitMax.init(90.0, "SightLimitMax", "", obj);
    mSightLimitMin.init(-90.0, "SightLimitMin", "", obj);
    mMaxSpeed.init(25.0, "MaxSpeed", "", obj);
    mCannonBoneName.init("Eye", "CannonBoneName", "", obj);
    mRapidFireDistance.init(10.0, "RapidFireDistance", "", obj);
}

}  // namespace ksys::res
