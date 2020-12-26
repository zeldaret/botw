#include "Game/AI/Action/actionNPCMakeItem.h"

namespace uking::action {

NPCMakeItem::NPCMakeItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCMakeItem::~NPCMakeItem() = default;

bool NPCMakeItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCMakeItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCMakeItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCMakeItem::loadParams_() {
    getDynamicParam(&mShopType_d, "ShopType");
    getDynamicParam(&mIncludePorch_d, "IncludePorch");
}

void NPCMakeItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
