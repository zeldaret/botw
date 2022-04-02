#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectPrey : public GParamListObject {
public:
    GParamListObjectPrey();
    const char* getName() const override { return "Prey"; }

    agl::utl::Parameter<f32> mEatActorFindRadius;
    agl::utl::Parameter<f32> mEatActorFindRotDegree;
    agl::utl::Parameter<f32> mWaitTimeForStartEat;
    agl::utl::Parameter<bool> mIsEnableGroupEscape;
    agl::utl::Parameter<f32> mAimEscapeOffsetRate;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectPrey, 0xd8);

inline GParamListObjectPrey::GParamListObjectPrey() {
    auto* const obj = &mObj;

    mEatActorFindRadius.init(-1.0, "EatActorFindRadius", "", obj);
    mEatActorFindRotDegree.init(135.0, "EatActorFindRotDegree", "", obj);
    mWaitTimeForStartEat.init(150.0, "WaitTimeForStartEat", "", obj);
    mIsEnableGroupEscape.init(true, "IsEnableGroupEscape", "", obj);
    mAimEscapeOffsetRate.init(1.0, "AimEscapeOffsetRate", "", obj);
}

}  // namespace ksys::res
