#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectEnemyShown : public GParamListObject {
public:
    GParamListObjectEnemyShown();
    const char* getName() const override { return "EnemyShown"; }

    agl::utl::Parameter<bool> mIsHappy;
    agl::utl::Parameter<bool> mIsCasebyCase;
    agl::utl::Parameter<bool> mIsSit;
    agl::utl::Parameter<bool> mIsNoise;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectEnemyShown, 0xb8);

inline GParamListObjectEnemyShown::GParamListObjectEnemyShown() {
    auto* const obj = &mObj;

    mIsHappy.init(false, "IsHappy", "", obj);
    mIsCasebyCase.init(false, "IsCasebyCase", "", obj);
    mIsSit.init(false, "IsSit", "", obj);
    mIsNoise.init(false, "IsNoise", "", obj);
}

}  // namespace ksys::res
