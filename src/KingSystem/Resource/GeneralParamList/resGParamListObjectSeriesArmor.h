#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectSeriesArmor : public GParamListObject {
public:
    GParamListObjectSeriesArmor();
    const char* getName() const override { return "SeriesArmor"; }

    agl::utl::Parameter<sead::SafeString> mSeriesType;
    agl::utl::Parameter<bool> mEnableCompBonus;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectSeriesArmor, 0x80);

inline GParamListObjectSeriesArmor::GParamListObjectSeriesArmor() {
    auto* const obj = &mObj;

    mSeriesType.init("", "SeriesType", "", obj);
    mEnableCompBonus.init(false, "EnableCompBonus", "", obj);
}

}  // namespace ksys::res
