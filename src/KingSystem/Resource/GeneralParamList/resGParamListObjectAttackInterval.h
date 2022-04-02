#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAttackInterval : public GParamListObject {
public:
    GParamListObjectAttackInterval();
    const char* getName() const override { return "AttackInterval"; }

    agl::utl::Parameter<s32> mShortAttackTimeMin;
    agl::utl::Parameter<s32> mShortAttackTimeMax;
    agl::utl::Parameter<s32> mMiddleAttackTimeMin;
    agl::utl::Parameter<s32> mMiddleAttackTimeMax;
    agl::utl::Parameter<s32> mLongAttackTimeMin;
    agl::utl::Parameter<s32> mLongAttackTimeMax;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAttackInterval, 0xf8);

inline GParamListObjectAttackInterval::GParamListObjectAttackInterval() {
    auto* const obj = &mObj;

    mShortAttackTimeMin.init(10, "ShortAttackTimeMin", "", obj);
    mShortAttackTimeMax.init(30, "ShortAttackTimeMax", "", obj);
    mMiddleAttackTimeMin.init(40, "MiddleAttackTimeMin", "", obj);
    mMiddleAttackTimeMax.init(60, "MiddleAttackTimeMax", "", obj);
    mLongAttackTimeMin.init(80, "LongAttackTimeMin", "", obj);
    mLongAttackTimeMax.init(110, "LongAttackTimeMax", "", obj);
}

}  // namespace ksys::res
