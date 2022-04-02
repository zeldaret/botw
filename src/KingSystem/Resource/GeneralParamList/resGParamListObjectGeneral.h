#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGeneral : public GParamListObject {
public:
    GParamListObjectGeneral();
    const char* getName() const override { return "General"; }

    agl::utl::Parameter<f32> mSpeed;
    agl::utl::Parameter<s32> mLife;
    agl::utl::Parameter<bool> mIsLifeInfinite;
    agl::utl::Parameter<f32> mElectricalDischarge;
    agl::utl::Parameter<bool> mIsBurnOutBorn;
    agl::utl::Parameter<sead::SafeString> mBurnOutBornName;
    agl::utl::Parameter<bool> mIsBurnOutBornIdent;
    agl::utl::Parameter<sead::SafeString> mChangeDropTableName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGeneral, 0x148);

inline GParamListObjectGeneral::GParamListObjectGeneral() {
    auto* const obj = &mObj;

    mSpeed.init(1.0, "Speed", "", obj);
    mLife.init(100, "Life", "", obj);
    mIsLifeInfinite.init(false, "IsLifeInfinite", "", obj);
    mElectricalDischarge.init(1.0, "ElectricalDischarge", "", obj);
    mIsBurnOutBorn.init(false, "IsBurnOutBorn", "", obj);
    mBurnOutBornName.init("", "BurnOutBornName", "", obj);
    mIsBurnOutBornIdent.init(false, "IsBurnOutBornIdent", "", obj);
    mChangeDropTableName.init("", "ChangeDropTableName", "", obj);
}

}  // namespace ksys::res
