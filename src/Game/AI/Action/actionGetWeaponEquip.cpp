#include "Game/AI/Action/actionGetWeaponEquip.h"

namespace uking::action {

GetWeaponEquip::GetWeaponEquip(const InitArg& arg) : GetItem(arg) {}

void GetWeaponEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetWeaponEquip::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
