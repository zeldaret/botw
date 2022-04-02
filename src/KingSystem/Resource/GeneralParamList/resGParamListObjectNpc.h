#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectNpc : public GParamListObject {
public:
    GParamListObjectNpc();
    const char* getName() const override { return "Npc"; }

    agl::utl::Parameter<bool> mIsReactNakedPlayer;
    agl::utl::Parameter<bool> mUseAutoLabel;
    agl::utl::Parameter<bool> mIsOffPodFromWeapon;
    agl::utl::Parameter<bool> mIsRunRainWhenGoToSleep;
    agl::utl::Parameter<bool> mIsWalkUnderShelterFromRain;
    agl::utl::Parameter<bool> mIsSlowWalkOnSandAndSnow;
    agl::utl::Parameter<bool> mIsAlwaysCounterPlayerAttack;
    agl::utl::Parameter<bool> mIsNotTurnDetect;
    agl::utl::Parameter<bool> mIsNotEscapeFromTerror;
    agl::utl::Parameter<s32> mTolerantTime;
    agl::utl::Parameter<s32> mTolerantCount;
    agl::utl::Parameter<s32> mCounterRate;
    agl::utl::Parameter<sead::SafeString> mChangeSearchModeFlagName;
    agl::utl::Parameter<sead::SafeString> mOnFlagWhenDelete;
    agl::utl::Parameter<sead::SafeString> mOffFlagWhenDelete;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectNpc, 0x230);

inline GParamListObjectNpc::GParamListObjectNpc() {
    auto* const obj = &mObj;

    mIsReactNakedPlayer.init(false, "IsReactNakedPlayer", "", obj);
    mUseAutoLabel.init(true, "UseAutoLabel", "", obj);
    mIsOffPodFromWeapon.init(false, "IsOffPodFromWeapon", "", obj);
    mIsRunRainWhenGoToSleep.init(true, "IsRunRainWhenGoToSleep", "", obj);
    mIsWalkUnderShelterFromRain.init(true, "IsWalkUnderShelterFromRain", "", obj);
    mIsSlowWalkOnSandAndSnow.init(false, "IsSlowWalkOnSandAndSnow", "", obj);
    mIsAlwaysCounterPlayerAttack.init(false, "IsAlwaysCounterPlayerAttack", "", obj);
    mIsNotTurnDetect.init(false, "IsNotTurnDetect", "", obj);
    mIsNotEscapeFromTerror.init(false, "IsNotEscapeFromTerror", "", obj);
    mTolerantTime.init(20, "TolerantTime", "", obj);
    mTolerantCount.init(10, "TolerantCount", "", obj);
    mCounterRate.init(30, "CounterRate", "", obj);
    mChangeSearchModeFlagName.init("", "ChangeSearchModeFlagName", "", obj);
    mOnFlagWhenDelete.init("", "OnFlagWhenDelete", "", obj);
    mOffFlagWhenDelete.init("", "OffFlagWhenDelete", "", obj);
}

}  // namespace ksys::res
