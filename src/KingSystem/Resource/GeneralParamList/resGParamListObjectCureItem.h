#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectCureItem : public GParamListObject {
public:
    GParamListObjectCureItem();
    const char* getName() const override { return "CureItem"; }

    agl::utl::Parameter<s32> mHitPointRecover;
    agl::utl::Parameter<sead::SafeString> mEffectType;
    agl::utl::Parameter<s32> mEffectLevel;
    agl::utl::Parameter<s32> mEffectiveTime;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectCureItem, 0xc0);

inline GParamListObjectCureItem::GParamListObjectCureItem() {
    auto* const obj = &mObj;

    mHitPointRecover.init(0, "HitPointRecover", "", obj);
    mEffectType.init("None", "EffectType", "", obj);
    mEffectLevel.init(0, "EffectLevel", "", obj);
    mEffectiveTime.init(0, "EffectiveTime", "", obj);
}

}  // namespace ksys::res
