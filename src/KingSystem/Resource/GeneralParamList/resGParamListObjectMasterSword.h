#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectMasterSword : public GParamListObject {
public:
    GParamListObjectMasterSword();
    const char* getName() const override { return "MasterSword"; }

    agl::utl::Parameter<bool> mIsMasterSword;
    agl::utl::Parameter<s32> mTrueFormAttackPower;
    agl::utl::Parameter<s32> mTrueFormMagicPower;
    agl::utl::Parameter<f32> mTrueFormBreakRatio;
    agl::utl::Parameter<f32> mSearchEvilDist;
    agl::utl::Parameter<s32> mRecoverTime;
    agl::utl::Parameter<sead::SafeString> mSleepActorName;
    agl::utl::Parameter<sead::SafeString> mTrueFormActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectMasterSword, 0x148);

inline GParamListObjectMasterSword::GParamListObjectMasterSword() {
    auto* const obj = &mObj;

    mIsMasterSword.init(false, "IsMasterSword", "", obj);
    mTrueFormAttackPower.init(-1, "TrueFormAttackPower", "", obj);
    mTrueFormMagicPower.init(-1, "TrueFormMagicPower", "", obj);
    mTrueFormBreakRatio.init(0.5, "TrueFormBreakRatio", "", obj);
    mSearchEvilDist.init(-1.0, "SearchEvilDist", "", obj);
    mRecoverTime.init(30, "RecoverTime", "", obj);
    mSleepActorName.init("", "SleepActorName", "", obj);
    mTrueFormActorName.init("", "TrueFormActorName", "", obj);
}

}  // namespace ksys::res
