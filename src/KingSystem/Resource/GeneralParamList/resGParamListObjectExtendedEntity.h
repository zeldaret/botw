#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectExtendedEntity : public GParamListObject {
public:
    GParamListObjectExtendedEntity();
    const char* getName() const override { return "ExtendedEntity"; }

    agl::utl::Parameter<bool> mIsUsePivotAdjustRange;
    agl::utl::Parameter<f32> mPivotAdjustRange;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectExtendedEntity, 0x78);

inline GParamListObjectExtendedEntity::GParamListObjectExtendedEntity() {
    auto* const obj = &mObj;

    mIsUsePivotAdjustRange.init(false, "IsUsePivotAdjustRange", "", obj);
    mPivotAdjustRange.init(1.0, "PivotAdjustRange", "", obj);
}

}  // namespace ksys::res
