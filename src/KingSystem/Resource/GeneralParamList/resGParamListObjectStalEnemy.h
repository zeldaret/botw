#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectStalEnemy : public GParamListObject {
public:
    GParamListObjectStalEnemy() {
        auto* const obj = &mObj;

        mHeadActorName.init("", "HeadActorName", "", obj);
        mLeftArmActorName.init("", "LeftArmActorName", "", obj);
    }

    const char* getName() const override { return "StalEnemy"; }

    agl::utl::Parameter<sead::SafeString> mHeadActorName;
    agl::utl::Parameter<sead::SafeString> mLeftArmActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectStalEnemy, 0x88);

}  // namespace ksys::res
