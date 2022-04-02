#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorseCreator : public GParamListObject {
public:
    GParamListObjectHorseCreator() {
        auto* const obj = &mObj;

        mHorseNames.init("", "HorseNames", "", obj);
        mLeaderHorseNames.init("", "LeaderHorseNames", "", obj);
    }

    const char* getName() const override { return "HorseCreator"; }

    agl::utl::Parameter<sead::SafeString> mHorseNames;
    agl::utl::Parameter<sead::SafeString> mLeaderHorseNames;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectHorseCreator, 0x88);

}  // namespace ksys::res
