#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectInsect : public GParamListObject {
public:
    GParamListObjectInsect();
    const char* getName() const override { return "Insect"; }

    agl::utl::Parameter<s32> mFireResistanceLevel;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectInsect, 0x58);

inline GParamListObjectInsect::GParamListObjectInsect() {
    auto* const obj = &mObj;

    mFireResistanceLevel.init(0, "FireResistanceLevel", "", obj);
}

}  // namespace ksys::res
