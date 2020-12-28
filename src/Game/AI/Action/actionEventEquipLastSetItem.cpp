#include "Game/AI/Action/actionEventEquipLastSetItem.h"

namespace uking::action {

EventEquipLastSetItem::EventEquipLastSetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventEquipLastSetItem::~EventEquipLastSetItem() = default;

bool EventEquipLastSetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventEquipLastSetItem::loadParams_() {}

}  // namespace uking::action
