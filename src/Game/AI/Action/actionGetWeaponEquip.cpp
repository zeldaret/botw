#include "Game/AI/Action/actionGetWeaponEquip.h"

namespace uking::action {

GetWeaponEquip::GetWeaponEquip(const InitArg& arg) : GetItem(arg) {}

GetWeaponEquip::~GetWeaponEquip() = default;

bool GetWeaponEquip::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetWeaponEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetWeaponEquip::leave_() {
    GetItem::leave_();
}

void GetWeaponEquip::loadParams_() {}

void GetWeaponEquip::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
