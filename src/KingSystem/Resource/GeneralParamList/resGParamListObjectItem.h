#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectItem : public GParamListObject {
public:
    GParamListObjectItem();
    const char* getName() const override { return "Item"; }

    agl::utl::Parameter<bool> mPlayerUseItem;
    agl::utl::Parameter<s32> mSellingPrice;
    agl::utl::Parameter<s32> mBuyingPrice;
    agl::utl::Parameter<s32> mCreatingPrice;
    agl::utl::Parameter<s32> mStainColor;
    agl::utl::Parameter<s32> mSaleRevivalCount;
    agl::utl::Parameter<sead::SafeString> mUseIconActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectItem, 0x120);

inline GParamListObjectItem::GParamListObjectItem() {
    auto* const obj = &mObj;

    mPlayerUseItem.init(false, "PlayerUseItem", "", obj);
    mSellingPrice.init(-1, "SellingPrice", "", obj);
    mBuyingPrice.init(-1, "BuyingPrice", "", obj);
    mCreatingPrice.init(-1, "CreatingPrice", "", obj);
    mStainColor.init(-1, "StainColor", "", obj);
    mSaleRevivalCount.init(-1, "SaleRevivalCount", "", obj);
    mUseIconActorName.init("", "UseIconActorName", "", obj);
}

}  // namespace ksys::res
