#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGiantArmor : public GParamListObject {
public:
    GParamListObjectGiantArmor();
    const char* getName() const override { return "GiantArmor"; }

    agl::utl::Parameter<f32> mDamageScale;
    agl::utl::Parameter<sead::Vector3f> mRotOffset;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGiantArmor, 0x80);

inline GParamListObjectGiantArmor::GParamListObjectGiantArmor() {
    auto* const obj = &mObj;

    mDamageScale.init(0.0, "DamageScale", "", obj);
    mRotOffset.init({0.0, 0.0, 0.0}, "RotOffset", "", obj);
}

}  // namespace ksys::res
