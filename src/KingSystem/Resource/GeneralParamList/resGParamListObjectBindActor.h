#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectBindActor : public GParamListObject {
public:
    GParamListObjectBindActor();
    const char* getName() const override { return "BindActor"; }

    agl::utl::Parameter<sead::SafeString> mBindActorName;
    agl::utl::Parameter<bool> mIsKeepSleep;
};

inline GParamListObjectBindActor::GParamListObjectBindActor() {
    auto* const obj = &mObj;

    mBindActorName.init("", "BindActorName", "", obj);
    mIsKeepSleep.init(false, "IsKeepSleep", "", obj);
}

}  // namespace ksys::res
