#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAnimalFollowOffset : public GParamListObject {
public:
    GParamListObjectAnimalFollowOffset();
    const char* getName() const override { return "AnimalFollowOffset"; }

    agl::utl::Parameter<sead::Vector3f> mEatLocalOffset;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAnimalFollowOffset, 0x60);

inline GParamListObjectAnimalFollowOffset::GParamListObjectAnimalFollowOffset() {
    auto* const obj = &mObj;

    mEatLocalOffset.init({0.0, 0.0, 0.0}, "EatLocalOffset", "", obj);
}

}  // namespace ksys::res
