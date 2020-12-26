#include "Game/AI/Action/actionShopFixedItemNum.h"

namespace uking::action {

ShopFixedItemNum::ShopFixedItemNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShopFixedItemNum::~ShopFixedItemNum() = default;

bool ShopFixedItemNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShopFixedItemNum::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShopFixedItemNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShopFixedItemNum::loadParams_() {
    getDynamicParam(&mIsSelectAll_d, "IsSelectAll");
}

void ShopFixedItemNum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
