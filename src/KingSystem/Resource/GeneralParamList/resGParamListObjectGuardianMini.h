#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGuardianMini : public GParamListObject {
public:
    GParamListObjectGuardianMini();
    const char* getName() const override { return "GuardianMini"; }

    agl::utl::Parameter<s32> mColorType;
    agl::utl::Parameter<sead::SafeString> mBodyMatName;
    agl::utl::Parameter<sead::SafeString> mGuardJustActor;
    agl::utl::Parameter<sead::SafeString> mBeamName;
    agl::utl::Parameter<sead::SafeString> mLineBeamName;
    agl::utl::Parameter<sead::SafeString> mFinalBeamName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGuardianMini, 0x120);

inline GParamListObjectGuardianMini::GParamListObjectGuardianMini() {
    auto* const obj = &mObj;

    mColorType.init(0, "ColorType", "", obj);
    mBodyMatName.init("", "BodyMatName", "", obj);
    mGuardJustActor.init("", "GuardJustActor", "", obj);
    mBeamName.init("", "BeamName", "", obj);
    mLineBeamName.init("", "LineBeamName", "", obj);
    mFinalBeamName.init("", "FinalBeamName", "", obj);
}

}  // namespace ksys::res
