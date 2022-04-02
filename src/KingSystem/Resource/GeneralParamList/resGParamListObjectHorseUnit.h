#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorseUnit : public GParamListObject {
public:
    GParamListObjectHorseUnit();
    const char* getName() const override { return "HorseUnit"; }

    agl::utl::Parameter<s32> mRiddenAnimalType;
    agl::utl::Parameter<s32> mCalmDownNum;
    agl::utl::Parameter<f32> mRideonAboveASHeight;
    agl::utl::Parameter<f32> mRideonAboveASRadius;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectHorseUnit, 0xb8);

inline GParamListObjectHorseUnit::GParamListObjectHorseUnit() {
    auto* const obj = &mObj;

    mRiddenAnimalType.init(0, "RiddenAnimalType", "", obj);
    mCalmDownNum.init(10, "CalmDownNum", "", obj);
    mRideonAboveASHeight.init(1.0, "RideonAboveASHeight", "", obj);
    mRideonAboveASRadius.init(1.0, "RideonAboveASRadius", "", obj);
}

}  // namespace ksys::res
