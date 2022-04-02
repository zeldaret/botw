#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGolem : public GParamListObject {
public:
    GParamListObjectGolem();
    const char* getName() const override { return "Golem"; }

    agl::utl::Parameter<sead::SafeString> mUpperArmRActor;
    agl::utl::Parameter<sead::SafeString> mLowerArmRActor;
    agl::utl::Parameter<sead::SafeString> mUpperArmLActor;
    agl::utl::Parameter<sead::SafeString> mLowerArmLActor;
    agl::utl::Parameter<sead::SafeString> mDefaultWeakPointActor;
    agl::utl::Parameter<bool> mIsDefaultChemicalOn;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGolem, 0x120);

inline GParamListObjectGolem::GParamListObjectGolem() {
    auto* const obj = &mObj;

    mUpperArmRActor.init("", "UpperArmRActor", "", obj);
    mLowerArmRActor.init("", "LowerArmRActor", "", obj);
    mUpperArmLActor.init("", "UpperArmLActor", "", obj);
    mLowerArmLActor.init("", "LowerArmLActor", "", obj);
    mDefaultWeakPointActor.init("", "DefaultWeakPointActor", "", obj);
    mIsDefaultChemicalOn.init(false, "IsDefaultChemicalOn", "", obj);
}

}  // namespace ksys::res
