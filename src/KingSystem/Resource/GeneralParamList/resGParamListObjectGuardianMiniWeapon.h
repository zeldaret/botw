#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGuardianMiniWeapon : public GParamListObject {
public:
    GParamListObjectGuardianMiniWeapon();
    const char* getName() const override { return "GuardianMiniWeapon"; }

    agl::utl::Parameter<sead::SafeString> mBindMyNodeName;
    agl::utl::Parameter<sead::SafeString> mVisibleMatNameR;
    agl::utl::Parameter<sead::SafeString> mVisibleMatNameL;
    agl::utl::Parameter<sead::SafeString> mVisibleMatNameB;
    agl::utl::Parameter<sead::SafeString> mVisibleOffMatName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGuardianMiniWeapon, 0x100);

inline GParamListObjectGuardianMiniWeapon::GParamListObjectGuardianMiniWeapon() {
    auto* const obj = &mObj;

    mBindMyNodeName.init("", "BindMyNodeName", "", obj);
    mVisibleMatNameR.init("", "VisibleMatNameR", "", obj);
    mVisibleMatNameL.init("", "VisibleMatNameL", "", obj);
    mVisibleMatNameB.init("", "VisibleMatNameB", "", obj);
    mVisibleOffMatName.init("Mt_Arm", "VisibleOffMatName", "", obj);
}

}  // namespace ksys::res
