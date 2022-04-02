#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorseTargetedInfo : public GParamListObject {
public:
    GParamListObjectHorseTargetedInfo() {
        auto* const obj = &mObj;

        mHorseMoveRadius.init(-1.0, "HorseMoveRadius", "", obj);
        mHorseAvoidOffset.init(-1.0, "HorseAvoidOffset", "", obj);
        mIsCircularMoveAlways.init(false, "IsCircularMoveAlways", "", obj);
    }

    const char* getName() const override { return "HorseTargetedInfo"; }

    agl::utl::Parameter<f32> mHorseMoveRadius;
    agl::utl::Parameter<f32> mHorseAvoidOffset;
    agl::utl::Parameter<bool> mIsCircularMoveAlways;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectHorseTargetedInfo, 0x98);

}  // namespace ksys::res
