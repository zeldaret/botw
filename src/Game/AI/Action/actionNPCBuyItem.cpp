#include "Game/AI/Action/actionNPCBuyItem.h"

namespace uking::action {

NPCBuyItem::NPCBuyItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCBuyItem::~NPCBuyItem() = default;

bool NPCBuyItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCBuyItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCBuyItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCBuyItem::loadParams_() {}

void NPCBuyItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
