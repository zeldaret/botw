#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectCookSpice : public GParamListObject {
public:
    GParamListObjectCookSpice();
    const char* getName() const override { return "CookSpice"; }

    agl::utl::Parameter<s32> mBoostHitPointRecover;
    agl::utl::Parameter<s32> mBoostEffectiveTime;
    agl::utl::Parameter<s32> mBoostSuccessRate;
    agl::utl::Parameter<s32> mBoostMaxHeartLevel;
    agl::utl::Parameter<s32> mBoostStaminaLevel;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectCookSpice, 0xd8);

inline GParamListObjectCookSpice::GParamListObjectCookSpice() {
    auto* const obj = &mObj;

    mBoostHitPointRecover.init(0, "BoostHitPointRecover", "", obj);
    mBoostEffectiveTime.init(0, "BoostEffectiveTime", "", obj);
    mBoostSuccessRate.init(0, "BoostSuccessRate", "", obj);
    mBoostMaxHeartLevel.init(0, "BoostMaxHeartLevel", "", obj);
    mBoostStaminaLevel.init(0, "BoostStaminaLevel", "", obj);
}

}  // namespace ksys::res
