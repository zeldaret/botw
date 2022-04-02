#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectRupee : public GParamListObject {
public:
    GParamListObjectRupee();
    const char* getName() const override { return "Rupee"; }

    agl::utl::Parameter<s32> mRupeeValue;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectRupee, 0x58);

inline GParamListObjectRupee::GParamListObjectRupee() {
    auto* const obj = &mObj;

    mRupeeValue.init(1, "RupeeValue", "", obj);
}

}  // namespace ksys::res
