#include "Game/AI/Action/actionEventEquipLastSetItem.h"

namespace uking::action {

EventEquipLastSetItem::EventEquipLastSetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventEquipLastSetItem::~EventEquipLastSetItem() = default;

bool EventEquipLastSetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventEquipLastSetItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventEquipLastSetItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventEquipLastSetItem::loadParams_() {}

void EventEquipLastSetItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
