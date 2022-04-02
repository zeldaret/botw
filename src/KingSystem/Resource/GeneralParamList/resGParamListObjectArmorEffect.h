#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectArmorEffect : public GParamListObject {
public:
    GParamListObjectArmorEffect();
    const char* getName() const override { return "ArmorEffect"; }

    agl::utl::Parameter<sead::SafeString> mEffectType;
    agl::utl::Parameter<s32> mEffectLevel;
    agl::utl::Parameter<bool> mAncientPowUp;
    agl::utl::Parameter<bool> mEnableClimbWaterfall;
    agl::utl::Parameter<bool> mEnableSpinAttack;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectArmorEffect, 0xe0);

inline GParamListObjectArmorEffect::GParamListObjectArmorEffect() {
    auto* const obj = &mObj;

    mEffectType.init("None", "EffectType", "", obj);
    mEffectLevel.init(0, "EffectLevel", "", obj);
    mAncientPowUp.init(false, "AncientPowUp", "", obj);
    mEnableClimbWaterfall.init(false, "EnableClimbWaterfall", "", obj);
    mEnableSpinAttack.init(false, "EnableSpinAttack", "", obj);
}

}  // namespace ksys::res
