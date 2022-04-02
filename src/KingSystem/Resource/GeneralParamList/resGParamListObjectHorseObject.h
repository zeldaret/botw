#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectHorseObject : public GParamListObject {
public:
    GParamListObjectHorseObject();
    const char* getName() const override { return "HorseObject"; }

    agl::utl::Parameter<bool> mHideHorseMane;
    agl::utl::Parameter<bool> mIsHorseClothDisable;
};

inline GParamListObjectHorseObject::GParamListObjectHorseObject() {
    auto* const obj = &mObj;

    mHideHorseMane.init(false, "HideHorseMane", "", obj);
    mIsHorseClothDisable.init(false, "IsHorseClothDisable", "", obj);
}

}  // namespace ksys::res
