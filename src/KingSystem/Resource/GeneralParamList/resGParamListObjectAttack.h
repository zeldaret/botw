#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAttack : public GParamListObject {
public:
    GParamListObjectAttack();
    const char* getName() const override { return "Attack"; }

    agl::utl::Parameter<s32> mPower;
    agl::utl::Parameter<s32> mImpulse;
    agl::utl::Parameter<s32> mImpulseLarge;
    agl::utl::Parameter<f32> mRange;
    agl::utl::Parameter<s32> mGuardBreakPower;
    agl::utl::Parameter<sead::SafeString> mSpHitActor;
    agl::utl::Parameter<sead::SafeString> mSpHitTag;
    agl::utl::Parameter<f32> mSpHitRatio;
    agl::utl::Parameter<sead::SafeString> mSpWeakHitActor;
    agl::utl::Parameter<s32> mPowerForPlayer;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAttack, 0x190);

inline GParamListObjectAttack::GParamListObjectAttack() {
    auto* const obj = &mObj;

    mPower.init(0, "Power", "", obj);
    mImpulse.init(0, "Impulse", "", obj);
    mImpulseLarge.init(0, "ImpulseLarge", "", obj);
    mRange.init(0.0, "Range", "", obj);
    mGuardBreakPower.init(0, "GuardBreakPower", "", obj);
    mSpHitActor.init("", "SpHitActor", "", obj);
    mSpHitTag.init("", "SpHitTag", "", obj);
    mSpHitRatio.init(2.0, "SpHitRatio", "", obj);
    mSpWeakHitActor.init("", "SpWeakHitActor", "", obj);
    mPowerForPlayer.init(-1, "PowerForPlayer", "", obj);
}

}  // namespace ksys::res
