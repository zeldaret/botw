#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectBullet : public GParamListObject {
public:
    GParamListObjectBullet();
    const char* getName() const override { return "Bullet"; }

    agl::utl::Parameter<bool> mNoHitParent;
    agl::utl::Parameter<bool> mIsLimitCount;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectBullet, 0x78);

inline GParamListObjectBullet::GParamListObjectBullet() {
    auto* const obj = &mObj;

    mNoHitParent.init(true, "NoHitParent", "", obj);
    mIsLimitCount.init(false, "IsLimitCount", "", obj);
}

}  // namespace ksys::res
