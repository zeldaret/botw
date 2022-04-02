#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAutoGen : public GParamListObject {
public:
    GParamListObjectAutoGen();
    const char* getName() const override { return "AutoGen"; }

    agl::utl::Parameter<sead::SafeString> mSetName;
    agl::utl::Parameter<sead::SafeString> mKeyActorName;
    agl::utl::Parameter<f32> mSetRadius;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAutoGen, 0xa8);

inline GParamListObjectAutoGen::GParamListObjectAutoGen() {
    auto* const obj = &mObj;

    mSetName.init("", "SetName", "", obj);
    mKeyActorName.init("", "KeyActorName", "", obj);
    mSetRadius.init(0.0, "SetRadius", "", obj);
}

}  // namespace ksys::res
