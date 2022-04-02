#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectPictureBook : public GParamListObject {
public:
    GParamListObjectPictureBook() {
        auto* const obj = &mObj;

        mLiveSpot1.init(-1, "LiveSpot1", "", obj);
        mLiveSpot2.init(-1, "LiveSpot2", "", obj);
        mSpecialDrop.init(-1, "SpecialDrop", "", obj);
    }

    const char* getName() const override { return "PictureBook"; }

    agl::utl::Parameter<s32> mLiveSpot1;
    agl::utl::Parameter<s32> mLiveSpot2;
    agl::utl::Parameter<s32> mSpecialDrop;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectPictureBook, 0x98);

}  // namespace ksys::res
