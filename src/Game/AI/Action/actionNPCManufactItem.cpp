#include "Game/AI/Action/actionNPCManufactItem.h"

namespace uking::action {

NPCManufactItem::NPCManufactItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCManufactItem::~NPCManufactItem() = default;

bool NPCManufactItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCManufactItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCManufactItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCManufactItem::loadParams_() {}

void NPCManufactItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
