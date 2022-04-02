#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectMonsterShop : public GParamListObject {
public:
    GParamListObjectMonsterShop();
    const char* getName() const override { return "MonsterShop"; }

    agl::utl::Parameter<s32> mBuyMamo;
    agl::utl::Parameter<s32> mSellMamo;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectMonsterShop, 0x78);

inline GParamListObjectMonsterShop::GParamListObjectMonsterShop() {
    auto* const obj = &mObj;

    mBuyMamo.init(0, "BuyMamo", "", obj);
    mSellMamo.init(0, "SellMamo", "", obj);
}

}  // namespace ksys::res
