#include "Game/AI/Action/actionReqCreateManufactedEquipItem.h"

namespace uking::action {

ReqCreateManufactedEquipItem::ReqCreateManufactedEquipItem(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ReqCreateManufactedEquipItem::~ReqCreateManufactedEquipItem() = default;

bool ReqCreateManufactedEquipItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReqCreateManufactedEquipItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReqCreateManufactedEquipItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReqCreateManufactedEquipItem::loadParams_() {}

void ReqCreateManufactedEquipItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
