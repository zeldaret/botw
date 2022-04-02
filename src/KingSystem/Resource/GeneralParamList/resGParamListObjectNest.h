#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectNest : public GParamListObject {
public:
    GParamListObjectNest();
    const char* getName() const override { return "Nest"; }

    agl::utl::Parameter<sead::SafeString> mCreateActor;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectNest, 0x60);

inline GParamListObjectNest::GParamListObjectNest() {
    auto* const obj = &mObj;

    mCreateActor.init("", "CreateActor", "", obj);
}

}  // namespace ksys::res
