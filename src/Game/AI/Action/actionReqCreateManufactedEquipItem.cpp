#include "Game/AI/Action/actionReqCreateManufactedEquipItem.h"

namespace uking::action {

ReqCreateManufactedEquipItem::ReqCreateManufactedEquipItem(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ReqCreateManufactedEquipItem::~ReqCreateManufactedEquipItem() = default;

bool ReqCreateManufactedEquipItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReqCreateManufactedEquipItem::loadParams_() {}

}  // namespace uking::action
